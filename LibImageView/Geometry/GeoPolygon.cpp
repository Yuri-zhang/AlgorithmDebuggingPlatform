#include "GeoPolygon.h"
#include <QPainter>
#include <QDebug>
#include <QPainterPath>

#define PI 3.1415927

GeoPolygon::GeoPolygon() :BaseGeo()
{
    rect_ = QRect(0,0,0,0);
    ajust_point_index_ = -1;
    m_insertID = -1;
    type_ = E_Polygon;
    mouseDown = false;

    add_action_.setIcon(QIcon(":/images/add.png"));
    add_action_.setText(u8"添加点");
    delete_action.setIcon(QIcon(":/images/delete.png"));
    delete_action.setText(u8"删除点");
    menu.addAction(&add_action_);
	menu.addAction(&delete_action);

    connect(&delete_action, SIGNAL(triggered(bool)), this, SLOT(DeletePoint()));
    connect(&add_action_, SIGNAL(triggered(bool)), this, SLOT(AddPoint()));
}

GeoPolygon::GeoPolygon(BaseGeo* geo) :BaseGeo(geo)
{
    rect_ = geo->rect_;
    ajust_point_index_ = geo->ajust_point_index_;
    m_insertID = geo->m_insertID;
    type_ = E_Polygon;
    points_ = geo->points_;
    mouseDown = false;
    cacuRect();
	
	add_action_.setIcon(QIcon(":/images/add.png"));
	add_action_.setText(u8"添加点");
	delete_action.setIcon(QIcon(":/images/delete.png"));
	delete_action.setText(u8"删除点");
	menu.addAction(&add_action_);
	menu.addAction(&delete_action);

	connect(&delete_action, SIGNAL(triggered(bool)), this, SLOT(DeletePoint()));
	connect(&add_action_, SIGNAL(triggered(bool)), this, SLOT(AddPoint()));
}



