#ifndef CGEOPOINT_H
#define CGEOPOINT_H

#include "BaseGeo.h"

class QDomDocument;
class QDomElement;
class LIBIMAGEVIEW_API GeoPoint : public BaseGeo
{
    Q_OBJECT
public:
    GeoPoint(int x=0, int y=0);
    GeoPoint(BaseGeo* geo);

    virtual ~GeoPoint(){};
    virtual bool checkInGeo(QPoint, bool);
    //检查当前集合体是否被激活，参数为鼠标的像素位置
    virtual bool checkActive(QPoint);
    virtual bool checkMove(QPoint point);
    virtual void move(QPoint distance);

    //更新颜色
    virtual void updateColor();
    //检查是否调整外形，第一个参数为鼠标的像素位置，第二个参数为图像显示比例
    virtual bool checkAjust(QPoint,QPoint, QPoint ,double ){ return false;};
    //调整外形，参数为待调整的像素距离
    virtual void ajust(QPoint ){};
    virtual void draw(QPainter &painter,QPoint topleft,double scale);

    //新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
    virtual bool drawNewGeomety(QPoint ,E_MouseState );

	virtual QRect getRect();
  
};

#endif // CGEOPOINT_H
