#include "GeoCircle.h"
#include <QPainter>

GeoCircle::GeoCircle():BaseGeo()
{
    type_ = E_Circle;
}

GeoCircle::GeoCircle(BaseGeo* geo):BaseGeo(geo)
{
    type_ = E_Circle;
    color_ = geo->color_;
}


bool GeoCircle::checkInGeo(QPoint point, bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly)) 
        return false;
    double dis = (center_.x()-point.x())*(center_.x()-point.x())
            +(center_.y()-point.y())*(center_.y()-point.y());

    if(dis<radius_* radius_)
    {
        return true;
    }
    return false;
}

void GeoCircle::updateColor()
{
    /*if(m_actived)
    {
        m_color = Qt::red;
    }
    else
    {
        m_color = Qt::white;
    }*/
}

bool GeoCircle::checkActive(QPoint point)
{
    if(hide_ || show_only_) return false;

    double dis = (center_.x()-point.x())*(center_.x()-point.x())
            +(center_.y()-point.y())*(center_.y()-point.y());

    if(dis<radius_*radius_)
    {
        setActive();
        return true;
    }

    deActive();
    return false;
}

bool GeoCircle::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
    if(hide_ || show_only_) return false;

    QRectF contourRect;
    contourRect.setRect(center_.x()-radius_,center_.y()-radius_,2*radius_,2*radius_);


	QRectF recttemp = QRectF((contourRect.x() - left_top.x()) * scale,
		(contourRect.y() - left_top.y()) * scale,
		contourRect.width() * scale,
		contourRect.height() * scale);


    QRectF guideRect(0,0, guide_size_ , guide_size_ );

    guideRect.moveCenter(QPointF(recttemp.left(),recttemp.center().y()));
    if(guideRect.contains(position))
    {
        m_resizeMode = E_RectResize_left;
        return true;
    }
    guideRect.moveCenter(QPointF(recttemp.right(),recttemp.center().y()));
    if(guideRect.contains(position))
    {
        m_resizeMode = E_RectResize_right;
        return true;
    }
    guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.top()));
    if(guideRect.contains(position))
    {
        m_resizeMode = E_RectResize_top;
        return true;
    }
    guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.bottom()));
    if(guideRect.contains(position))
    {
        m_resizeMode = E_RectResize_bottom;
        return true;
    }

    m_resizeMode = E_RectResize_none;
    return false;
}

bool GeoCircle::checkMove(QPoint point)
{
    if(hide_ || show_only_) return false;

    double dis = (center_.x()-point.x())*(center_.x()-point.x())
            +(center_.y()-point.y())*(center_.y()-point.y());

    if(dis<radius_*radius_)
    {
        return true;
    }
    return false;
}

void GeoCircle::ajust(QPoint distance)
{
    if(hide_ || show_only_) return;

    if(m_resizeMode == E_RectResize_top)
        radius_ -= distance.y();
    else if(m_resizeMode == E_RectResize_bottom)
        radius_ += distance.y();
    else if(m_resizeMode == E_RectResize_left)
        radius_ -= distance.x();
    else if(m_resizeMode == E_RectResize_right)
        radius_ += distance.x();
    emit signal_geoChanged();

}

void GeoCircle::move(QPoint distance)
{
    if(hide_ || show_only_) return;

    center_ += distance;
    emit signal_geoChanged();
}

void GeoCircle::draw(QPainter &painter,QPoint topleft,double scale)
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

    QRectF recttemp;
    recttemp.setRect(center_.x()-radius_,center_.y()-radius_,2*radius_,2*radius_);
    recttemp = recttemp.adjusted(-topleft.x(),-topleft.y(),-topleft.x(),-topleft.y());

    painter.drawEllipse(QPointF(center_.x()-topleft.x(),center_.y()-topleft.y()),radius_,radius_);

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
    painter.drawText(center_.x()-topleft.x() - wid/2,recttemp.bottom() + height,text_);


	if (id_ == CircleDrawString)
	{
		QPen pen = QPen(QColor(0, 120, 215), pensize / scale);
		pen.setStyle(Qt::DotLine);
		painter.setPen(pen);
		painter.drawRect(recttemp);

		QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), G_Transparent_Rate);
		QBrush brush(fill_color, Qt::SolidPattern);
		painter.setBrush(brush);

		painter.drawEllipse(QPointF(center_.x() - topleft.x(), center_.y() - topleft.y()), 
            radius_, 
            radius_);

	}

    if(actived_ && !show_only_)
    {
        QRectF guideRect(0,0,guide_size_/scale, guide_size_ /scale);
        guideRect.moveCenter(QPointF(recttemp.left(),recttemp.center().y()));
        painter.fillRect(guideRect,Qt::red);
        guideRect.moveCenter(QPointF(recttemp.right(),recttemp.center().y()));
        painter.fillRect(guideRect,Qt::red);
        guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.top()));
        painter.fillRect(guideRect,Qt::red);
        guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.bottom()));
        painter.fillRect(guideRect,Qt::red);
    }
    painter.restore();
}


//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoCircle::drawNewGeomety(QPoint point, E_MouseState state)
{
	static bool mouseDown = false;
	if (state == E_LDown)
	{
		center_ = point;
		radius_ = 0;
		mouseDown = true;
		return false;
	}
	else if (mouseDown && state == E_Move)
	{
		double dis = (center_.x() - point.x()) * (center_.x() - point.x())
			+ (center_.y() - point.y()) * (center_.y() - point.y());

		radius_ = sqrt(dis);
		return false;
	}
	else if (state == E_MouseUp)
	{
		mouseDown = false;
		emit signal_geoChanged();
		return true;
	}
	return true;
}

QRect GeoCircle::getRect()
{
	return QRect(center_.x()- radius_, center_.y() - radius_, radius_*2, radius_*2);
}
