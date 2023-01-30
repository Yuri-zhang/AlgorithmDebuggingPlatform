#include "GeoArc.h"
#include <QPainter>
#define PI 3.1415927

GeoArc::GeoArc(int x, int y, int w, int h) :BaseGeo()
{
	type_ = E_Arc;
    center_ = QPoint(0,0);
    r_x_ = 0;
    r_y_ = 0;
    angle_ = 0;
    begin_angle_ = 0;
    end_angle_ = 270;
    setRect(x, x, w, h);
}


GeoArc::GeoArc(BaseGeo* geo):BaseGeo(geo)
{
	type_ = E_Arc;
	r_x_ = geo->r_x_;
	r_y_ = geo->r_y_;
	angle_ = geo->angle_;
	center_ = geo->center_;
    begin_angle_ = geo->begin_angle_;
    end_angle_ = geo->end_angle_;
    setRect(geo->rect_);
}

bool GeoArc::checkInGeo(QPoint point,bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly)) return false;
    QRectF contourRect;
    contourRect.setRect(center_.x()-r_x_,center_.y()-r_y_,2*r_x_,2*r_y_);

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
bool GeoArc::checkActive(QPoint point)
{
    if(hide_ || show_only_) return false;

    QRectF contourRect;
    contourRect.setRect(center_.x()-r_x_,center_.y()-r_y_,2*r_x_,2*r_y_);

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

bool GeoArc::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
    if(hide_ || show_only_) return false;

    QRectF contourRect;
    contourRect.setRect(center_.x()-r_x_,center_.y()-r_y_,2*r_x_,2*r_y_);

    double xx= (point.x() - center_.x())*cos(angle_ / 180 * PI)
             - (point.y() - center_.y())*sin(angle_ / 180 * PI) + center_.x() ;

    double yy= (point.x() - center_.x())*sin(angle_ / 180 * PI)
             + (point.y() - center_.y())*cos(angle_ / 180 * PI) + center_.y() ;

	QPointF tPoint = QPointF((xx - left_top.x()) * scale, (yy - left_top.y()) * scale);
	QRectF guideRect(0, 0, guide_size_, guide_size_);

	QRectF recttemp = QRectF((contourRect.x() - left_top.x()) * scale,
		(contourRect.y() - left_top.y()) * scale,
		contourRect.width() * scale,
		contourRect.height() * scale);

	QPointF begin_angle = GetBeginAnglePosition();
	guideRect.moveCenter(QPointF((begin_angle.x() + center_.x()-left_top.x())*scale, 
        (begin_angle.y() + center_.y()-left_top.y())*scale));
	if (guideRect.contains(tPoint))
	{
		resize_mode_ = E_Arc_BeginAngle;
		return true;
	}

	QPointF end_angle = GetEndAnglePosition();
	guideRect.moveCenter(QPointF((end_angle.x() + center_.x()-left_top.x())*scale, (end_angle.y() + center_.y()-left_top.y())*scale));
	if (guideRect.contains(tPoint))
	{
		resize_mode_ = E_Arc_EndAngle;
		return true;
	}

    guideRect.moveCenter(QPointF(recttemp.center().x(), recttemp.top()));
    if(guideRect.contains(tPoint))
    {
        resize_mode_ = E_Resize_y;
        return true;
    }

    guideRect.moveCenter(QPointF(recttemp.right(), recttemp.center().y()));
    if(guideRect.contains(tPoint))
    {
        resize_mode_ = E_Resize_x;
        return true;
    }

    guideRect.moveCenter(QPointF(recttemp.right()+guide_size_*scale, recttemp.center().y()));
    if(guideRect.contains(tPoint))
    {
        resize_mode_ = E_Resize_angle;
        return true;
    }

  

    return false;
}

