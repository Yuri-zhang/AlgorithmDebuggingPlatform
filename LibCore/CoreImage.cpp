#include "pch.h"
#include "CoreImage.h"
#include <stdio.h>
// CoreImage::CoreImage()
// {
// 	channal_ = 1;
// 	imagestep_ = 0;
// 	width_ = 0;
// 	height_ = 0;
// 	imagedata_ = NULL;
// }
// 
// 
// CoreImage::~CoreImage()
// {
// 
// }

void CoreImage::SetValue(int channal, int width, int height, int step, char *data)
{
	channal_ = channal;
	width_ = width;
	height_ = height;
	imagestep_ = step;
	imagedata_ = data;	
}

