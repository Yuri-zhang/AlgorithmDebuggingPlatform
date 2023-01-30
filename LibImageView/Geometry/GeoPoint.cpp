#include "GeoPoint.h"
#include <QPainter>
GeoPoint::GeoPoint(int x, int y) :BaseGeo()
{
    point_.setX(0);
    point_.setY(0);
    scale_ = 1;
    type_ = E_Point;
    addPoint(x, y);
}

GeoPoint::GeoPoint(BaseGeo* geo) :BaseGeo(geo)
{
	type_ = E_Point;
    show_only_ = geo->show_only_;

}

bool GeoPoint::checkInGeo(QPoint point,bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly)) return false;
    QRectF guideRect(0,0, guide_size_ /scale_, guide_size_ /scale_);
    guideRect.moveCenter(point_);

    if(guideRect.contains(point))
    {
        return true;
    }
    return false;
}

bool GeoPoint::checkActive(QPoint point)
{
	if (hide_ || show_only_) return false;

    QRectF guideRect(0,0, guide_size_ /scale_, guide_size_ /scale_);
    guideRect.moveCenter(point_);

    if(guideRect.contains(point))
    {
        setActive();
        return true;
    }
    deActive();
    return false;
}


bool GeoPoint::checkMove(QPoint point)
{
	if (hide_ || show_only_) return false;

    QRectF guideRect(0,0,8/scale_,8/scale_);
    guideRect.moveCenter(point_);

    if(guideRect.contains(point))
    {
        return true;
    }
    return false;
}


void GeoPoint::move(QPoint distance)
{
	if (hide_ || show_only_) return;

	if (point_.x() + distance.x() < 0
		|| point_.x() + distance.x() >= image_size_.width()
		|| point_.y() + distance.y() < 0
		|| point_.y() + distance.y() > image_size_.height())
	{
		return;
	}

    point_ += distance;
    emit signal_geoChanged();
}


//更新颜色
void GeoPoint::updateColor()
{   
}


void GeoPoint::draw(QPainter &painter,QPoint topleft,double scale)
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

	painter.setPen(QPen(Qt::white, pensize / scale));
	painter.drawEllipse(QPointF(point_.x() - topleft.x(), point_.y() - topleft.y()), 1, 1);

    if(actived_)
    {
        painter.setPen(QPen(Qt::red, pensize /scale));
    }
    else
    {
        painter.setPen(QPen(color_, pensize /scale));
    }

    painter.drawLine(QPointF(point_.x()-topleft.x()-guide_size_/2,point_.y()-topleft.y()),
                     QPointF(point_.x()-topleft.x()+ guide_size_ /2,point_.y()-topleft.y()));
    
    painter.drawLine(QPointF(point_.x()-topleft.x(),point_.y()-topleft.y()- guide_size_ /2),
                     QPointF(point_.x()-topleft.x(),point_.y()-topleft.y()+ guide_size_ /2));
   

    QFont font;
    font.setPointSizeF(12/scale);
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing,0);
    painter.setFont(font);

    QFontMetricsF fontMetrics(font);
    //qreal wid = fontMetrics.width(text_);
    qreal height = fontMetrics.height();
	qreal wid = height * text_.length();

    painter.drawText(point_.x()-topleft.x() - wid/2,point_.y()-topleft.y() + height,text_);

    painter.restore();
}


//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoPoint::drawNewGeomety(QPoint point ,E_MouseState state)
{
    if(state == E_LDown)
    {
        point_ = point;
        emit signal_geoChanged();
        return true;
    }

    return false;
}
QRect GeoPoint::getRect()
{
	return QRect(point_.x() - 5, point_.y() - 5, 10, 10);
}