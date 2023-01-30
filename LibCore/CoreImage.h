#pragma once
#ifndef Coreimage_h
#define Coreimage_h

/*****************************************************************************
* @author : xiaoteng
* @date : 2020/12/12 14:40
* @last change : 
* @description : 图像的基础定义
*****************************************************************************/
class CoreImage
{
public:
	void SetValue(int channal,int width,int height,int step,char *data);

public:
	//图像通道
	int channal_;
	//宽	
	int width_;
	//高
	int height_;
	//每行字节数
	int imagestep_;
	//图像数据
	char *imagedata_;
};
#endif