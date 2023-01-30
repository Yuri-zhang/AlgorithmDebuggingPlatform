#ifndef CGEOMETRYELEMENT_H
#define CGEOMETRYELEMENT_H

static int G_Transparent_Rate = 100;

#include "../Defines.h"
#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QVector>

enum GEOMETRYTYPE
{
	E_unknownGeo,
	E_Point,
	E_Ellipse,
	E_Circle,
	E_Line,
	E_Rect,	
	E_Path,
	E_Polygon,
	E_Arraw,
	E_Arc,
};

using namespace ImageViewDefine;
class LIBIMAGEVIEW_API BaseGeo :public QObject
{
    Q_OBJECT
public:
	BaseGeo();
    BaseGeo(BaseGeo *geo);
    virtual ~BaseGeo(){};
    //激活当前集合体
    virtual void setActive(bool active=true);

    //取消激活
    virtual void deActive();

    //绘制几何体，第一个参数为绘图对象，第二个为图像在绘图区域的偏置，第三个为图像显示放大系数
    virtual void draw(QPainter &,QPoint ,double ){};

    //更新颜色
    virtual void updateColor(){};

    //检查当前点是否在几何体内
    virtual bool checkInGeo(QPoint,bool){return false;};

    //检查当前集合体是否被激活，参数为鼠标的像素位置
    virtual bool checkActive(QPoint){return false;};

    //检查是否调整外形，第一个参数为鼠标的像素位置，第二个参数为鼠标的像素位置，第三个参数为鼠标的像素位置，第四个参数为图像显示比例
    virtual bool checkAjust(QPoint, QPoint,QPoint ,double ){ return false;};

    //检查是否移动几何体，参数为鼠标的像素位置
    virtual bool checkMove(QPoint ){ return false;};

    //调整外形，参数为待调整的像素距离
    virtual void ajust(QPoint ){};

    //移动几何体，参数为待移动的像素距离
    virtual void move(QPoint ){};

    //新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
    virtual bool drawNewGeomety(QPoint ,E_MouseState ){return true;}

    //激活状态右键事件
    virtual bool rightButtonDown(QPoint, QPoint, QPoint, double){return false;};

	virtual QRect getRect() { return QRect(); };
	//从多个相交的几何体中筛选一个激活几何体
	static BaseGeo* selectIntersectionGeos(QVector<BaseGeo*> geos, QPoint cursorPos);

    virtual void reset();

	void clearPoints();

	virtual void addPoint(int x, int y);

	virtual void setRect(int x, int y, int w, int h);

	virtual void setRect(QRect rect);

	virtual void setPoints(QVector<QPoint> points);

	virtual void cacuRect();

	//将数据限制在区域内
	bool regionLimit(QRect region);

	//设置正常显示时的颜色
	void setColor(QColor color);

	//设置激活状态的颜色
	void setActivedColor(QColor color);

	//设置图形内显示文本
	void setText(QString Text);

	//设置tooltip
	void setToolTip(QString Text);

	//设置只显示或可以被修改
	void setShowOnly(bool);

	//设置隐藏状态
	void setHide(bool hide = true);


	//是否被激活
	bool isActive();


	//判断是否为同一几何体
	bool sameData(BaseGeo* data);

	void setLimitRegion(QRect limitRegion);

	QRect m_limitRegion;//限制区域

	void SetImageSize(QSize size);

	void Copy(BaseGeo* geo);

signals:
	void signal_GeoViewChanged();
	void signal_RegionLimited();

public:
	QString id_;
	QRect rect_;                   //区域数据，矩形、圆、椭圆使用
	QRect bound_rect_;				//限制区域，只能在当前区域内部调整
	QVector<QPoint> points_;       //点集数据
	QPoint point_;
	double angle_;                 //旋转角度
	double begin_angle_;           //开始角度，适用于度  
	double end_angle_;				//结束角度，适用于度  
	QString text_;                 //图形内显示的文本，一直存在
	QString toolTip_;              //tooltip文本，鼠标悬停时显示
	GEOMETRYTYPE type_;            //几何体类型
	QSize image_size_;
	bool actived_;                 //是否被激活

    bool hide_;            //为true时不显示
    bool show_only_;        //只显示，不可编辑
    bool drawing_;

    QColor color_;         //常规颜色
    QColor actived_color_;  //激活时的颜色
	QRectF show_only_rect_;  //只显状态显示的矩形，区域过小时会放大显示

	E_ResizeMode resize_mode_;

	QPointF center_;

	double r_x_;

	double r_y_;

	int ajust_point_index_;//待调整点ID   

	bool m_quadMode;//四边形区域模式，标定模块使用

	bool mouseDown;

	bool created_;

	double scale_;

	int m_insertID;//待填加点ID

	QPoint m_insertPoint;//待填加点

	QPointF point1_;

	QPointF point2_;

	double radius_;

	int guide_size_;

	static int G_LimitImageRect;
signals:
    void signal_geoChanged();
};

#endif // CGEOMETRYELEMENT_H
