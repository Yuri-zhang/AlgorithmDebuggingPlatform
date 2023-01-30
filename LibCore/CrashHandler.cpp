#include "pch.h"
#include "CrashHandler.h"
#include "CrashInfos.h"
#include <new.h>
#include <eh.h>
#include <csignal>
#include <set>
#include <dbghelp.h>
#include "LockHelper.h"
#include "BaseFile.h"
static bool _show_message_box = true;
static bool _show_stack_message = true;
static bool init_ = false;
static bool catch_crash = true;
static HANDLE mutex_ = NULL;
static CrashHandler::CrashMessage crash_message_function_ = NULL;
static void* context_ = NULL;
std::string CrashHandler::save_path_ = "./log";
static std::set<std::string> _flag;


void CrashHandler::Init(bool show_message_box ,bool show_stack_message, const char* save_path)
{
	_show_message_box = show_message_box;
	_show_stack_message = show_stack_message;
	if (mutex_==NULL)
	{
		mutex_ = CreateMutex(NULL, FALSE, NULL);
	}

	if (!init_)
	{
		init_ = true;	

		AddVectoredExceptionHandler(1, VectoredExceptionHandler);
		SetUnhandledExceptionFilter(ExceptionFilter);
		CrashInfo::DisableSetUnhandledExceptionFilter();
		AttachProcess();
		AttachThread();
	}

	save_path_ = save_path + std::string("\\");
	CreateDirectoryA(save_path_.c_str(), NULL);

	catch_crash = true;
}


void CrashHandler::Close()
{
	if (mutex_)
	{
		CloseHandle(mutex_);
		mutex_ = NULL;
	}
	catch_crash = false;
}


void CrashHandler::PostCRTCrashMessage(std::string name)
{
	if (!catch_crash)
	{
		return;
	}

	char message_data[MAX_PATH] = { 0 };
	std::string process_name;
	CrashInfo::GetProcessName(process_name);
	SYSTEMTIME stLocalTime;
	GetLocalTime(&stLocalTime);

	std::string flag_name;
	GetFlagName(flag_name);
	sprintf_s(message_data, "%s_%s_%s",		
		process_name.c_str(),
		flag_name.c_str(),
		name.c_str());
		
	

	// 创建 dmp 文件件
	SYSTEMTIME local_time;
	GetLocalTime(&local_time);
	char strtime[MAX_PATH];
	sprintf_s(strtime, "%04d%02d%02d-%02d%02d%02d",
		local_time.wYear,
		local_time.wMonth,
		local_time.wDay,
		local_time.wHour,
		local_time.wMinute,
		local_time.wSecond);

	std::string file_name;
	std::string exception_message;
	
	exception_message = process_name + "-"
		+ std::string(strtime) + "-"
		+ flag_name + "-"
		+ name;

	std::string first_exceptin_name;
	GetFirstFlagName(first_exceptin_name);
	file_name = save_path_
		+ process_name + "-"
		+ std::string(strtime) + "-"
		+ first_exceptin_name.c_str() + "-"
		+ name
		+ ".dmp";


	std::string stack_infos;
	CrashInfo::SaveStack(file_name + ".txt", stack_infos);

	stack_infos = exception_message + "\n" + stack_infos;

	if (crash_message_function_)
	{
		crash_message_function_(message_data,
			stack_infos.c_str(),
			context_);
	}

	if (_show_message_box)
	{
		MessageBoxA(NULL, message_data, "高视半导体---异常名称", MB_ICONERROR);
	}	

	if (_show_stack_message)
	{
		MessageBoxA(NULL, stack_infos.c_str(), "高视半导体---堆栈", MB_ICONERROR);
	}

	SetUnhandledExceptionFilter(ExceptionFilter);
	
}

