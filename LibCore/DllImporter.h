#ifndef ImportDll_h
#define ImportDll_h
#include <windows.h>

/*****************************************************************************
* @author : xiaoteng
* @date : 2020/11/27 14:12
* @last change : 
* @description : dll动态导入
*****************************************************************************/
class    DllImporter
{
	enum 
	{
		MaxImportDllCount=200,
	};
public:	
	DllImporter();
	~DllImporter();
	
	
	/*****************************************************************************
	@description : 导入目录中所有的dll
	@param: 	
	@retrun:  
	*****************************************************************************/
	bool Import(const char *pDllPath, bool bRecur = false);

	/*****************************************************************************
	@description : 释放dll
	@param: 	
	@retrun:  
	*****************************************************************************/
	void FreeDll();	
	
private:
	HMODULE *importdll_;
	int importcount_ ;

};

#endif