bool GeoPolygon::checkInGeo(QPoint point,bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly)) 
        return false;
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
bool GeoPolygon::checkActive(QPoint point)
{
    if(hide_ || show_only_) return false;

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
bool GeoPolygon::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
    if(hide_ || show_only_) return false;

    ajust_point_index_ = -1;
    m_insertID = -1;
    QRectF guideRect(0,0,guide_size_ ,guide_size_);

    for(int i=0;i<points_.size();i++)
    {
        guideRect.moveCenter(QPoint((points_[i].x()  - left_top.x()) * scale, (points_[i].y() - left_top.y()) * scale));
        //guideRect.moveCenter(points_[i]);
        if(guideRect.contains(position))
        {
            ajust_point_index_ = i;
            return true;
        }
    }	
    return false;
}
bool GeoPolygon::checkMove(QPoint point)
{
    if(hide_ || show_only_) return false;

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
void GeoPolygon::ajust(QPoint distance)
{
    if(hide_ || show_only_)
        return;

    if(m_insertID >= 0)
    {
        points_.insert(m_insertID,m_insertPoint);
        ajust_point_index_ = m_insertID;
        m_insertID = -1;
    }

    if(ajust_point_index_>=0 && ajust_point_index_<points_.size())
    {

        if (G_LimitImageRect)
        {
			if (points_[ajust_point_index_].x() + distance.x() < 0
				|| points_[ajust_point_index_].x() + distance.x() >= image_size_.width()
				|| points_[ajust_point_index_].y() + distance.y() < 0
				|| points_[ajust_point_index_].y() + distance.y() > image_size_.height())
			{
				return;
			}
        }

        points_[ajust_point_index_].setX(points_[ajust_point_index_].x()+distance.x());
        points_[ajust_point_index_].setY(points_[ajust_point_index_].y()+distance.y());
    }
	cacuRect();
    emit signal_geoChanged();
}
void GeoPolygon::move(QPoint distance)
{
    if(hide_ || show_only_) return;


    for (int i = 0; i < points_.size(); i++)
	{
		if (points_[i].x() + distance.x() < 0
			|| points_[i].x() + distance.x() >= image_size_.width()
			|| points_[i].y() + distance.y() < 0
			|| points_[i].y() + distance.y() > image_size_.height())
		{
			return;
		}

		if (points_[i].x() + distance.x() <= bound_rect_.x()
			|| points_[i].x() + distance.x() > bound_rect_.width() + bound_rect_.x()
			|| points_[i].y() + distance.y() <= bound_rect_.y()
			|| points_[i].y() + distance.y() > bound_rect_.height() + bound_rect_.y())
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

void GeoPolygon::draw(QPainter &painter,QPoint topleft,double scale)
{
    if(hide_) return;

    painter.save();
    painter.scale(scale, scale);
	float pensize = 2;
	if (actived_)
	{
		pensize = 3;
	}
 
	if (id_ == PolyDrawString)
	{
		QPen pen = QPen(QColor(251, 252, 253), pensize / scale);
		pen.setStyle(Qt::SolidLine);
		painter.setPen(pen);
	}
	else   if(actived_)
    {
        painter.setPen(QPen(actived_color_, pensize /scale));
    }
    else
    {
        painter.setPen(QPen(color_, pensize /scale));
    }


    for(int i=1;i<points_.size();i++)
    {
        painter.drawLine(QPointF(points_[i].x()-topleft.x(),points_[i].y()-topleft.y()),
                         QPointF(points_[i-1].x()-topleft.x(),points_[i-1].y()-topleft.y()));

	
    }
    if(points_.size()>2)
    {
        if(drawing_)
        {
            painter.setPen(QPen(Qt::red, pensize /scale));
        }
        painter.drawLine(QPointF(points_[0].x()-topleft.x(),points_[0].y()-topleft.y()),
                QPointF(points_[points_.size()-1].x()-topleft.x(),points_[points_.size()-1].y()-topleft.y()));	
    }

    if (id_ == PolyDrawString)
	{
		

		QPen pen = QPen(QColor(0, 120, 215), pensize / scale);
		pen.setStyle(Qt::DotLine);
		painter.setPen(pen);

		for (int i = 1; i < points_.size(); i++)
		{		
			painter.drawLine(QPointF(points_[i].x() - topleft.x(), points_[i].y() - topleft.y()),
				QPointF(points_[i - 1].x() - topleft.x(), points_[i - 1].y() - topleft.y()));
		}

		if (points_.size() > 2)
		{		
			painter.drawLine(QPointF(points_[0].x() - topleft.x(), points_[0].y() - topleft.y()),
				QPointF(points_[points_.size() - 1].x() - topleft.x(), points_[points_.size() - 1].y() - topleft.y()));
		}    

		QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), G_Transparent_Rate);
		QBrush brush(fill_color, Qt::SolidPattern);

        QVector<QPoint> shift_points;
        for (int i = 0; i < points_.size(); i++)
        {
            shift_points.push_back(QPoint(points_[i].x() - topleft.x(), points_[i].y() - topleft.y()));
        }
        QPolygon polygon(shift_points);


        QPainterPath painter_path;
        painter_path.addPolygon(polygon);
        painter.fillPath(painter_path, brush);
        painter_path.closeSubpath();
    }



    if((actived_ && !show_only_) || drawing_ || points_.size()<3)
    {      
        painter.setPen(QPen(Qt::red, pensize /scale));       
    }
   
	
    QPoint center = QPoint(0, 0);
    QRectF guideRect(0, 0, guide_size_ / scale, guide_size_ / scale);  
	for (int i = 0; i < points_.size(); i++)
	{
		
		if (actived_)
		{
			guideRect.moveCenter(QPoint(points_[i].x() - topleft.x(), points_[i].y() - topleft.y()));
			painter.setBrush(QBrush(Qt::white));
			painter.setPen(QPen(Qt::red, pensize / scale));
			painter.drawRect(guideRect);
		}
		else
		{
			//painter.fillRect(guideRect, QBrush(color_));
		}
		
        center.setX(center.x()+ points_[i].x());
        center.setY(center.y() + points_[i].y());
	}
	painter.setBrush(Qt::NoBrush);

    if (points_.size()!=0)
	{
		center.setX(center.x() / points_.size());
        center.setY(center.y() / points_.size());
    }
    

    if(actived_)
    {
        painter.setPen(QPen(actived_color_, 2/scale));
    }
    else
    {
        painter.setPen(QPen(color_, 2/scale));
    }
    if(!drawing_ && !text_.isEmpty())
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
        painter.drawText(center.x() - topleft.x() - wid/2, center.y() - topleft.y() + height,text_);
    }

    painter.restore();
}

