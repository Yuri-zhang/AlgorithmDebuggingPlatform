// Coredata.cpp : 定义静态库的函数。
//

#include "pch.h"
#include <stdio.h>
#include "GString.h"
#include <algorithm>
#include "windows.h"
#include <iostream>
#include <sstream>

//编码表
const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//解码表 
const char DecodeTable[] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	62, // '+'
	0, 0, 0,
	63, // '/' 
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
	0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
	13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
	0, 0, 0, 0, 0, 0,
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
};

GString::GString()
{
	stringdata_ = "";
}

GString::GString(std::string strdata)
{
	stringdata_ = strdata;
}

GString::GString(std::wstring strdata)
{
	if (strdata.length()*2>=MAX_PATH)
	{
		int charsize = int(strdata.length() * 2+1);
		char *strBuffer = new char[charsize];
		memset(strBuffer, 0, sizeof(charsize));
		WideCharToMultiByte(CP_ACP,
			NULL,
			strdata.c_str(),
			(int)strdata.length(),
			strBuffer,
			charsize,
			NULL,
			NULL);
		stringdata_ = std::string(strBuffer);
		if (strBuffer)
		{
			delete strBuffer;
			strBuffer = NULL;
		}
	}
	else
	{
		char strBuffer[MAX_PATH];
		memset(strBuffer, 0, sizeof(strBuffer));
		WideCharToMultiByte(CP_ACP,
			NULL,
			strdata.c_str(),
			(int)strdata.length(),
			strBuffer,
			MAX_PATH,
			NULL,
			NULL);
		stringdata_ = std::string(strBuffer);
	}
	
}

GString::GString(char *data)
{
	if (data == NULL)
	{
		return;
	}
	stringdata_ = std::string(data);
}

GString::GString(const char *data) 
{
	if (data==NULL)
	{
		return;
	}
	stringdata_ = std::string(data);
}

GString::GString(unsigned char *data)
{
	if (data == NULL)
	{
		return;
	}
	stringdata_ = std::string((char*)data);
}

GString::GString(int data)
{
	stringdata_ = std::to_string(data);

}

GString::GString(double data)
{
	stringdata_ = std::to_string(data);
}


GString::GString(double data, int count)
{
	char strBuffer[MAX_PATH];
	std::string format_string = "%." + std::to_string(count) + "f";
	sprintf_s(strBuffer, MAX_PATH, format_string.c_str(), data);
	stringdata_ = strBuffer;
}


GString::GString(unsigned long long data)
{
	stringdata_ = std::to_string(data);
}

GString::GString(long long data)
{
	stringdata_ = std::to_string(data);
}

GString::~GString(){

}


std::string GString::ToStdString()const
{
	return stringdata_;
}


const char* GString::ToChar()const
{
	return stringdata_.c_str();
}


int GString::ToInt()const
{
	if (stringdata_.c_str())
	{
		return atoi(stringdata_.c_str());
	}
	else
		return -1;
	
}

double GString::ToDouble()const
{
	if (stringdata_.c_str())
	{
		return (double)atof(stringdata_.c_str());
	}
	else
		return -1.0;
	
}

int GString::Size()const
{
	return (int)stringdata_.length();
}


GString GString::Sub(int begin, int end)const
{
	return stringdata_.substr(begin, end - begin);
}

bool isntspace(const char& ch) 
{
	return !isspace(ch);
}

GString GString::TrimLeft()const
{
	std::string::const_iterator iter = find_if(stringdata_.begin(), stringdata_.end(), isntspace);
	return std::string(iter, stringdata_.end());
}

GString GString::TrimRight() const
{
	std::string::const_iterator iter = find_if(stringdata_.rbegin(), stringdata_.rend(), isntspace).base();
	return std::string(stringdata_.begin(), iter);
}


GString GString::Trim()const
{
	std::string::const_iterator iter1 = find_if(stringdata_.begin(), stringdata_.end(), isntspace);
	std::string::const_iterator iter2 = find_if(stringdata_.rbegin(), stringdata_.rend(), isntspace).base();
	return iter1 < iter2 ? std::string(iter1, iter2) : std::string("");
}


int GString::Find(const char *substring)const
{
	return (int)stringdata_.find(substring);
}


bool GString::IsEmpty()const
{
	return stringdata_.empty();
}


GString GString::Replace(const char *oldreplace, const char *newreplace)
{
	std::string before = oldreplace;
	std::string after = newreplace;
	for (std::string::size_type pos(0); pos != std::string::npos; pos += after.length())
	{
		pos = stringdata_.find(before, pos);
		if (pos != std::string::npos)
			stringdata_.replace(pos, before.length(), after);
		else
			break;
	}

	return *this;
}




