#include "pch.h"
#include "EnvViriable.h"
#include <windows.h>

std::string EnvViriable::GetValue(std::string name)
{
	char value[MAX_PATH];
	GetEnvironmentVariableA(name.c_str(), value, MAX_PATH);	
	value_ = std::string(value);
	return value_.c_str();
}


int EnvViriable::AppendPath(std::string path)
{
	char chBuf[0x8000] = { 0 };
	DWORD dwSize = GetEnvironmentVariableA("path", chBuf, 0x10000);

	return 0;
}