//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoPolygon::drawNewGeomety(QPoint point,E_MouseState state)
{
    if(state == E_LDown)
    {
        if(!mouseDown )
        {
            points_.clear();
            mouseDown = true;
            drawing_ = true;
        }
        return false;
    }
    else if(mouseDown && state==E_MouseUp)
    {
        points_.push_back(point);
        return false;
    }
    else if(mouseDown && state == E_RDown)
    {
        mouseDown = false;
        drawing_ = false;
		cacuRect();
        emit signal_geoChanged();
        return true;
    }
    else if(mouseDown && state == E_Move)
    {
        return false;
    }

    return false;
}


void GeoPolygon::DeletePoint()
{
    if (operation_point_index_>=0
        && operation_point_index_< points_.size())
	{
		points_.removeAt(operation_point_index_);
		cacuRect();
        emit signal_geoChanged();
    }
	
}


void GeoPolygon::AddPoint()
{
	if (operation_point_index_ >= 0
		&& operation_point_index_ < points_.size())
	{
        QVector<QPoint>::iterator it= points_.begin()+ operation_point_index_+1;

        int end_index = operation_point_index_;
        if (operation_point_index_== points_.size() - 1)
		{
            end_index = 0;
        }
        else
		{
            end_index = operation_point_index_ + 1;
        }
        
        points_.insert(it,  QPoint((points_[operation_point_index_].x()+ points_[end_index].x())/2,
            (points_[operation_point_index_].y() + points_[end_index].y()) / 2));

		cacuRect();
		emit signal_geoChanged();
	}

}




bool GeoPolygon::rightButtonDown(QPoint position, QPoint left_top, QPoint point, double scale)
{
    if (hide_ || show_only_) 
        return false;

	QRectF guideRect(0, 0, guide_size_, guide_size_);

	for (int i = 0; i < points_.size(); i++)
	{
		guideRect.moveCenter(QPoint((points_[i].x() - left_top.x()) * scale, (points_[i].y() - left_top.y()) * scale));
		//guideRect.moveCenter(points_[i]);
		if (guideRect.contains(position))
		{
			operation_point_index_ = i;
			menu.exec(QCursor::pos());
			return true;
		}
	}
	return false;
}
void GeoPolygon::reset()
{
    mouseDown = false;
    drawing_ = false;
}
void GeoPolygon::cacuRect()
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
QRect GeoPolygon::getRect()
{
	return rect_;
}

bool GeoPolygon::checkInLine(QPoint point,QPoint point1,QPoint point2,double scale)
{
    QPointF center;
    double angle;
    if(point1.x()>point2.x())//调整顺序，点2在右
    {
        QPoint temp = point1;
        point1 = point2;
        point2 = temp;
    }

    center.setX((point1.x()+point2.x())/2.0);
    center.setY((point1.y()+point2.y())/2.0);

    if(point1.x()==point2.x())
        angle=90;
    else
    {
        double yy = point2.y()-point1.y();
        double xx = point2.x()-point1.x();
        angle = 0 - atan(yy / xx) * 180 / PI;
    }
    double width = sqrt((point1.x()-point2.x())*(point1.x()-point2.x())+
                        (point1.y()-point2.y())*(point1.y()-point2.y()));
    QRectF contourRect;
    contourRect.setRect(center.x()-width/2,center.y()-4/scale,width,8/scale);

    double xx= (point.x() - center.x())*cos(angle / 180 * PI)
             - (point.y() - center.y())*sin(angle / 180 * PI) + center.x() ;

    double yy= (point.x() - center.x())*sin(angle / 180 * PI)
             + (point.y() - center.y())*cos(angle / 180 * PI) + center.y() ;

    if(contourRect.contains(QPointF(xx,yy)))
    {
        return true;
    }

    return false;
}
