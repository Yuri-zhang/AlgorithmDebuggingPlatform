#pragma once
#include <windows.h>
#include <string>

class CrashHandler
{
public:
	typedef void(*CrashMessage)(const char* message,const char *stack_message, void *context);


public:
	/*****************************************************************************
	@description :   初始化崩溃泄露捕获
	@param:
	*****************************************************************************/
	void Init(bool show_message_box = true, bool show_stack_message=true, const char* save_path="./log");


	/*****************************************************************************
	@description :  关闭崩溃泄露
	@param:
	*****************************************************************************/
	void Close();

	/*****************************************************************************
	@description :   设置回调消息
	@param:
	*****************************************************************************/
	void SetPostMessage(CrashMessage function, void *context);


	// Sets exception handlers that work on per-process basis
	void AttachProcess();


	// Installs C++ exception handlers that function on per-thread basis
	void AttachThread();

	/*****************************************************************************
	@description : 设置异常标记
	@param:
	@retrun:
	*****************************************************************************/
	static void SetFlag(const char* flag = "system");

	/*****************************************************************************
	@description :   获取标记的名称
	@param:
	*****************************************************************************/
	static void GetFlagName(std::string &name);

	/*****************************************************************************
	@description :   获取标记的名称
	@param:
	*****************************************************************************/
	static void GetFirstFlagName(std::string &name);

	/*****************************************************************************
	@description :  移除异常标记
	@param:
	*****************************************************************************/
	static void RemoveFlag(const char* flag = "system");

private:
	static int GenerateDumpFile(PEXCEPTION_POINTERS pExceptionPointers);

	/*****************************************************************************
	@description :  异常过滤
	@param:
	@retrun:
		>=0 success, <0 failed
	*****************************************************************************/
	static LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo);


	static void PostCRTCrashMessage(std::string name);


	static LONG WINAPI VectoredExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo);


	static void __cdecl TerminateHandler();
	static void __cdecl UnexpectedHandler();
	static void __cdecl PureCallHandler();
	static void __cdecl InvalidParameterHandler(const wchar_t* expression,
		const wchar_t* function,
		const wchar_t* file,
		unsigned int line,
		uintptr_t pReserved);
	static int __cdecl NewHandler(size_t size);
	static void SigabrtHandler(int code);
	static void SigfpeHandler(int code, int subcode);
	static void SigintHandler(int code);
	static void SigillHandler(int code);
	static void SigsegvHandler(int code);
	static void SigtermHandler(int code);

private:
	static std::string  save_path_;
};
