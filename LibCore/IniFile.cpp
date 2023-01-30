#include "pch.h"
#include "IniFile.h"
#include <windows.h>

IniFile::IniFile(const char *pFile)
{
	char absolutepath[MAX_PATH];
	memset(absolutepath, 0, MAX_PATH);

	char* lpPart[MAX_PATH] = { NULL };
	GetFullPathNameA(pFile,
		MAX_PATH,
		absolutepath,
		lpPart);
	filepath_ = absolutepath;
	memset(stringbuffer_, 0, MAX_PATH);
}

IniFile::IniFile(std::string pFile) :IniFile(pFile.c_str())
{

}




IniFile::~IniFile()
{

}


std::string IniFile::GetPathName()
{
	return filepath_;
}

bool IniFile::GetValue(std::string strSection, std::string strKey, bool bDefault)
{
	memset(stringbuffer_, 0, MAX_PATH);
	GetPrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		bDefault ? "1" : "0",
		stringbuffer_,
		MAX_PATH,
		filepath_.c_str());

	if (std::string(stringbuffer_) <= "0")
	{
		return false;
	}
	else
		return true;

}


int IniFile::GetValue(std::string strSection, std::string strKey, int nDefault)
{
	memset(stringbuffer_, 0, MAX_PATH);
	static int nResult = 0;
	nResult = GetPrivateProfileIntA(strSection.c_str(),
		strKey.c_str(),
		nDefault,
		filepath_.c_str());

	return nResult;

}

double IniFile::GetValue(std::string strSection, std::string strKey, double dDefault)
{
	memset(stringbuffer_, 0, MAX_PATH);
	static double dResult = 0.0f;
	char strDefault[MAX_PATH];
	sprintf_s(strDefault, "%.5f", dDefault);
	GetPrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		strDefault,
		stringbuffer_,
		MAX_PATH,
		filepath_.c_str());

	dResult = atof(stringbuffer_);
	return dResult;

}

std::string IniFile::GetValue(std::string strSection, std::string strKey, const char* strDefault)
{
	return GetValue(strSection, strKey, std::string(strDefault));
}

std::string IniFile::GetValue(std::string strSection, std::string strKey, std::string strDefault)
{
	memset(stringbuffer_, 0, MAX_PATH);
	std::string strResult;
	GetPrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		strDefault.c_str(),
		stringbuffer_,
		MAX_PATH,
		filepath_.c_str());
	strResult = std::string(stringbuffer_);
	return strResult;
}

RECT IniFile::GetValue(std::string strSection, std::string strKey, RECT rectDefault)
{
	memset(stringbuffer_, 0, MAX_PATH);

	char strDefault[MAX_PATH];
	memset(strDefault, 0, MAX_PATH);

	GetPrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		strDefault,
		stringbuffer_,
		MAX_PATH,
		filepath_.c_str());

	if (std::string(stringbuffer_) == "")
	{
		return rectDefault;
	}

	if (strlen(stringbuffer_) != 2 * sizeof(RECT))
	{
		return rectDefault;
	}

	static RECT resultRect;
	LPBYTE lpb = (LPBYTE)&resultRect;
	char *pBuffer = stringbuffer_;
	for (DWORD i = 0; i < strlen(stringbuffer_); i++)
	{
		char sz[3] = "";
		strncpy_s(sz, pBuffer, 2);
		lpb[i] = BYTE(strtoul(sz, NULL, 16));
		pBuffer = &pBuffer[2];
	}


	return resultRect;
}


bool IniFile::SetValue(std::string strSection, std::string strKey, bool bDefault)
{
	WritePrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		bDefault ? "1" : "0",
		filepath_.c_str());

	return bDefault ? "1" : "0";
}
int IniFile::SetValue(std::string strSection, std::string strKey, int nDefault)
{
	char strBuffer[MAX_PATH];
	sprintf_s(strBuffer, "%d", nDefault);
	WritePrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		strBuffer,
		filepath_.c_str());

	return nDefault;

}


double IniFile::SetValue(std::string strSection, std::string strKey, double dDefault)
{
	char strBuffer[MAX_PATH];
	sprintf_s(strBuffer, "%.5f", dDefault);
	WritePrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		strBuffer,
		filepath_.c_str());

	return dDefault;
}

std::string IniFile::SetValue(std::string string_section, std::string string_key, const char *strDefault)
{
	return SetValue(string_section, string_key, std::string(strDefault));
}

std::string IniFile::SetValue(std::string strSection, std::string strKey, std::string strDefault)
{
	WritePrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		strDefault.c_str(),
		filepath_.c_str());

	return strDefault;
}

int IniFile::SetValue(std::string strSection, std::string strKey, RECT rectDefault)
{
	memset(stringbuffer_, 0, MAX_PATH);
	char strDefault[MAX_PATH];
	memset(strDefault, 0, MAX_PATH);

	const BYTE* lpb = (const BYTE*)&rectDefault;
	if (lpb == NULL)
	{
		return -1;
	}

	int nDataSize = sizeof(RECT) * 2 + 1;
	char *pBuffer = new char[nDataSize];
	memset(pBuffer, 0, nDataSize);
	int nLenght = 0;
	for (int nIndex = 0, j = 0; nIndex < sizeof(RECT); nIndex++, j += 2)
		nLenght += sprintf_s(&pBuffer[j], nDataSize - nLenght, "%02X", lpb[nIndex]);

	WritePrivateProfileStringA(strSection.c_str(),
		strKey.c_str(),
		pBuffer,
		filepath_.c_str());

	if (pBuffer)
	{
		delete[] pBuffer;
		pBuffer = NULL;
	}

	return 0;
}
