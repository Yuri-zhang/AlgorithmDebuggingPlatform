#ifndef CGEOPOINTS_H
#define CGEOPOINTS_H

#include "BaseGeo.h"

class LIBIMAGEVIEW_API GeoPath : public BaseGeo
{
    Q_OBJECT
public:
    GeoPath();
    GeoPath(BaseGeo* geo);
    virtual ~GeoPath(){};
    virtual bool checkInGeo(QPoint, bool);
    virtual bool checkActive(QPoint point);
    virtual bool checkAjust(QPoint position, QPoint left_top, QPoint point,double scale=1);
    virtual bool checkMove(QPoint point);
    virtual void ajust(QPoint distance);
    virtual void move(QPoint distance);

    virtual void draw(QPainter &painter,QPoint topleft,double scale);

	//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
    virtual bool drawNewGeomety(QPoint, E_MouseState);

    void setQuadMode( bool addmode = true)
    {
        m_quadMode = addmode;
    }

    void updatePoints(QVector<QPoint> &points)
    {
        points_.clear();
        points_.append(points);
		cacuRect();
    }
	void cacuRect();
	virtual QRect getRect();
  

};

#endif // CGEOPOINTS_H