GString GString::operator=(const GString &srcstring)
{
	stringdata_ = srcstring.ToStdString();
	return *this;
}


GString GString::operator+(const GString& combinestring)const
{	
	std::string newstring = stringdata_+ combinestring.ToStdString();
	return GString(newstring);
}


GString GString::operator*(int times) const
{
	std::string newstring="";
	for (int  index = 0; index < times; index++)
	{
		newstring += stringdata_;
	}
	return GString(newstring);
}


bool GString::operator==(const GString &other) const
{
	if (stringdata_ == other.ToStdString())
	{
		return true;
	}
	else
		return false;
}


std::wstring GString::toWString()
{
	if (stringdata_.length()>MAX_PATH)
	{
		wchar_t *wcsBuffer = new wchar_t[stringdata_.length()];
		memset(wcsBuffer, 0, stringdata_.length());
		MultiByteToWideChar(CP_ACP,
			NULL,
			stringdata_.c_str(),
			(int)stringdata_.length(),
			wcsBuffer,
			(int)stringdata_.length());

		std::wstring result= std::wstring(wcsBuffer);

		if (wcsBuffer)
		{
			delete []wcsBuffer;
			wcsBuffer = NULL;
		}

		return result;

	}
	else
	{
		wchar_t wcsBuffer[MAX_PATH];
		memset(wcsBuffer, 0, sizeof(wcsBuffer));
		MultiByteToWideChar(CP_ACP,
			NULL,
			stringdata_.c_str(),
			(int)stringdata_.length(),
			wcsBuffer,
			MAX_PATH);

		return std::wstring(wcsBuffer);
	}
}


int GString::FromUtf8(const char* szU8)
{
	stringdata_ = "";
	if (szU8 == NULL)
	{
		return -1;
	}
	size_t char_length = strlen(szU8);
	char *szString=new char[char_length];
	wchar_t *wszString = new wchar_t[char_length];
	memset(szString, 0, char_length);	
	memset(wszString, 0, sizeof(wchar_t)*char_length);
	//转换
	int length = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, (int)strlen(szU8), wszString, (int)char_length);
	//最后加上'\0'
	//wszString[nLenght] = '\0';
	length=WideCharToMultiByte(CP_ACP, 0, wszString, length, szString, (int)char_length, NULL, NULL);
	stringdata_ = std::string(szString, length);

	if (szString)
	{
		delete szString;
		szString = NULL;
	}

	if (wszString)
	{
		delete  wszString;
		wszString = NULL;
	}

	return 0;
}

std::string GString::ToUtf8()
{
	wchar_t wszString[MAX_PATH];
	memset(wszString, 0, MAX_PATH);
	int stringlength = ::MultiByteToWideChar(CP_ACP, NULL, stringdata_.c_str(), (int)stringdata_.length(),
		wszString, MAX_PATH);
	wszString[stringlength] = '\0';
	
	char szU8[MAX_PATH];
	memset(szU8, 0, sizeof(szU8));
	WideCharToMultiByte(CP_UTF8, 0, wszString, MAX_PATH, szU8, MAX_PATH, NULL, NULL);
	
	stringdata_ = std::string(szU8);
	return stringdata_;
}


