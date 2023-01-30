#include "GeoArraw.h"
#include <QPainter>
#define PI 3.1415927

GeoArraw::GeoArraw() :BaseGeo()
{
    point1_ = QPointF(0,0);
    point2_ = QPointF(0,0);
    type_ = E_Arraw;
    ajust_point_index_ = -1;
}


GeoArraw::GeoArraw(BaseGeo* geo) :BaseGeo(geo)
{
	point1_ = geo->point1_;
	point2_ = geo->point2_;
	type_ = E_Arraw;
	ajust_point_index_ = geo->ajust_point_index_;
}


bool GeoArraw::checkInGeo(QPoint point,bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly)) return false;
    getCenter();
    double width = sqrt((point1_.x()-point2_.x())*(point1_.x()-point2_.x())+
                        (point1_.y()-point2_.y())*(point1_.y()-point2_.y()));
    QRectF contourRect;
    contourRect.setRect(center_.x()-width/2,center_.y()-4/scale_,width,8/scale_);

    double xx= (point.x() - center_.x())*cos(angle_ / 180 * PI)
             - (point.y() - center_.y())*sin(angle_ / 180 * PI) + center_.x() ;

    double yy= (point.x() - center_.x())*sin(angle_ / 180 * PI)
             + (point.y() - center_.y())*cos(angle_ / 180 * PI) + center_.y() ;

    if(contourRect.contains(QPointF(xx,yy)))
    {
        return true;
    }

    return false;
}

bool GeoArraw::checkActive(QPoint point)
{
    if(hide_) return false;

    getCenter();
    double width = sqrt((point1_.x()-point2_.x())*(point1_.x()-point2_.x())+
                        (point1_.y()-point2_.y())*(point1_.y()-point2_.y()));
    QRectF contourRect;
    contourRect.setRect(center_.x()-width/2,center_.y()-4/scale_,width,20/scale_);

    double xx= (point.x() - center_.x())*cos(angle_ / 180 * PI)
             - (point.y() - center_.y())*sin(angle_ / 180 * PI) + center_.x() ;

    double yy= (point.x() - center_.x())*sin(angle_ / 180 * PI)
             + (point.y() - center_.y())*cos(angle_ / 180 * PI) + center_.y() ;

    if(contourRect.contains(QPointF(xx,yy)))
    {
        setActive();
        return true;
    }

    deActive();
    return false;
}


bool GeoArraw::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
    if(hide_) return false;

    QRectF guideRect(0,0, guide_size_, guide_size_);

    QPointF pt1 = QPoint((point1_.x() - left_top.x()) * scale, (point1_.y() - left_top.y()) * scale);
    QPointF pt2 = QPoint((point2_.x() - left_top.x()) * scale, (point2_.y() - left_top.y()) * scale);


    guideRect.moveCenter(pt1);
    if(guideRect.contains(position))
    {
        ajust_point_index_ = 1;
        return true;
    }
    guideRect.moveCenter(pt2);
    if(guideRect.contains(position))
    {
        ajust_point_index_ = 2;
        return true;
    }
    ajust_point_index_ = -1;
    return false;
}


bool GeoArraw::checkMove(QPoint point)
{
    if(hide_) 
        return false;

    getCenter();
    double width = sqrt((point1_.x()-point2_.x())*(point1_.x()-point2_.x())+
                        (point1_.y()-point2_.y())*(point1_.y()-point2_.y()));
    QRectF contourRect;
    contourRect.setRect(center_.x()-width/2,center_.y()-4/scale_,width,8/scale_);

    double xx= (point.x() - center_.x())*cos(angle_ / 180 * PI)
             - (point.y() - center_.y())*sin(angle_ / 180 * PI) + center_.x() ;

    double yy= (point.x() - center_.x())*sin(angle_ / 180 * PI)
             + (point.y() - center_.y())*cos(angle_ / 180 * PI) + center_.y() ;

    if(contourRect.contains(QPointF(xx,yy)))
    {
        return true;
    }

    return false;
}


void GeoArraw::ajust(QPoint distance)
{
    if(hide_) return;


    if(ajust_point_index_==1)
    {
        if (G_LimitImageRect)
		{
			if (point1_.x() + distance.x() < 0
				|| point1_.x() + distance.x() >= image_size_.width()
				|| point1_.y() + distance.y() < 0
				|| point1_.y() + distance.y() > image_size_.height())
			{
				return;
			}
        }
		

        point1_.setX(point1_.x()+distance.x());
        point1_.setY(point1_.y()+distance.y());
    }
    else if(ajust_point_index_==2)
	{
        if (G_LimitImageRect)
        {
            if (point2_.x() + distance.x() < 0
                || point2_.x() + distance.x() >= image_size_.width()
                || point2_.y() + distance.y() < 0
                || point2_.y() + distance.y() > image_size_.height())
            {
                return;
            }
        }

        point2_.setX(point2_.x()+distance.x());
        point2_.setY(point2_.y()+distance.y());
    }
    emit signal_geoChanged();
}


