#include "pch.h"
#include "FileDirectory.h"
#include <windows.h>
#include <filesystem>
#include <Shlwapi.h>
#include <io.h>
#include "GString.h"
#include <Shlwapi.h>
#include <algorithm>
#include <shellapi.h>

static bool classComare(std::string a, std::string b)
{
	int nResult = StrCmpLogicalW(GString(a.c_str()).toWString().c_str(),
		GString(b.c_str()).toWString().c_str());
	if (nResult > 0)
	{
		return false;
	}
	else
		return true;
}


int FileDirectory::DeleteFolder(std::string forder, bool  bDeleteSubdirectories)
{
	bool            bSubdirectory = false;       // Flag, indicating whether
											  // subdirectories have been found
	HANDLE          hFile;                       // Handle to directory
	std::string     strFilePath;                 // Filepath
	std::string     strPattern;                  // Pattern
	WIN32_FIND_DATAA FileInformation;             // File information

	strPattern = forder + "\\*.*";
	hFile = ::FindFirstFileA(strPattern.c_str(), &FileInformation);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FileInformation.cFileName[0] != '.')
			{
				strFilePath.erase();
				strFilePath = forder + "\\" + FileInformation.cFileName;

				if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (bDeleteSubdirectories)
					{
						// Delete subdirectory
						int iRC = DeleteFolder(strFilePath, bDeleteSubdirectories);
						if (iRC)
							return iRC;
					}
					else
						bSubdirectory = true;
				}
				else
				{
					// Set file attributes
					if (::SetFileAttributesA(strFilePath.c_str(),
						FILE_ATTRIBUTE_NORMAL) == FALSE)
						return ::GetLastError();

					// Delete file
					if (::DeleteFileA(strFilePath.c_str()) == FALSE)
						return ::GetLastError();
				}
			}
		} while (::FindNextFileA(hFile, &FileInformation) == TRUE);

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
			return dwError;
		else
		{
			if (!bSubdirectory)
			{
				// Set directory attributes
				if (::SetFileAttributesA(forder.c_str(),
					FILE_ATTRIBUTE_NORMAL) == FALSE)
					return ::GetLastError();

				// Delete directory
				if (::RemoveDirectoryA(forder.c_str()) == FALSE)
					return ::GetLastError();
			}
		}
	}

	return 0;
}


bool FileDirectory::CreateFolder(std::string forder)
{
	return CreateDirectoryA(forder.c_str(),NULL);
}

bool FileDirectory::PathFileExist(std::string forder)
{
	return _access(forder.c_str(), 0) == 0?true:false;
}


std::string FileDirectory::CurrentDirectory()
{
	char strBuffer[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, strBuffer);
	return std::string(strBuffer);
}

int FileDirectory::GetSubForder(std::string forder, std::vector<std::string>& sub_forders)
{
	sub_forders.clear();
	struct __finddata64_t fileinfo;
	std::string current = forder + "\\*.*";
	__int64 handle = _findfirst64(current.c_str(), &fileinfo);
	int fileNum = 0;
	if (handle == -1)
		return 0;

	while (!_findnext64(handle, &fileinfo))
	{
		if ((_A_SUBDIR & fileinfo.attrib)!=0
			&& 0 != strcmp(fileinfo.name, ".")
			&& 0 != strcmp(fileinfo.name, ".."))
		{
			sub_forders.push_back(fileinfo.name);
		}		
	}

	_findclose(handle);

	std::sort(sub_forders.begin(), sub_forders.end(), classComare);

	return fileNum;
}


int FileDirectory::GetFiles(std::string forder, std::vector<std::string>& paths)
{
	paths.clear();
	struct __finddata64_t fileinfo;
	std::string current = forder + "\\*.*";
	__int64 handle = _findfirst64(current.c_str(), &fileinfo);
	int fileNum = 0;
	if (handle == -1)
		return 0;

	while (!_findnext64(handle, &fileinfo))
	{
		if (0 == strcmp(fileinfo.name, "..") 
			|| 0 == strcmp(fileinfo.name, ".")
			|| _A_SUBDIR == fileinfo.attrib) 
		{
			continue;
		}
		else
		{
			GString convert_string;
			std::string file_ext = convert_string.GetFileExtType(fileinfo.name);
			paths.push_back(fileinfo.name);
		}
	}
	_findclose(handle);
	return int(paths.size());
}



bool FileDirectory::CopySigFile(std::string src, std::string des)
{
	return CopyFileA(src.c_str(), des.c_str(),false);
}


int FileDirectory::CopyForder(std::string src_forder, std::string des_forder, bool clear_des_forder)
{
	if (clear_des_forder)
	{
		DeleteFolder(des_forder);
	}

	CreateFolder(des_forder);

	
	GString src_convert;
	src_convert = src_forder;
	src_convert.Replace("/", "\\");
	

	GString des_convert;
	des_convert = des_forder;
	des_convert.Replace("/", "\\");

	std::string cmd = "xcopy " + src_convert.ToStdString() + " " + des_convert.ToStdString() + " /I /S /Y ";
	return WinExec(cmd.c_str(), SW_HIDE);
}