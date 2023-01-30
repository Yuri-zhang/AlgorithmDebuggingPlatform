#ifndef crash_infos_h
#define crash_infos_h
#include <string>
#include <windows.h>

//回调消息

namespace CrashInfo
{
	void GetErrorName(DWORD error_code, std::string &error_name);

	void PrintStack(std::string &stack_info);

	void DisableSetUnhandledExceptionFilter();

	void SaveStack(std::string file_name,std::string &stack_info);
	
	/*****************************************************************************
	@description : 获取进程名称
	@param:
	@retrun:
	*****************************************************************************/
	BOOL GetProcessName(std::string &strProcessName);
}
#endif
