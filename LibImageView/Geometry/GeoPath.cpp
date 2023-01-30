#include "GeoPath.h"
#include <QPainter>
#include <QDebug>
GeoPath::GeoPath() :BaseGeo()
{
    rect_ = QRect(0,0,0,0);
    ajust_point_index_ = -1;

    type_ = E_Path;
    m_quadMode = false;
    mouseDown = false;
}

GeoPath::GeoPath(BaseGeo* geo) :BaseGeo(geo)
{
    cacuRect();
}


bool GeoPath::checkInGeo(QPoint point,bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly)) return false;
	if (!rect_.contains(point))
	{
		return false;
	}
    QPolygon polygon(points_);
    if(polygon.containsPoint(point,Qt::OddEvenFill))
    {
        return true;
    }
    return false;
}
bool GeoPath::checkActive(QPoint point)
{
    if(hide_ || show_only_) return false;
    if(m_quadMode) return actived_;

	if (!rect_.contains(point))
	{
		return false;
	}
    QPolygon polygon(points_);
    if(polygon.containsPoint(point,Qt::OddEvenFill))
    {
        setActive();
        return true;
    }

    deActive();
    return false;
}

bool GeoPath::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
	if (hide_ || show_only_) return false;

	ajust_point_index_ = -1;
	m_insertID = -1;
	QRectF guideRect(0, 0, guide_size_, guide_size_);

	for (int i = 0; i < points_.size(); i++)
	{
		guideRect.moveCenter(QPoint((points_[i].x() - left_top.x()) * scale, (points_[i].y() - left_top.y()) * scale));
		//guideRect.moveCenter(points_[i]);
		if (guideRect.contains(position))
		{
			ajust_point_index_ = i;
			return true;
		}
	}
	return false;
}
bool GeoPath::checkMove(QPoint point)
{
	if (hide_ || show_only_) return false;

	if (!rect_.contains(point))
	{
		return false;
	}
	QPolygon polygon(points_);
	if (polygon.containsPoint(point, Qt::OddEvenFill))
	{
		return true;
	}
	return false;
}
void GeoPath::ajust(QPoint distance)
{
    if(hide_ || show_only_) 
		return;

    if(ajust_point_index_>=0 && ajust_point_index_<points_.size())
    {
        points_[ajust_point_index_].setX(points_[ajust_point_index_].x()+distance.x());
        points_[ajust_point_index_].setY(points_[ajust_point_index_].y()+distance.y());
    }
    cacuRect();
    emit signal_geoChanged();
}
void GeoPath::move(QPoint distance)
{
    if(hide_ || show_only_) return;
    if(m_quadMode) return;


	for (int i = 0; i < points_.size(); i++)
	{
		if (points_[i].x() + distance.x() < 0
			|| points_[i].x() + distance.x() >= image_size_.width()
			|| points_[i].y() + distance.y() < 0
			|| points_[i].y() + distance.y() > image_size_.height())
		{
			return;
		}
	}

	

    for(int i=0;i<points_.size();i++)
    {
        points_[i].setX(points_[i].x()+distance.x());
        points_[i].setY(points_[i].y()+distance.y());
    }
    rect_.adjust(distance.x(),distance.y(),distance.x(),distance.y());
    emit signal_geoChanged();
}

void GeoPath::draw(QPainter &painter,QPoint topleft,double scale)
{
    if(hide_) return;

    painter.save();
    painter.scale(scale, scale);
	float pensize = 2;
	if (actived_)
	{
		pensize = 3;
	}   

    QFont font;
    font.setPointSizeF(12/scale);
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing,0);
    painter.setFont(font);

    QFontMetricsF fontMetrics(font);
    //qreal wid = fontMetrics.width("1");
    qreal height = fontMetrics.height();
	qreal wid = height;

 
	if (actived_)
	{
		painter.setPen(QPen(actived_color_, pensize / scale));
	}
	else
	{
		painter.setPen(QPen(color_, pensize / 2 / scale));
	}
	for (int i = 0; i < points_.size(); i++)
	{
		int next_index = i + 1;
		if (next_index < points_.size())
		{
			painter.drawLine(QPointF(points_[i].x() - topleft.x(), points_[i].y() - topleft.y()),
				QPointF(points_[next_index].x() - topleft.x(), points_[next_index].y() - topleft.y()));
		}
	}

	if (actived_)
	{
		painter.setPen(QPen(actived_color_, pensize / scale));
        painter.setBrush(QBrush(Qt::red));
	}
	else
	{
		painter.setPen(QPen(color_, pensize / 2 / scale));
        painter.setBrush(QBrush(color_));
	}

	QRectF guideRect(0, 0, guide_size_ / scale, guide_size_ / scale);
	
    for(int i=0;i<points_.size();i++)
    {	      
		/*   painter.drawEllipse(QPointF(points_[i].x() - topleft.x(), points_[i].y() - topleft.y()),
			   guide_size_ / scale,
			   guide_size_ / scale);*/
		if (actived_)
		{
			guideRect.moveCenter(QPoint(points_[i].x() - topleft.x(), points_[i].y() - topleft.y()));
			painter.fillRect(guideRect, Qt::red);

			painter.drawText(points_[i].x() - topleft.x() - wid / 2,
				points_[i].y() - topleft.y() + height, QString::number(i));
		}
    }
    painter.setBrush(Qt::NoBrush);

    if(m_quadMode && points_.size()>2)
    {
        if(actived_)
        {
            painter.setPen(QPen(actived_color_, 1/scale));
        }
        else
        {
            painter.setPen(QPen(color_, 0.5/scale));
        }

      
        for(int i=1;i<points_.size();i++)
        {
            painter.drawLine(QPointF(points_[i].x()-topleft.x(),points_[i].y()-topleft.y()),
                             QPointF(points_[i-1].x()-topleft.x(),points_[i-1].y()-topleft.y()));
        }
     

        painter.drawLine(QPointF(points_[0].x()-topleft.x(),points_[0].y()-topleft.y()),
                QPointF(points_[points_.size()-1].x()-topleft.x(),points_[points_.size()-1].y()-topleft.y()));
    }

    painter.restore();
}

void GeoPath::cacuRect()
{
	int xmin = 100000;
	int ymin = 100000;
	int xmax = 0;
	int ymax = 0;
	for (int i = 0; i < points_.size(); i++)
	{
		if (points_[i].x() < xmin) xmin = points_[i].x();
		if (points_[i].x() > xmax) xmax = points_[i].x();
		if (points_[i].y() < ymin) ymin = points_[i].y();
		if (points_[i].y() > ymax) ymax = points_[i].y();
	}
	rect_.setRect(xmin, ymin, xmax - xmin, ymax - ymin);
}
QRect GeoPath::getRect()
{ 
	return rect_;
}


//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoPath::drawNewGeomety(QPoint point, E_MouseState state)
{
	if (state == E_LDown)
	{
		if (!mouseDown)
		{
			if (!m_quadMode)
				points_.clear();
			mouseDown = true;
			drawing_ = true;
		}
		return false;
	}
	else if (mouseDown && state == E_MouseUp)
	{
		points_.push_back(point);
		cacuRect();
		emit signal_geoChanged();
		if (m_quadMode && points_.size() > 3)
		{
			mouseDown = false;
			drawing_ = false;
			return true;
		}
		return false;
	}
	else if (mouseDown && state == E_RDown)
	{
		mouseDown = false;
		drawing_ = false;
		return true;
	}
	else if (mouseDown && state == E_Move)
	{
		return false;
	}

	return false;
}
