#ifndef CGEOPOLYGON_H
#define CGEOPOLYGON_H

#include "BaseGeo.h"
#include <QMenu>
#include <QAction>

class LIBIMAGEVIEW_API GeoPolygon : public BaseGeo
{
    Q_OBJECT
public:
    GeoPolygon();
    GeoPolygon(BaseGeo* geo);

    virtual ~GeoPolygon(){};
    virtual bool checkInGeo(QPoint, bool);
    virtual bool checkActive(QPoint point);
    virtual bool checkAjust(QPoint position, QPoint left_top, QPoint point,double scale=1);
    virtual bool checkMove(QPoint point);
    virtual void ajust(QPoint distance);
    virtual void move(QPoint distance);

    virtual void draw(QPainter &painter,QPoint topleft,double scale);

    //新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
    virtual bool drawNewGeomety(QPoint ,E_MouseState );

    //激活状态右键事件
    virtual bool rightButtonDown(QPoint, QPoint, QPoint, double);

    virtual void reset();
	void cacuRect();
	virtual QRect getRect();

public slots:

    void DeletePoint();

    void AddPoint();
  
private:
    bool checkInLine(QPoint point,QPoint point1,QPoint point2, double scale);

private:
	QMenu menu;
    QAction add_action_;
	QAction delete_action;

    int operation_point_index_;
};

#endif // CGEOPOLYGON_H
