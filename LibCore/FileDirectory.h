#pragma once
#ifndef ldirectory_h
#define ldirectory_h
#include <string>
#include <vector>
#pragma comment(lib,"shlwapi.lib")
namespace FileDirectory
{
	/*****************************************************************************
	@description : 创建文件夹
	@param:

	@retrun:
		>=0 success, <0 failed
	*****************************************************************************/
	bool CreateFolder(std::string forder);


	/*****************************************************************************
	@description : 删除文件夹
	@param:
		
	@retrun:
		>=0 success, <0 failed
	*****************************************************************************/	
	int DeleteFolder(std::string forder, bool  bDeleteSubdirectories = true);

	
	/*****************************************************************************
		@description :  拷贝文件夹
		@param:
		 src_forder 为原目录，如果只需要复制所有bmp文件，则可以 .../*.bmp
		@retrun:
			>=0 success, <0 failed
		*****************************************************************************/
	int CopyForder(std::string src_forder, std::string des_forder, bool clear_des_forder = true);


	/*****************************************************************************
	@description : 文件夹是否存在
	@param:
		
	@retrun:
		>=0 success, <0 failed
	*****************************************************************************/
	bool PathFileExist(std::string forder);
  
	/*****************************************************************************
	@description : 获取子文件夹个数
	@param:
		
	@retrun:
		>=0 success, <0 failed
	*****************************************************************************/
	int GetSubForder(std::string forder,std::vector<std::string>&sub_forders);

	/*****************************************************************************
	@description : 获取文件夹内文件个数,不递归子文件夹
	@param:
		
	@retrun:
		>=0 success, <0 failed
	*****************************************************************************/
	int GetFiles(std::string forder, std::vector<std::string>&paths);


	/*****************************************************************************
	@description : 获取当前目录
	@param:	
	*****************************************************************************/
	std::string CurrentDirectory();


	/*****************************************************************************
	@description : 复制文件夹
	@param:	
	*****************************************************************************/
	bool CopySigFile(std::string src, std::string des);
}


#endif