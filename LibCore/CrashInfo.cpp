#include "pch.h"
#include "CrashInfos.h"
#include <new.h>
#include <eh.h>
#include <csignal>
#include <set>
#include <dbghelp.h>
#include "BaseFile.h"
void CrashInfo::GetErrorName(DWORD error_code, std::string &error_name)
{
	error_name = "";
	switch (error_code)
	{
	case STATUS_ACCESS_VIOLATION:
		error_name = "访问越界";
		break;
	case STATUS_IN_PAGE_ERROR:
		error_name = "页内错误";
		break;
	case STATUS_INVALID_HANDLE:
		error_name = "句柄错误";
		break;
	case STATUS_INVALID_PARAMETER:
		error_name = "错误的页码";
		break;
	case STATUS_NO_MEMORY:
		error_name = "存储错误";
		break;
	case STATUS_ILLEGAL_INSTRUCTION:
		error_name = "错误指令";
		break;
	case STATUS_NONCONTINUABLE_EXCEPTION:
		error_name = "不可控错误";
		break;
	case STATUS_INVALID_DISPOSITION:
		error_name = "非法地址";
		break;
	case STATUS_ARRAY_BOUNDS_EXCEEDED:
		error_name = "数组越界";
		break;
	case STATUS_FLOAT_DENORMAL_OPERAND:
		error_name = "访问越界";
		break;
	case STATUS_FLOAT_DIVIDE_BY_ZERO:
		error_name = "除零异常";
		break;
	case STATUS_FLOAT_INEXACT_RESULT:
		error_name = "浮点数不精确";
		break;
	case STATUS_FLOAT_INVALID_OPERATION:
		error_name = "浮点数错误操作";
		break;
	case STATUS_FLOAT_OVERFLOW:
		error_name = "浮点数越界";
		break;
	case STATUS_FLOAT_STACK_CHECK:
		error_name = "浮点数栈";
		break;
	case STATUS_FLOAT_UNDERFLOW:
		error_name = "访问越界";
		break;
	case STATUS_INTEGER_DIVIDE_BY_ZERO:
		error_name = "浮点数除零异常";
		break;
	case STATUS_INTEGER_OVERFLOW:
		error_name = "整数越界";
		break;
	case STATUS_PRIVILEGED_INSTRUCTION:
		error_name = "特权指令";
		break;
	case STATUS_STACK_OVERFLOW:
		error_name = "栈溢出";
		break;
	case STATUS_DLL_NOT_FOUND:
		error_name = "dll无法找到";
		break;
	case STATUS_ORDINAL_NOT_FOUND:
		error_name = "序数无法找到";
		break;
	case STATUS_ENTRYPOINT_NOT_FOUND:
		error_name = "入口无法找到";
		break;
	case STATUS_CONTROL_C_EXIT:
		error_name = "control+c退出";
		break;
	case STATUS_DLL_INIT_FAILED:
		error_name = "dll初始化错误";
		break;
	case STATUS_FLOAT_MULTIPLE_FAULTS:
		error_name = "浮点数多个错误";
		break;
	case STATUS_FLOAT_MULTIPLE_TRAPS:
		error_name = "浮点数多个错误";
		break;
	case STATUS_REG_NAT_CONSUMPTION:
		error_name = "STATUS_REG_NAT_CONSUMPTION";
		break;
	case STATUS_HEAP_CORRUPTION:
		error_name = "堆损坏";
		break;
	case STATUS_STACK_BUFFER_OVERRUN:
		error_name = "栈缓存溢出";
		break;
	case STATUS_INVALID_CRUNTIME_PARAMETER:
		error_name = "错误的持续参数";
		break;
	case STATUS_ASSERTION_FAILURE:
		error_name = "断言错误";
		break;
	//case STATUS_ENCLAVE_VIOLATION:
	//	error_name = "violation异常";
	//	break;
	default:
		break;
	}
}

void CrashInfo::DisableSetUnhandledExceptionFilter()
{
	/*void *addr = (void*)GetProcAddress(LoadLibrary(_T("kernel32.dll")),
		"SetUnhandledExceptionFilter");
	if (addr)
	{
		unsigned char code[16];
		int size = 0;
		code[size++] = 0x33;
		code[size++] = 0xC0;
		code[size++] = 0xC2;
		code[size++] = 0x04;
		code[size++] = 0x00;
		DWORD dwOldFlag, dwTempFlag;
		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
	}*/
}


void CrashInfo::PrintStack(std::string &stack_info)
{
	void   *stack[100];
	HANDLE process = GetCurrentProcess();
	SymInitialize(process, NULL, TRUE);
	unsigned short frames = CaptureStackBackTrace(0, 100, stack, NULL);	

	DWORD symOptions = SymGetOptions();
	symOptions |= SYMOPT_LOAD_LINES;
	symOptions |= SYMOPT_FAIL_CRITICAL_ERRORS;
	//symOptions |= SYMOPT_DEBUG;
	SymSetOptions(symOptions);

	SYMBOL_INFO * symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	for (unsigned int index = 0; index < frames; index++)
	{
		IMAGEHLP_MODULE64 module_info;
		memset(&module_info, 0, sizeof(module_info));
		module_info.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
		SymGetModuleInfo64(process, (DWORD64)(stack[index]), &module_info);
	
		//防止符号Name过长 2022-01
		const int MAX_NAME_LEN = 8192;

		char info[MAX_NAME_LEN] = { 0 };
		BOOL result=SymFromAddr(process, (DWORD64)(stack[index]), 0, symbol);
		if (!result)
		{
			sprintf_s(info, MAX_NAME_LEN,"%s,符号解析失败,0x%llX,GetLastError[%d]",
				module_info.ModuleName,
				(DWORD64)(stack[index]),
				GetLastError());
			stack_info += std::to_string(frames - index - 1) + " " + info + "\n";
			continue;
		}
		sprintf_s(info, MAX_NAME_LEN, " %s - 0x%llX",
			symbol->Name,
			symbol->Address);	

		IMAGEHLP_LINE64 line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		std::string line_info = "";
		DWORD displacement;
		if (SymGetLineFromAddr64(process, (DWORD64)(stack[index]), &displacement, &line))
		{
			line_info = std::string(line.FileName)
				+" "
				+std::to_string(line.LineNumber) 
				+ info;
		}			
		else
		{
			line_info = std::string(module_info.ModuleName)+" "+info;
		}

		stack_info += std::to_string(frames-index-1)+" "+line_info+"\n";
	}
	free(symbol);
}

void CrashInfo::SaveStack(std::string file_name, std::string &stack_info)
{
	//写入堆栈信息
	stack_info = "";
	CrashInfo::PrintStack(stack_info);
	BaseFile stack_file(stack_info);
	stack_file.Write(file_name.c_str());
}


BOOL CrashInfo::GetProcessName(std::string &strProcessName)
{
	char cIniFileName[MAX_PATH];
	GetModuleFileNameA(NULL, cIniFileName, sizeof(cIniFileName));
	char *pProcessName = strrchr(cIniFileName, '\\');
	if (pProcessName)
	{
		pProcessName = pProcessName + 1;
	}
	if (pProcessName == NULL)
	{
		return FALSE;
	}
	strProcessName = std::string(pProcessName);
	return TRUE;
}

