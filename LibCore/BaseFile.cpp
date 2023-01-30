#include "pch.h"
#include "BaseFile.h"
#include<iostream>
#include <fstream>
#include <sstream>
#include <io.h>
#include <windows.h>
BaseFile::BaseFile(std::string data)
{
	filedata_ = data;
}

int BaseFile::Read(const char* file_path)
{
	if (_access_s(file_path,0)!=0)
	{
		return -1;
	}
	std::ifstream in;
	in.open(file_path, std::ios::in | std::ios::binary);
	if (!in.is_open())
	{
		return -1;
	}
	in.seekg(0, std::ios::end);
	int fileLen = in.tellg();
	in.seekg(0, std::ios::beg);

	char* data = new char[fileLen];
	if (!data)
	{
		return -1;
	}
	in.read(data, fileLen);

	filedata_ = std::string(data, fileLen);

	delete[] data;
	in.close();
	return 0;
}

int BaseFile::Write(const char* file_path)
{
	std::ofstream outfile;
	outfile.open(file_path, std::ios::out | std::ios::binary);
	if (!outfile.is_open())
	{
		return -1;
	}
	outfile.write(filedata_.c_str(), filedata_.size());

	outfile.close();

	return 0;
}

int BaseFile::Move(std::string src_path, std::string des_path)
{
	if (MoveFileA(src_path.c_str(), des_path.c_str()))
	{
		return 0;
	}
	return -1;
}