const int MaxNameLen = 256;
void printStack(CONTEXT *ctx1,std::string &stackstring) //Prints stack trace based on context record
{
 	CONTEXT ctx;
 	RtlCaptureContext(&ctx);
	BOOL    result;
	HANDLE  process;
	HANDLE  thread;
	HMODULE hModule;

	STACKFRAME64        stack;
	ULONG               frame;
	DWORD64             displacement;

	DWORD disp;
	IMAGEHLP_LINE64 *line;

	char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
	char module[MaxNameLen];
	PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

	memset(&stack, 0, sizeof(STACKFRAME64));

	process = GetCurrentProcess();
	thread = GetCurrentThread();
	displacement = 0;
#if !defined(_M_AMD64)
	stack.AddrPC.Offset = (*ctx).Eip;
	stack.AddrPC.Mode = AddrModeFlat;
	stack.AddrStack.Offset = (*ctx).Esp;
	stack.AddrStack.Mode = AddrModeFlat;
	stack.AddrFrame.Offset = (*ctx).Ebp;
	stack.AddrFrame.Mode = AddrModeFlat;
#endif

	SymInitialize(process, NULL, TRUE); //load symbols

	for (frame = 0; ; frame++)
	{
		char str_info[MAX_PATH];
		//get next call from stack
		result = StackWalk64
		(
#if defined(_M_AMD64)
			IMAGE_FILE_MACHINE_AMD64
#else
			IMAGE_FILE_MACHINE_I386
#endif
			,
			process,
			thread,
			&stack,
			ctx1,
			NULL,
			SymFunctionTableAccess64,
			SymGetModuleBase64,
			NULL
		);

		if (!result) 
			break;
		//get symbol name for address
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		pSymbol->MaxNameLen = MAX_SYM_NAME;
		SymFromAddr(process, (ULONG64)stack.AddrPC.Offset, &displacement, pSymbol);
		line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
		line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		//try to get line
		if (SymGetLineFromAddr64(process, stack.AddrPC.Offset, &disp, line))
		{
			sprintf_s(str_info,"\tat %s in %s: line: %lu: address: 0x%llX\n", pSymbol->Name, 
				line->FileName,
				line->LineNumber, 
				pSymbol->Address);
		}
		else
		{
			//failed to get line
			sprintf_s(str_info,"\tat %s, address 0x%llX.\n", pSymbol->Name, pSymbol->Address);
			hModule = NULL;
			lstrcpyA(module, "");
			GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
				(LPCTSTR)(stack.AddrPC.Offset), &hModule);
			//at least print module name
			if (hModule != NULL)GetModuleFileNameA(hModule, module, MaxNameLen);
			//printf("in %s\n", module);
		}
		free(line);
		line = NULL;
		stackstring += str_info;
	}
}


