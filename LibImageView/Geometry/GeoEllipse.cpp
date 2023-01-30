#include "GeoEllipse.h"
#include <QPainter>
#define PI 3.1415927

GeoEllipse::GeoEllipse(int x, int y, int w, int h) :BaseGeo()
{
	type_ = E_Ellipse;
    center_ = QPoint(0,0);
    r_x_ = 0;
    r_y_ = 0;
    angle_ = 0;
    setRect(x, x, w, h);
}


GeoEllipse::GeoEllipse(BaseGeo* geo):BaseGeo(geo) 
{
	type_ = E_Ellipse;
	r_x_ = geo->r_x_;
	r_y_ = geo->r_y_;
	angle_ = geo->angle_;
    center_ = geo->center_;
    setRect(geo->rect_);
}

bool GeoEllipse::checkInGeo(QPoint point,bool ignorShowonly)
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
bool GeoEllipse::checkActive(QPoint point)
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

bool GeoEllipse::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
    if(hide_ || show_only_) return false;

    QRectF contourRect;
    contourRect.setRect(center_.x()-r_x_,center_.y()-r_y_,2*r_x_,2*r_y_);

    double xx= (point.x() - center_.x())*cos(angle_ / 180 * PI)
             - (point.y() - center_.y())*sin(angle_ / 180 * PI) + center_.x() ;

    double yy= (point.x() - center_.x())*sin(angle_ / 180 * PI)
             + (point.y() - center_.y())*cos(angle_ / 180 * PI) + center_.y() ;

    QPointF tPoint = QPointF((xx-left_top.x())*scale,(yy-left_top.y())*scale);
    QRectF guideRect(0,0, guide_size_ , guide_size_ );

	QRectF recttemp = QRectF((contourRect.x() - left_top.x()) * scale,
		(contourRect.y() - left_top.y()) * scale,
        contourRect.width() * scale,
        contourRect.height() * scale);

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

    guideRect.moveCenter(QPointF(recttemp.right()+ guide_size_*scale, recttemp.center().y()));
    if(guideRect.contains(tPoint))
    {
        resize_mode_ = E_Resize_angle;
        return true;
    }

    return false;
}

bool GeoEllipse::checkMove(QPoint point)
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

void GeoEllipse::ajust(QPoint distance)
{
    if(hide_ || show_only_) return;
    //注意：图像向下是正
    if(resize_mode_ == E_Resize_x)
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

// 	if (m_angle > 89.99) m_angle = 89.99;
// 	if (m_angle < -89.99) m_angle = -89.99;
// 
// 	if (m_rx < 0) m_rx = 0 - m_rx;
// 	if (m_ry < 0) m_ry = 0 - m_ry;


    emit signal_geoChanged();
}
void GeoEllipse::move(QPoint distance)
{
    if(hide_ || show_only_) return;
    center_.setX(center_.x()+distance.x());
    center_.setY(center_.y()+distance.y());
    emit signal_geoChanged();
}

void GeoEllipse::updateColor()
{

}

void GeoEllipse::draw(QPainter &painter,QPoint topleft,double scale)
{
    if(hide_) return;

    painter.save();
    painter.scale(scale, scale);

	float pensize = 2;
	if (actived_)
	{
		pensize = 3;
	}

	if (id_ == EllipseDrawString)
	{
		QPen pen = QPen(QColor(251, 252, 253), pensize / scale);
		pen.setStyle(Qt::SolidLine);
		painter.setPen(pen);
	}
	else if (actived_)
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
    //文字画在（x，y）这个点的左边，（x，y）在文字的中间

	painter.drawText(0 - wid / 2, 0 + r_y_ + height, text_);

    painter.rotate(0-angle_);//从目标角度逆时针旋转到0du，
	
	painter.drawEllipse(QPointF(0, 0), r_x_, r_y_);
	painter.drawLine(QPointF(0 - 2 / scale, 0),
		QPointF(0 + 2 / scale, 0));
	painter.drawLine(QPointF(0, 0 - 2 / scale),
		QPointF(0, 0 + 2 / scale));


	QRectF recttemp = QRectF(0 - r_x_, 0 - r_y_, 2 * r_x_, 2 * r_y_);
	painter.drawRect(recttemp);
	if (id_ == EllipseDrawString)
	{
		QPen pen = QPen(QColor(0, 120, 215), pensize / scale);
		pen.setStyle(Qt::DotLine);
		painter.setPen(pen);
        painter.drawRect(recttemp);

		QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), G_Transparent_Rate);
		QBrush brush(fill_color, Qt::SolidPattern);
		painter.setBrush(brush);

		painter.drawEllipse(QPointF(0, 0), r_x_, r_y_);
		
	}

    if(actived_ && !show_only_)
    {
       // painter.setPen(QPen(actived_color_, pensize /scale));
      

        QRectF guideRect(0,0, guide_size_ /scale, guide_size_ /scale);

       // painter.setPen(QPen(Qt::red, pensize /scale));
        //旋转向导连线
        painter.drawLine(QPointF(recttemp.right(),recttemp.center().y()),
                         QPointF(recttemp.right()+guide_size_,recttemp.center().y()));
        
        //旋转向导
        guideRect.moveCenter(QPointF(recttemp.right()+ guide_size_,recttemp.center().y()));
       
        painter.setBrush(QBrush(Qt::white));
        painter.setPen(QPen(Qt::red, pensize / scale));
        painter.drawEllipse(guideRect);

        //水平向导
        guideRect.moveCenter(QPointF(recttemp.right(),recttemp.center().y()));
        painter.drawRect(guideRect);
        //竖直向导
        guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.top()));
        painter.drawRect(guideRect);

        painter.setBrush(Qt::NoBrush);
    }

    painter.restore();
}


//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoEllipse::drawNewGeomety(QPoint point, E_MouseState state)
{
	static bool mouseDown = false;
	static QRect rect;
	if (state == E_LDown)
	{
		rect.setLeft(point.x());
		rect.setTop(point.y());
		rect.setWidth(0);
		rect.setHeight(0);
		mouseDown = true;
		return false;
	}
	else if (mouseDown && state == E_Move)
	{
		rect.setRight(point.x());
		rect.setBottom(point.y());
		center_ = rect.center();
		r_x_ = rect.width() / 2;
		r_y_ = rect.height() / 2;
		return false;
	}
	else if (state == E_MouseUp)
	{
		mouseDown = false;

		QRect rect = QRect(0, 0, r_x_ * 2, r_y_ * 2);
		rect.moveCenter(QPoint(center_.x(), center_.y()));
		setRect(rect);

		// emit signal_geoChanged();
		return true;
	}
	return true;
}


QRect GeoEllipse::getRect()
{
	return QRect(center_.x() - r_x_, center_.y() - r_y_, r_x_ * 2, r_y_ * 2);
}