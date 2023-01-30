#pragma once
#include <string>

/*****************************************************************************
* @author : xiaoteng
* @date : 2021/4/12 16:32
* @last change : 
* @description : 文件读写到字符串的操作
*****************************************************************************/
class BaseFile
{
public:
	BaseFile(std::string data);

	int Read(const char* file_path);

	int Write(const char* file_path);	

	static int Move(std::string src_path, std::string des_path);

public:
	std::string filedata_;
};

