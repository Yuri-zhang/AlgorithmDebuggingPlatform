#include "GeoLine.h"
#include <QPainter>
#define PI 3.1415927

GeoLine::GeoLine() :BaseGeo()
{
    point1_ = QPointF(0,0);
    point2_ = QPointF(0,0);
    type_ = E_Line;
    ajust_point_index_ = -1;
}


GeoLine::GeoLine(BaseGeo* geo) :BaseGeo(geo)
{
	point1_ = geo->point1_;
	point2_ = geo->point2_;
	type_ = E_Line;
	ajust_point_index_ = geo->ajust_point_index_;
}


bool GeoLine::checkInGeo(QPoint point,bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly)) return false;
    getCenter();
    double width = sqrt((point1_.x()-point2_.x())*(point1_.x()-point2_.x())+
                        (point1_.y()-point2_.y())*(point1_.y()-point2_.y()));
    QRectF contourRect;
    contourRect.setRect(center_.x()-width/2,center_.y()- guide_size_ /scale_,width, guide_size_ /scale_);

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

bool GeoLine::checkActive(QPoint point)
{
    if(hide_) return false;

    getCenter();
    double width = sqrt((point1_.x()-point2_.x())*(point1_.x()-point2_.x())+
                        (point1_.y()-point2_.y())*(point1_.y()-point2_.y()));
    QRectF contourRect;
    contourRect.setRect(center_.x()-width/2,center_.y()- guide_size_ /scale_,width, guide_size_ /scale_);

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
bool GeoLine::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
    if(hide_) return false;

    QRectF guideRect(0,0, guide_size_, guide_size_);

    QPointF pt1 = QPointF((point1_.x() - left_top.x()) * scale, (point1_.y() - left_top.y()) * scale);
    QPointF pt2 = QPointF((point2_.x() - left_top.x()) * scale, (point2_.y() - left_top.y()) * scale);

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


bool GeoLine::checkMove(QPoint point)
{
    if(hide_) return false;

    getCenter();
    double width = sqrt((point1_.x()-point2_.x())*(point1_.x()-point2_.x())+
                        (point1_.y()-point2_.y())*(point1_.y()-point2_.y()));
    QRectF contourRect;
    contourRect.setRect(center_.x()-width/2,center_.y()- guide_size_ /scale_,width, guide_size_ /scale_);

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
void GeoLine::ajust(QPoint distance)
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
void GeoLine::move(QPoint distance)
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

void GeoLine::draw(QPainter &painter,QPoint topleft,double scale)
{
    if(hide_) return;

    painter.save();
    painter.scale(scale, scale);

    scale_ = scale;

	float pensize = 2;
	if (actived_)
	{
		pensize = 3;
	}
    painter.setPen(QPen(color_, pensize /scale));

    if(actived_)
    {
        painter.setPen(QPen(actived_color_, pensize /scale));
    }
    painter.drawLine(QPointF(point1_.x()-topleft.x(),point1_.y()-topleft.y()),
                     QPointF(point2_.x()-topleft.x(),point2_.y()-topleft.y()));

    

    if(actived_)
    {
        painter.setPen(QPen(Qt::red, pensize /scale));
		painter.setBrush(QBrush(Qt::white));
		painter.drawEllipse(QPointF(point1_.x() - topleft.x(), point1_.y() - topleft.y()), guide_size_/2/scale_, guide_size_ /2/scale_);
		painter.drawEllipse(QPointF(point2_.x() - topleft.x(), point2_.y() - topleft.y()), guide_size_/2/scale_ , guide_size_/2/scale_ );
		painter.setBrush(Qt::NoBrush);
    }
    else
    {
        painter.setPen(QPen(color_, pensize / scale));
    }

  

    painter.setPen(QPen(color_, pensize /scale));

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
		qreal wid = height * text_.length();
        //文字画在（x，y）这个点的左边，（x，y）在文字的中间

     
        QPointF pos = QPointF((point1_.x() + point2_.x()) / 2, (point1_.y() + point2_.y()) / 2);
        painter.drawText(pos.x()-topleft.x() - wid/2,pos.y()-topleft.y() + height,text_);
    }
    painter.restore();
}

//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoLine::drawNewGeomety(QPoint point, E_MouseState state)
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
void GeoLine::getCenter()
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



QRect GeoLine::getRect()
{
    int left = std::min(point1_.x(), point2_.x());
    int right= std::max(point1_.x(), point2_.x());
	int top = std::min(point1_.y(), point2_.y());
	int bottom = std::max(point1_.y(), point2_.y());

    return QRect(left, top, right - left, bottom - top);
}