bool GeoArc::checkMove(QPoint point)
{
    if(hide_ || show_only_) return false;

    QRectF contourRect;
    contourRect.setRect(center_.x()-r_x_,center_.y()-r_y_,2*r_x_,2*r_y_);

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



void GeoArc::ajust(QPoint distance)
{
    if(hide_ || show_only_) 
        return;
   
    //注意：图像向下是正
	if (resize_mode_ == E_Arc_BeginAngle)
	{
		double angle_distance = 2 * r_x_ * begin_angle_ / 360;

		double xx = angle_distance * cos(angle_ / 180 * PI) + distance.x();
		double yy = angle_distance * sin(angle_ / 180 * PI) - distance.y();

		angle_distance = sqrt(xx * xx + yy * yy);

        begin_angle_ = angle_distance * 360 / (2 * r_x_);

		if (begin_angle_ > (end_angle_-5))
		{
            begin_angle_ = end_angle_ - 5;
           return;
		}
		else if (begin_angle_ < 0)
		{
            begin_angle_ = 0;
		}
	}
	else if (resize_mode_ == E_Arc_EndAngle)
	{
        double angle_distance = 2 * r_x_ * end_angle_ / 360;

		double xx = angle_distance * cos(angle_ / 180 * PI) + distance.x();
		double yy = angle_distance * sin(angle_ / 180 * PI) - distance.y();

        angle_distance = sqrt(xx * xx + yy * yy);

        end_angle_ = angle_distance * 360 / (2 * r_x_);     

       if (end_angle_>360.0f)
       {
           end_angle_ = 360.0f;
       }
       else if (end_angle_<(begin_angle_ +5))
       {
           end_angle_ = begin_angle_ +5;
       }
	}
    else  if(resize_mode_ == E_Resize_x)
    {
        double xx = r_x_ * cos(angle_ / 180 * PI) + distance.x();
        double yy = r_x_ * sin(angle_ / 180 * PI) - distance.y();
       
		r_x_ = sqrt(xx*xx + yy * yy);
    }
    else if(resize_mode_ == E_Resize_y)
    {
		double xx = r_y_ * cos((angle_+90) / 180 * PI) + distance.x();
        double yy = r_y_ * sin((angle_+90) / 180 * PI) - distance.y();
       
		r_y_ = sqrt(xx*xx + yy * yy);
    }
    else if(resize_mode_ == E_Resize_angle)
    {
		double xx = r_x_ * cos(angle_ / 180 * PI) + distance.x();
		double yy = r_x_ * sin(angle_ / 180 * PI) - distance.y();
	

        angle_ = atan(yy / xx) * 180 / PI;

		if (yy > 0
			&& xx < 0)
		{
			angle_ = 180 + angle_;
		}
		else if (yy < 0
			&& xx < 0)
		{
			angle_ = 180 + angle_;
		}
		else if (yy < 0
			&& xx>0)
		{
			angle_ = 360 + angle_;
		}
    }  


    emit signal_geoChanged();
}


void GeoArc::move(QPoint distance)
{
    if(hide_ || show_only_) return;
    center_.setX(center_.x()+distance.x());
    center_.setY(center_.y()+distance.y());
    emit signal_geoChanged();
}


void GeoArc::updateColor()
{

}


double GeoArc::GetAngleValue(double value)
{
    return  value*PI/180;
}


QPointF GeoArc::GetBeginAnglePosition()
{
    return QPointF(2 * r_x_ * begin_angle_ / 360 - r_x_, r_y_);
}

QPointF GeoArc::GetEndAnglePosition()
{   
	return QPointF(2*r_x_ * end_angle_/360-r_x_, r_y_);
}


void GeoArc::draw(QPainter &painter,QPoint topleft,double scale)
{
    if(hide_) return;

    painter.save();
    painter.scale(scale, scale);

	float pensize = 2;
	if (actived_)
	{
		pensize = 3;
	}


	if (actived_)
	{
		painter.setPen(QPen(actived_color_, pensize / scale));
	}
	else
	{
		painter.setPen(QPen(color_, pensize / scale));
	}

    QPointF Pointtemp = center_ - topleft;
    painter.translate(Pointtemp.x(), Pointtemp.y());//把画图区域中心点作为坐标系原点


	//设置字体、大小、字符间距等
	QFont font;
	font.setPointSizeF(12 / scale);
	font.setFamily("Microsoft YaHei");
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);

	//获取这种字体情况下，文本的长度和高度
	QFontMetricsF fontMetrics(font);
	//qreal wid = fontMetrics.width(text_);
	qreal height = fontMetrics.height();
	qreal wid = height * text_.length();


	painter.drawText(0 - wid / 2, 0 + r_y_ + height, text_);

    painter.rotate(-angle_);//从目标角度逆时针旋转到0du，	

    painter.drawArc(QRect(-r_x_,-r_y_,r_x_*2,r_y_*2), begin_angle_*16, (end_angle_-begin_angle_)*16);
    

    painter.drawLine(QPointF(0 - 2 / scale, 0),
		QPointF(0 + 2 / scale, 0));
	painter.drawLine(QPointF(0, 0 - 2 / scale),
		QPointF(0, 0 + 2 / scale));


    if(actived_ && !show_only_)
    {
        painter.setPen(QPen(actived_color_, pensize /scale));
        QRectF recttemp = QRectF(0-r_x_,0-r_y_,2*r_x_,2*r_y_);
        painter.drawRect(recttemp);

        QRectF guideRect(0,0,guide_size_/scale, guide_size_ /scale);

        painter.setPen(QPen(Qt::red, pensize / scale));
        //旋转向导连线
        painter.drawLine(QPointF(recttemp.right(),recttemp.center().y()),
                         QPointF(recttemp.right()+ guide_size_ ,recttemp.center().y()));
        //旋转向导
        guideRect.moveCenter(QPointF(recttemp.right()+ guide_size_ ,recttemp.center().y()));
       
      
        painter.setBrush(QBrush(Qt::red));
        painter.drawEllipse(guideRect);

        //水平向导
        guideRect.moveCenter(QPointF(recttemp.right(),recttemp.center().y()));
        painter.fillRect(guideRect, Qt::red);
       
        //竖直向导
        guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.top()));
        painter.fillRect(guideRect, Qt::red);

      
       
        painter.setBrush(Qt::NoBrush);

        //圆弧角度向导
		painter.setPen(QPen(Qt::green, pensize / scale));

		QPointF begin_angle_point = GetBeginAnglePosition();
		guideRect.moveCenter(begin_angle_point);
		painter.drawEllipse(guideRect);

		painter.setPen(QPen(Qt::blue, pensize / scale));
        QPointF end_angle_point = GetEndAnglePosition();
		guideRect.moveCenter(end_angle_point);       
		painter.drawEllipse(guideRect);       
    }  

    //painter.drawEllipse(QPointF(0,0),2/scale,2/scale);

    painter.restore();

}

//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoArc::drawNewGeomety(QPoint point, E_MouseState state)
{
    static bool mouseDown=false;
    static QRect rect;
    if(state == E_LDown)
    {
        rect.setLeft(point.x());
        rect.setTop(point.y());
        rect.setWidth(0);
        rect.setHeight(0);
        mouseDown = true;
        return false;
    }
    else if(mouseDown && state == E_Move)
    {
        rect.setRight(point.x());
        rect.setBottom(point.y());
        center_ = rect.center();
        r_x_ = rect.width()/2;
        r_y_ = rect.height()/2;
        return false;
    }
    else if(state == E_MouseUp)
    {
        mouseDown=false;

		QRect rect = QRect(0, 0, r_x_ * 2, r_y_ * 2);
		rect.moveCenter(QPoint(center_.x(), center_.y()));
		setRect(rect);

       // emit signal_geoChanged();
        return true;
    }
    return true;
}


QRect GeoArc::getRect()
{
	return QRect(center_.x() - r_x_, center_.y() - r_y_, r_x_ * 2, r_y_ * 2);
}