std::vector<std::string> GString::Split(const std::string delim )
{
	std::vector<std::string> elems;
	size_t pos = 0;
	size_t len = stringdata_.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) 
		return elems;
	while (pos < len)
	{
		int find_pos = (int)stringdata_.find(delim, pos);
		if (find_pos < 0)
		{
			elems.push_back(stringdata_.substr(pos, len - pos));
			break;
		}
		elems.push_back(stringdata_.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}

std::vector<int> GString::SplitInt(const std::string delim )
{
	std::vector<int> elems;
	size_t pos = 0;
	size_t len = stringdata_.length();
	size_t delim_len = delim.length();
	if (delim_len == 0)
		return elems;
	while (pos < len)
	{
		int find_pos = (int)stringdata_.find(delim, pos);
		if (find_pos < 0
			&& stringdata_.substr(pos, len - pos).c_str())
		{
			elems.push_back(atoi(stringdata_.substr(pos, len - pos).c_str()));
			break;
		}

		if (stringdata_.substr(pos, find_pos - pos).c_str())
		{
			elems.push_back(atoi(stringdata_.substr(pos, find_pos - pos).c_str()));
		}
	
		pos = find_pos + delim_len;
	}
	return elems;
}

std::vector<double> GString::SplitDouble(const std::string delim)
{
	std::vector<double> elems;
	size_t pos = 0;
	size_t len = stringdata_.length();
	size_t delim_len = delim.length();
	if (delim_len == 0)
		return elems;
	while (pos < len)
	{
		int find_pos = (int)stringdata_.find(delim, pos);
		if (find_pos < 0
			&& stringdata_.substr(pos, len - pos).c_str())
		{
			elems.push_back(atof(stringdata_.substr(pos, len - pos).c_str()));
			break;
		}

		if (stringdata_.substr(pos, find_pos - pos).c_str())
		{
			elems.push_back(atof(stringdata_.substr(pos, find_pos - pos).c_str()));
		}

		pos = find_pos + delim_len;
	}
	return elems;
}


std::set<std::string> GString::SplitSet(const std::string delim)
{
	std::set<std::string> elems;
	size_t pos = 0;
	size_t len = stringdata_.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) 
		return elems;
	while (pos < len)
	{
		int find_pos =(int) stringdata_.find(delim, pos);
		if (find_pos < 0)
		{
			elems.insert(stringdata_.substr(pos, len - pos));
			break;
		}
		elems.insert(stringdata_.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}


std::string GString::FromBase64(const char*pData, int nDataByte)
{
	if (pData == NULL)
	{
		return "";
	}
	stringdata_ = "";
	
	int nValue;
	int i = 0;
	while (i < nDataByte)
	{
		if (*pData != '\r' && *pData != '\n')
		{
			nValue = DecodeTable[*pData++] << 18;
			nValue += DecodeTable[*pData++] << 12;
			stringdata_ += (nValue & 0x00FF0000) >> 16;
			if (*pData != '=')
			{
				nValue += DecodeTable[*pData++] << 6;
				stringdata_ += (nValue & 0x0000FF00) >> 8;
				if (*pData != '=')
				{
					nValue += DecodeTable[*pData++];
					stringdata_ += nValue & 0x000000FF;
				}
			}
			i += 4;
		}
		else
		{
			pData++;
			i++;
		}
	}
	return stringdata_;
}

int GString::ToBase64(std::string &strEncode)
{	
	strEncode = "";

	const char *pData = stringdata_.c_str();
	size_t nDataByte = stringdata_.length();	

	unsigned char Tmp[4] = { 0 };
	int LineLength = 0;
	for (int i = 0; i < (int)(nDataByte / 3); i++) {
		Tmp[1] = *pData++;
		Tmp[2] = *pData++;
		Tmp[3] = *pData++;
		strEncode += EncodeTable[Tmp[1] >> 2];
		strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode += EncodeTable[Tmp[3] & 0x3F];
	}
	//对剩余数据进行编码
	int Mod = nDataByte % 3;
	if (Mod == 1) {
		Tmp[1] = *pData++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode += "==";
	}
	else if (Mod == 2) {
		Tmp[1] = *pData++;
		Tmp[2] = *pData++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode += "=";
	}

	return 0;
}

std::string  GString::GetFileNameFromPath(std::string strFilePath, bool bIncludeEx)
{
	size_t nEndPos = strFilePath.rfind(".");
	if ((int)nEndPos < 0)
		return "";

	size_t nBeginPos = strFilePath.rfind("\\");
	if ((int)nBeginPos < 0)
	{
		nBeginPos = strFilePath.rfind("/");
	}

	if (bIncludeEx)
	{
		return strFilePath.substr(nBeginPos + 1, -1);
	}
	else
	{
		return strFilePath.substr(nBeginPos + 1, nEndPos - nBeginPos - 1);
	}

}

std::string  GString::GetFileNamExt(std::string strFilePath)
{
	size_t nBeginPos = strFilePath.rfind(".");
	return strFilePath.substr(nBeginPos + 1, -1);
}

std::string GString::GetFileFolderPath(std::string strFilePath)
{
	size_t nBeginPos = strFilePath.rfind("\\");

	return strFilePath.substr(0, max(0, nBeginPos));
}

std::string GString::GetFileExtType(std::string strFilePath)
{
	int nBeginPos = (int)strFilePath.rfind(".");
	return strFilePath.substr(nBeginPos + 1, -1);
}


std::string GString::RemoveIllegalCharater()
{
	Replace("\\","");
	Replace("/", "");
	Replace(":", "");
	Replace("?", "");
	Replace("/", "");
	Replace(">", "");
	Replace("<", "");
	Replace("|", "");
	return stringdata_;
}