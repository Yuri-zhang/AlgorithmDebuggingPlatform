#include "pch.h"
#include "DllImporter.h"
#include <iostream>
#include <string>        // for strcat()
#include <io.h>
#include "GString.h"

using namespace std;
DllImporter::DllImporter()
{	
	importdll_ = new HMODULE[MaxImportDllCount];
	importcount_ = 0;
	for (int nIndex = 0; nIndex < MaxImportDllCount; nIndex++)
	{		
		importdll_[nIndex] = NULL;
	}
}


DllImporter::~DllImporter()
{
	FreeDll();
	if (importdll_)
	{
		delete[] importdll_;
		importdll_ = NULL;
	}
}


bool DllImporter::Import(const char *dllpath, bool recur)
{
	if (importcount_== MaxImportDllCount)
	{
		return false;
	}
	char convert_path[MAX_PATH];	
	GetFullPathNameA(dllpath,
		MAX_PATH,
		convert_path,
		NULL);

	char newdirectory[MAX_PATH];
	strcpy_s(newdirectory, MAX_PATH, convert_path);
	strcat_s(newdirectory, "\\*.*");   
	intptr_t handle;
	_finddata_t findData;
	handle = _findfirst(newdirectory, &findData);
	if (handle == -1)      
		return false;
	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;
			//cout << findData.name << "\t<dir>\n";
			strcpy_s(newdirectory, MAX_PATH, convert_path);
			strcat_s(newdirectory, "\\");
			strcat_s(newdirectory, findData.name);
			if (recur)
			{
				DllImporter(newdirectory);
			}
		}
		else
		{
			strcpy_s(newdirectory, MAX_PATH, convert_path);
			strcat_s(newdirectory, "\\");
			strcat_s(newdirectory, findData.name);

			if (GString::GetFileNamExt(findData.name)=="dll")
			{
				importdll_[importcount_] = LoadLibraryExA(newdirectory, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
				if (importdll_[importcount_] != NULL)
				{
					importcount_++;
				}
				//cout << findData.name << "\t" << findData.size << " bytes.\n";
			}		
		}
		
	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);
	return true;
}


void DllImporter::FreeDll()
{
	for (int nIndex=0;nIndex<importcount_;nIndex++)
	{
		FreeLibrary(importdll_[nIndex]);
		importdll_[nIndex] = NULL;
	}
	importcount_ = 0;
}


