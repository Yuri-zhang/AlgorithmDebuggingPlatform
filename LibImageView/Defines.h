#pragma once

#define RectMeasureString "#$#RectMeasure"
#define RectDrawString "#$#RectDraw"
#define CircleDrawString "#$#CircleDraw"
#define EllipseDrawString "#$#EllipseDraw"
#define PolyDrawString "#$#PolyDraw"
#define MeasureAlgName "测量"
#ifdef LIB_IMAGEVIEW
#define LIBIMAGEVIEW_API __declspec(dllexport)
#else
#define LIBIMAGEVIEW_API __declspec(dllimport)
#endif


namespace ImageViewDefine
{
	enum EImageOpsType
	{
		e_Auto,
		e_ImageType,
		e_GeosType,
	};

	enum E_MouseState
	{
		E_LDown,
		E_MouseUp,
		E_Move,
		E_RDown,
	};

	enum E_ResizeMode
	{
		E_RectResize_none,
		E_RectResize_top,
		E_RectResize_bottom,
		E_RectResize_left,
		E_RectResize_right,
		E_RectResize_topleft,
		E_RectResize_bottomleft,
		E_RectResize_topright,
		E_RectResize_bottomright,	
		E_ORectResize_top,
		E_ORectResize_bottom,
		E_ORectResize_left,
		E_ORectResize_right,
		E_ORectResize_topleft,
		E_ORectResize_bottomleft,
		E_ORectResize_topright,
		E_ORectResize_bottomright,
		E_ORectMove,
		E_Resize_x,
		E_Resize_y,
		E_Resize_angle,
		E_Arc_BeginAngle,
		E_Arc_EndAngle,
	};
}