int CrashHandler::GenerateDumpFile(PEXCEPTION_POINTERS pExceptionPointers)
{
	if (!catch_crash)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	
	// 创建 dmp 文件件
	SYSTEMTIME local_time;
	GetLocalTime(&local_time);
	char strtime[MAX_PATH];
	sprintf_s(strtime, "%04d%02d%02d-%02d%02d%02d",
		local_time.wYear,
		local_time.wMonth,
		local_time.wDay,
		local_time.wHour,
		local_time.wMinute,
		local_time.wSecond);

	std::string file_name;
	std::string exception_message;	

	std::string process_name;
	CrashInfo::GetProcessName(process_name);
	
	std::string flag_name;
	GetFlagName(flag_name);
	std::string exception_name;
	CrashInfo::GetErrorName(pExceptionPointers->ExceptionRecord->ExceptionCode,
		exception_name);

	exception_message = process_name + "-"
		+ std::string(strtime) + "-"
		+ flag_name + "-"
		+ exception_name;
	
	std::string first_exceptin_name;
	GetFirstFlagName(first_exceptin_name);
	file_name = save_path_
		+process_name + "-"
		+ std::string(strtime) + "-"
		+ first_exceptin_name.c_str() + "-"
		+ exception_name
		+ ".dmp";
	
	if (file_name.length()>MAX_PATH)
	{
		file_name = save_path_
			+ process_name + "-"
			+ std::string(strtime) + "-"		
			+ exception_name
			+ ".dmp";
	}		

	//保存堆栈信息
	std::string stack_infos;
	CrashInfo::SaveStack(file_name + ".txt", stack_infos);
	//printStack(pExceptionPointers->ContextRecord, stack_infos);

	//StackWalkerToConsole sw; // output to console
	//sw.ShowCallstack(GetCurrentThread(), pExceptionPointers->ContextRecord);
	//LFile stack_file(sw.message_);
	//stack_file.write((file_name + ".log").c_str());

	if (crash_message_function_)
	{
		crash_message_function_(exception_message.c_str(), 
			stack_infos.c_str(),
			context_);
	}

	if (_show_message_box)
	{
		MessageBoxA(NULL,
			(flag_name+"_"+exception_name).c_str(),
			(std::string("高视半导体---异常名称:") + save_path_ + process_name).c_str(),
			MB_ICONERROR);
	}

	if (_show_stack_message)
	{
		MessageBoxA(NULL,
			stack_infos.c_str(),
			(std::string("高视半导体---堆栈:") + save_path_ + process_name).c_str(),
			MB_ICONERROR);
	}
	
	HANDLE hDumpFile = CreateFileA(file_name.c_str(), GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

	if (INVALID_HANDLE_VALUE == hDumpFile)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	// 写入 dmp 文件
	MINIDUMP_EXCEPTION_INFORMATION expParam;
	expParam.ThreadId = GetCurrentThreadId();
	expParam.ExceptionPointers = pExceptionPointers;
	expParam.ClientPointers = FALSE;

	bool dump_exception = MiniDumpWriteDump(GetCurrentProcess(),
		GetCurrentProcessId(),
		hDumpFile,
		MiniDumpNormal,
		(pExceptionPointers ? &expParam : NULL),
		NULL,
		NULL);

	// 释放文件
	CloseHandle(hDumpFile);

	if (!dump_exception)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}


LONG WINAPI CrashHandler::VectoredExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	if (!catch_crash)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	std::string error_name = "";
	switch (pExceptionInfo->ExceptionRecord->ExceptionCode)
	{
	case STATUS_ACCESS_VIOLATION:
	case STATUS_IN_PAGE_ERROR:
	case STATUS_INVALID_HANDLE:
	case STATUS_INVALID_PARAMETER:
	case STATUS_NO_MEMORY:
	case STATUS_ILLEGAL_INSTRUCTION:
	case STATUS_NONCONTINUABLE_EXCEPTION:
	case STATUS_INVALID_DISPOSITION:
	case STATUS_ARRAY_BOUNDS_EXCEEDED:
	case STATUS_FLOAT_DENORMAL_OPERAND:
	case STATUS_FLOAT_DIVIDE_BY_ZERO:
	case STATUS_FLOAT_INEXACT_RESULT:
	case STATUS_FLOAT_INVALID_OPERATION:
	case STATUS_FLOAT_OVERFLOW:
	case STATUS_FLOAT_STACK_CHECK:
	case STATUS_FLOAT_UNDERFLOW:
	case STATUS_INTEGER_DIVIDE_BY_ZERO:
	case STATUS_INTEGER_OVERFLOW:
	case STATUS_PRIVILEGED_INSTRUCTION:
	case STATUS_STACK_OVERFLOW:
		//case STATUS_DLL_NOT_FOUND:
	case STATUS_ORDINAL_NOT_FOUND:
		//case STATUS_ENTRYPOINT_NOT_FOUND:
	case STATUS_CONTROL_C_EXIT:
		//case STATUS_DLL_INIT_FAILED:
	case STATUS_FLOAT_MULTIPLE_FAULTS:
	case STATUS_FLOAT_MULTIPLE_TRAPS:
	case STATUS_REG_NAT_CONSUMPTION:
	case STATUS_HEAP_CORRUPTION:
	case STATUS_STACK_BUFFER_OVERRUN:
	case STATUS_INVALID_CRUNTIME_PARAMETER:
	case STATUS_ASSERTION_FAILURE:
	//case STATUS_ENCLAVE_VIOLATION:
		GenerateDumpFile(pExceptionInfo);
		return EXCEPTION_EXECUTE_HANDLER;
		break;
	default:
		SetUnhandledExceptionFilter(ExceptionFilter);
		break;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}


LONG WINAPI CrashHandler::ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	// 这里做一些异常的过滤或提示
	/*if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}*/
	return GenerateDumpFile(lpExceptionInfo);
}


void  __cdecl CrashHandler::TerminateHandler()
{
	PostCRTCrashMessage("TerminateHandler");
}
void __cdecl CrashHandler::UnexpectedHandler()
{
	PostCRTCrashMessage("UnexpectedHandler");
}

void __cdecl CrashHandler::PureCallHandler()
{
	PostCRTCrashMessage("PureCallHandler");
}