void GeoArraw::move(QPoint distance)
{
	if (point1_.x() + distance.x() < 0
		|| point1_.x() + distance.x() >= image_size_.width()
		|| point1_.y() + distance.y() < 0
		|| point1_.y() + distance.y() > image_size_.height())
	{
		return;
	}

	if (point2_.x() + distance.x() < 0
		|| point2_.x() + distance.x() >= image_size_.width()
		|| point2_.y() + distance.y() < 0
		|| point2_.y() + distance.y() > image_size_.height())
	{
		return;
	}


    point1_ += distance;
    point2_ += distance;
    emit signal_geoChanged();
}





void GeoArraw::draw(QPainter &painter,QPoint topleft,double scale)
{
    if(hide_) return;

    painter.save();
    painter.scale(scale, scale);

    scale_ = scale;

	QPointF source(point1_.x() - topleft.x(), point1_.y() - topleft.y());
	QPointF dest(point2_.x() - topleft.x(), point2_.y() - topleft.y());

	QLineF draw_line(source, dest);
    
    if (draw_line.length()==0)
	{
		painter.restore();
        return;
    }     

	float pensize = 2;
	QPen pen;
	if (actived_)
	{
		pen = QPen(actived_color_, pensize / scale);
	
	}
	else
	{
		pen = QPen(color_, pensize / scale);		
	}


	painter.setPen(pen);

    if (actived_)
	{
		painter.setBrush(QBrush(actived_color_));
    }
    else
    {
        painter.setBrush(QBrush(color_));
    }

    int arraw_size = 10 / scale;


    //绘制结束箭头
    QLineF v=draw_line.unitVector();
    if (draw_line.length()> arraw_size)
	{
		v.setLength(arraw_size);
    }    
    v.translate(QPointF(draw_line.dx()-v.dx(), draw_line.dy()-v.dy()));
    QLineF n = v.normalVector();
    n.setLength(n.length() * 0.5);
    QLineF n2 = n.normalVector().normalVector();
    QPointF p1 = v.p2();
    QPointF p2 = n.p2();
    QPointF p3 = n2.p2();   
    QVector<QPointF> poly_data;
    poly_data.push_back(p1);
    poly_data.push_back(p2);
    poly_data.push_back(p3);
    painter.drawPolygon(poly_data);

   
    //绘制开始箭头
    draw_line = QLineF(dest, source);
	v = draw_line.unitVector();
	if (draw_line.length() > arraw_size)
	{
		v.setLength(arraw_size);
	}
	v.translate(QPointF(draw_line.dx() - v.dx(), draw_line.dy() - v.dy()));
	n = v.normalVector();
	n.setLength(n.length() * 0.5);
	n2 = n.normalVector().normalVector();
	p1 = v.p2();
	p2 = n.p2();
	p3 = n2.p2();
    poly_data.clear();
	poly_data.push_back(p1);
	poly_data.push_back(p2);
	poly_data.push_back(p3);
	painter.drawPolygon(poly_data);

    painter.setBrush(Qt::NoBrush);

	pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
	painter.drawLine(draw_line);

    if(!drawing_)
    {
        //设置字体、大小、字符间距等
        QFont font;
        font.setPointSizeF(12/scale);
        font.setFamily("Microsoft YaHei");
        font.setLetterSpacing(QFont::AbsoluteSpacing,0);
        painter.setFont(font);
        //获取这种字体情况下，文本的长度和高度
        QFontMetricsF fontMetrics(font);
		//qreal wid = fontMetrics.width(text_);
        qreal height = fontMetrics.height();
		qreal wid = height*text_.length();
        //文字画在（x，y）这个点的左边，（x，y）在文字的中间

        QPoint pos =QPoint((point1_.x() + point2_.x()) / 2, (point1_.y() + point2_.y()) / 2);
      
        painter.drawText(pos.x()-topleft.x() - wid/2,pos.y()-topleft.y() + height,text_);
    }
    painter.restore();
}

//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoArraw::drawNewGeomety(QPoint point, E_MouseState state)
{
    static bool mouseDown = false;
    if(state == E_LDown)
    {
        if(!mouseDown )
        {
            point1_ = point;
            point2_ = point;
            mouseDown = true;
            drawing_ = true;
            return false;
        }
        else
        {
            point2_ = point;
            mouseDown = false;
            drawing_ = false;
            emit signal_geoChanged();
            return true;
        }
    }

    return false;
}
void GeoArraw::getCenter()
{
    if(point1_.x()>point2_.x())//调整顺序，点2在右
    {
        QPointF temp = point1_;
        point1_ = point2_;
        point2_ = temp;
    }

    center_.setX((point1_.x()+point2_.x())/2.0);
    center_.setY((point1_.y()+point2_.y())/2.0);

    if(point1_.x()==point2_.x())
        angle_=90;
    else
    {
        double yy = point2_.y()-point1_.y();
        double xx = point2_.x()-point1_.x();
        angle_ = 0 - atan(yy / xx) * 180 / PI;
    }
}



QRect GeoArraw::getRect()
{
    int left = std::min(point1_.x(), point2_.x());
    int right= std::max(point1_.x(), point2_.x());
	int top = std::min(point1_.y(), point2_.y());
	int bottom = std::max(point1_.y(), point2_.y());

    return QRect(left, top, right - left, bottom - top);
}