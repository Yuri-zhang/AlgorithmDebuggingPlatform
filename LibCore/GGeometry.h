#pragma once
/*****************************************************************************
* @author : xiaoteng
* @date : 2021/6/21 16:27
* @last change : 
* @description : 一般图形定义
*****************************************************************************/
#include <vector>
struct GPoint {
	int x;
	int y;
	GPoint(int nX = 0, int nY = 0)
	{
		x = nX;
		y = nY;
	}

	GPoint &operator=(const GPoint pt)
	{
		this->x = pt.x;
		this->y = pt.y;
		return *this;
	}

};

struct GPoints 
{
	std::vector<GPoint*> points_;
	GPoints()
	{
		points_.clear();
	}

	GPoints& operator=(const GPoints pts)
	{
		this->points_ = pts.points_;
		return *this;
	}

};




struct GRect {
	int left;
	int top;
	int right;
	int bottom;
	GRect() {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
	GRect(int left, int top, int right, int bottom)
	{
		left = left;
		top = top;
		right = right;
		bottom = bottom;
	}
	int Width()
	{
		return right - left;
	}
	int Height()
	{
		return bottom - top;
	}
	GRect &operator=(const GRect &rect)
	{
		this->left= rect.left;
		this->top = rect.top;
		this->right = rect.right;
		this->bottom = rect.bottom;
		return *this;
	}

	int PtInRect(GPoint pt)
	{
		return (pt.x >= left) && (pt.x <= right) && (pt.y >= top) && (pt.y <= bottom);
	}
};


//支持椭圆
struct GCircle {
	int x_;
	int y_;
	int width;
	int height;
	GCircle(int nX = 0, int nY = 0, int nWidth = 0, int nHeight = 0)
	{
		x_ = nX;
		y_ = nY;
		width = nWidth;
		height = nHeight;
	}

	GCircle &operator=(const GCircle &rect)
	{
		this->x_ = rect.x_;
		this->y_ = rect.y_;
		this->width = rect.width;
		this->height = rect.height;
		return *this;
	}
};



struct GDRect {
	GRect inside_rect_;
	GRect outside_rect_;
	GDRect()
	{
		inside_rect_ = GRect(0, 0, 0, 0);
		outside_rect_ = GRect(0, 0, 0, 0);
	}
	GDRect(GRect insideRect, GRect outsideRect)
	{
		inside_rect_ = insideRect;
		outside_rect_ = outsideRect;
	}

	GDRect &operator=(const GDRect &dRect)
	{
		this->inside_rect_ = dRect.inside_rect_;
		this->outside_rect_ = dRect.outside_rect_;
		return *this;
	}
};




struct GSize {
	int width_;
	int height_;
	GSize(int nwidth = 0, int nheight = 0)
	{
		width_ = nwidth;
		height_ = nheight;
	}

	GSize &operator=(const GSize size)
	{
		width_ = size.width_;
		height_ = size.height_;
		return *this;
	}
};