void __cdecl CrashHandler::InvalidParameterHandler(const wchar_t* expression,
	const wchar_t* function, const wchar_t* file,
	unsigned int line, uintptr_t pReserved)
{
	PostCRTCrashMessage("InvalidParameterHandler");
}

int __cdecl CrashHandler::NewHandler(size_t size)
{
	PostCRTCrashMessage("NewHandler");
	return 0;
}

void CrashHandler::SigabrtHandler(int code)
{
	PostCRTCrashMessage("SigabrtHandler");
}
void CrashHandler::SigfpeHandler(int code, int subcode)
{
	PostCRTCrashMessage("SigfpeHandler");
}
void CrashHandler::SigintHandler(int code)
{
	PostCRTCrashMessage("SigintHandler");
}
void CrashHandler::SigillHandler(int code)
{
	PostCRTCrashMessage("SigillHandler");
}
void CrashHandler::SigsegvHandler(int code)
{
	PostCRTCrashMessage("SigsegvHandler");
}
void CrashHandler::SigtermHandler(int code)
{
	PostCRTCrashMessage("SigtermHandler");
}


void CrashHandler::AttachProcess()
{
	// Catch pure virtual function calls.
	// Because there is one _purecall_handler for the whole process, 
	// calling this function immediately impacts all threads. The last 
	// caller on any thread sets the handler. 
	// http://msdn.microsoft.com/en-us/library/t296ys27.aspx
	_set_purecall_handler(PureCallHandler);

	// Catch new operator memory allocation exceptions
	_set_new_handler(NewHandler);

	// Catch invalid parameter exceptions.
	_set_invalid_parameter_handler(InvalidParameterHandler);

	// Set up C++ signal handlers

	_set_abort_behavior(_CALL_REPORTFAULT, _CALL_REPORTFAULT);

	// Catch an abnormal program termination
	signal(SIGABRT, SigabrtHandler);

	// Catch illegal instruction handler
	signal(SIGINT, SigintHandler);

	// Catch a termination request
	signal(SIGTERM, SigtermHandler);
}

void CrashHandler::AttachThread()
{
	// Catch terminate() calls. 
	// In a multithreaded environment, terminate functions are maintained 
	// separately for each thread. Each new thread needs to install its own 
	// terminate function. Thus, each thread is in charge of its own termination handling.
	// http://msdn.microsoft.com/en-us/library/t6fk7h29.aspx
	set_terminate(TerminateHandler);

	// Catch unexpected() calls.
	// In a multithreaded environment, unexpected functions are maintained 
	// separately for each thread. Each new thread needs to install its own 
	// unexpected function. Thus, each thread is in charge of its own unexpected handling.
	// http://msdn.microsoft.com/en-us/library/h46t5b69.aspx  
	set_unexpected(UnexpectedHandler);

	// Catch a floating point error
	typedef void(*sigh)(int);
	signal(SIGFPE, (sigh)SigfpeHandler);

	// Catch an illegal instruction
	signal(SIGILL, SigillHandler);

	// Catch illegal storage access errors
	signal(SIGSEGV, SigsegvHandler);
}


void CrashHandler::SetPostMessage(CrashMessage function, void *context)
{
	crash_message_function_ = function;
	context_ = context;
}


void CrashHandler::GetFirstFlagName(std::string &name)
{
	MutexHelper mutex(mutex_);
	name = "";
	if (_flag.size() > 0)
	{
		name = *_flag.begin();
	}
	else
	{
		name = "系统";
	}
}


void CrashHandler::GetFlagName(std::string &name)
{
	MutexHelper mutex(mutex_);
	name = "";
	for (auto it = _flag.begin(); it != _flag.end(); it++)
	{
		name += *it + " ";
	}

	if (name == "")
	{
		name = "system";
	}
}

void  CrashHandler::SetFlag(const char* flag)
{
	MutexHelper mutex(mutex_);
	_flag.insert(flag);
}

void  CrashHandler::RemoveFlag(const char* flag)
{
	MutexHelper mutex(mutex_);
	for (auto it = _flag.begin(); it != _flag.end(); it++)
	{
		if (*it == flag)
		{
			_flag.erase(it);
			return;
		}
	}
}
