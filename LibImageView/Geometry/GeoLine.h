#ifndef CGEOLINE_H
#define CGEOLINE_H

#include "BaseGeo.h"

class LIBIMAGEVIEW_API GeoLine : public BaseGeo
{
    Q_OBJECT
public:
    GeoLine(BaseGeo* geo);
    GeoLine();

    virtual ~GeoLine(){};
    virtual bool checkInGeo(QPoint, bool);
    //检查当前集合体是否被激活，参数为鼠标的像素位置
    virtual bool checkActive(QPoint);

    //检查是否调整外形，第一个参数为鼠标的像素位置，第二个参数为图像显示比例
    virtual bool checkAjust(QPoint position, QPoint left_top, QPoint ,double );

    //检查是否移动几何体，参数为鼠标的像素位置
    virtual bool checkMove(QPoint );

    //调整外形，参数为待调整的像素距离
    virtual void ajust(QPoint );

    //移动几何体，参数为待移动的像素距离
    virtual void move(QPoint );

    virtual void draw(QPainter &painter,QPoint topleft,double scale);

    //新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
    virtual bool drawNewGeomety(QPoint ,E_MouseState );

    void getCenter();

    virtual QRect getRect();
 
};

#endif // CGEOLINE_H
