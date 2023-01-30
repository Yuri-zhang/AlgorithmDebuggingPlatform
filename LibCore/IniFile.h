#ifndef IniFile_h
#define IniFile_h
#include <string>
#include <windows.h>

/*****************************************************************************
* @author : xiaoteng
* @date : 2020/11/27 14:00
* @last change :
* @description : ini配置文件读写
*****************************************************************************/
class   IniFile
{
public:
	IniFile(const char *pFile);
	IniFile(std::string pFile);
	~IniFile();

	/*****************************************************************************
	@description : 获取ini文件路径
	@param: 	
	@retrun:  
	*****************************************************************************/
	std::string GetPathName();

	/*****************************************************************************
	@description : 获取值
	@param: 	
	@retrun:  
	*****************************************************************************/
	bool GetValue(std::string string_section, std::string string_key, bool bDefault = false);
	int GetValue(std::string string_section, std::string string_key, int nDefault = 0);
	double GetValue(std::string string_section, std::string string_key, double dDefault = 0.0);
	std::string GetValue(std::string string_section, std::string string_key, const char* strDefault = "");
	std::string GetValue(std::string string_section, std::string string_key, std::string strDefault = "");
	RECT GetValue(std::string string_section, std::string string_key, RECT rectDefault);

	/*****************************************************************************
	@description : 设置值
	@param: 	
	@retrun:  
	*****************************************************************************/
	bool SetValue(std::string string_section, std::string string_key, bool bDefault = false);
	int SetValue(std::string string_section, std::string string_key, int nDefault = 0);
	double SetValue(std::string string_section, std::string string_key, double dDefault = 0.0);
	std::string SetValue(std::string string_section, std::string string_key,const char *strDefault = "");
	std::string SetValue(std::string string_section, std::string string_key, std::string strDefault = "");
	int SetValue(std::string string_section, std::string string_key, RECT rectDefault);
	
protected:
	//文件路径
	std::string filepath_;

	//数据缓存
	char stringbuffer_[MAX_PATH];
};

#endif