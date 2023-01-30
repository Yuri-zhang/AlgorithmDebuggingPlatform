#ifndef ARC_H
#define ARC_H

#include "BaseGeo.h"

class LIBIMAGEVIEW_API GeoArc : public BaseGeo
{
    Q_OBJECT    
public:
    GeoArc(BaseGeo* geo);
    GeoArc(int x=0, int y=0, int w=0, int h=0);
    virtual ~GeoArc(){};

    virtual bool checkInGeo(QPoint, bool);
    virtual bool checkActive(QPoint point);
    virtual bool checkAjust(QPoint position,QPoint left_top,QPoint point,double scale=1);
    virtual bool checkMove(QPoint point);
    virtual void ajust(QPoint distance);
    virtual void move(QPoint distance);
    virtual void updateColor();
    virtual void draw(QPainter &painter,QPoint topleft,double scale);

    //新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
    virtual bool drawNewGeomety(QPoint ,E_MouseState );

	virtual QRect getRect();

    double GetAngleValue(double value);

    QPointF GetBeginAnglePosition();

    QPointF GetEndAnglePosition();

signals:

};

#endif // CGEOELLIPSE_H
