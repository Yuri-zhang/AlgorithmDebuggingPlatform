#include "GeoRect.h"
#include <QPainter>
#include <QDebug>

GeoRect::GeoRect(int x, int y, int w, int h)
{
    actived_ = false;
    resize_mode_ = E_RectResize_none;
    type_ = E_Rect;
    setRect(x, y, w, h);
}


GeoRect::GeoRect(BaseGeo* geo) :BaseGeo(geo)
{

}


bool GeoRect::checkInGeo(QPoint point,bool ignorShowonly)
{
	if (hide_ || (show_only_ && !ignorShowonly))
	{
		return false;
	}
	if (show_only_ && show_only_rect_.isValid())
	{
		return show_only_rect_.contains(point);
	}
    QRectF rect(rect_.x(),rect_.y(),rect_.width(),rect_.height());
    if(rect.contains(point))
    {
        return true;
    }
    return false;
}
bool GeoRect::checkActive(QPoint point)
{
    if(hide_ || show_only_) return false;

    QRectF rect(rect_.x(),rect_.y(),rect_.width(),rect_.height());
    if(rect.contains(point))
    {
        setActive();
        return true;
    }

    deActive();
    return false;
}

bool GeoRect::checkAjust(QPoint position, QPoint left_top, QPoint point,double scale)
{
    if(hide_ || show_only_) 
        return false;
    //guideRect.moveCenter(QPoint((points_[i].x() - left_top.x()) * scale, (points_[i].y() - left_top.y()) * scale));
    QRectF recttemp = QRectF((rect_.x()-left_top.x())*scale,
        (rect_.y() - left_top.y()) * scale,
        rect_.width()*scale,
        rect_.height()*scale);
    QRectF guideRect(0,0, guide_size_ , guide_size_ );

    guideRect.moveCenter(recttemp.topLeft());
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_topleft;
        return true;
    }
    guideRect.moveCenter(recttemp.topRight());
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_topright;
        return true;
    }
    guideRect.moveCenter(recttemp.bottomLeft());
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_bottomleft;
        return true;
    }
    guideRect.moveCenter(recttemp.bottomRight());
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_bottomright;
        return true;
    }
    guideRect.moveCenter(QPointF(recttemp.left(),recttemp.center().y()));
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_left;
        return true;
    }
    guideRect.moveCenter(QPointF(recttemp.right(),recttemp.center().y()));
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_right;
        return true;
    }
    guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.top()));
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_top;
        return true;
    }
    guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.bottom()));
    if(guideRect.contains(position))
    {
        resize_mode_ = E_RectResize_bottom;
        return true;
    }


    resize_mode_ = E_RectResize_none;
    return false;
}

bool GeoRect::checkMove(QPoint point)
{
    if(hide_ || show_only_) return false;

    if(rect_.contains(point))
    {
        return true;
    }
    return false;
}

void GeoRect::ajust(QPoint distance)
{
    if(hide_ || show_only_) 
        return;    	

    QRect move_rect = rect_;
	if (resize_mode_ == E_RectResize_top)
	{
        move_rect.setY(rect_.y() + distance.y());
        move_rect.setHeight(rect_.width() - distance.y());
	}
	else if (resize_mode_ == E_RectResize_bottom)
	{
        move_rect.setHeight(rect_.height() + distance.y());
	}
	else if (resize_mode_ == E_RectResize_left)
	{
        move_rect.setX(rect_.x() + distance.x());
        move_rect.setWidth(rect_.width() - distance.x());
	}
	else if (resize_mode_ == E_RectResize_right)
	{
        move_rect.setWidth(rect_.width() + distance.x());
	}
	else if (resize_mode_ == E_RectResize_topleft)
	{
        move_rect.setX(rect_.x() + distance.x());       
        move_rect.setY(rect_.y() + distance.y());
        move_rect.setWidth(rect_.width() - distance.x());
        move_rect.setHeight(rect_.height() - distance.y());
	}
	else if (resize_mode_ == E_RectResize_topright)
	{
		move_rect.setY(rect_.y() + distance.y());
		move_rect.setWidth(rect_.width() + distance.x());
        move_rect.setHeight(rect_.height() - distance.y());
	}
	else if (resize_mode_ == E_RectResize_bottomleft)
	{
        move_rect.setX(rect_.x() + distance.x());
        move_rect.setWidth(rect_.width() - distance.x());
        move_rect.setHeight(rect_.height() + distance.y());
	}
	else if (resize_mode_ == E_RectResize_bottomright)
	{
        move_rect.setWidth(rect_.width() + distance.x());
        move_rect.setHeight(rect_.height() + distance.y());
	}


	if (G_LimitImageRect)
	{
		if (move_rect.x() < 0
			|| move_rect.y() < 0
			|| move_rect.x() + move_rect.width() > image_size_.width()
			|| move_rect.y() + move_rect.height() > image_size_.height())
		{
			return;
		}

	}
	


	if (resize_mode_ == E_RectResize_top)
	{
		rect_.setY(rect_.y() + distance.y());
	}
	else if (resize_mode_ == E_RectResize_bottom)
	{
		rect_.setHeight(rect_.height() + distance.y());
	}

	else if (resize_mode_ == E_RectResize_left)
	{
		rect_.setX(rect_.x() + distance.x());
	}
	else if (resize_mode_ == E_RectResize_right)
	{
		rect_.setWidth(rect_.width() + distance.x());
	}
	else if (resize_mode_ == E_RectResize_topleft)
	{
		rect_.setX(rect_.x() + distance.x());
		rect_.setY(rect_.y() + distance.y());
	}
	else if (resize_mode_ == E_RectResize_topright)
	{
		rect_.setY(rect_.y() + distance.y());
		rect_.setWidth(rect_.width() + distance.x());
	}
	else if (resize_mode_ == E_RectResize_bottomleft)
	{
		rect_.setX(rect_.x() + distance.x());
		rect_.setHeight(rect_.height() + distance.y());
	}
	else if (resize_mode_ == E_RectResize_bottomright)
	{
		rect_.setWidth(rect_.width() + distance.x());
		rect_.setHeight(rect_.height() + distance.y());
	}
    emit signal_geoChanged();
}

void GeoRect::move(QPoint distance)
{
    if(hide_ || show_only_) return;

    QRect move_rect = rect_;
    move_rect.adjust(distance.x(), distance.y(), distance.x(), distance.y());

    if (move_rect.x()<0
        || move_rect.y()<0
        || move_rect.x()+ move_rect.width()>=image_size_.width()
        || move_rect.y()+move_rect.height()>=image_size_.height())
    {
        return;
    }

    rect_.adjust(distance.x(),distance.y(),distance.x(),distance.y());
    emit signal_geoChanged();
}




void GeoRect::draw(QPainter &painter,QPoint topleft,double scale)
{
    if(hide_)
		return;

	if (rect_.width()==0
		&& rect_.height()==0)
	{
		return;
	}

    painter.save();
    painter.scale(scale, scale);

	float pensize = 2;
	if (actived_)
	{
		pensize = 3;
	}
    QPen pen;
	if (id_ == RectMeasureString)
	{
		pen = QPen(QColor(251, 0, 253), pensize / scale);
		pen.setStyle(Qt::SolidLine);
      
	}
	else if (id_ == RectDrawString)
	{
		pen = QPen(QColor(0, 120, 215), pensize / scale);
        pen.setStyle(Qt::SolidLine);
    }
    else if(actived_)
    {
        pen=QPen(actived_color_, pensize /scale);
    }
    else
    {
        pen=QPen(color_, pensize /scale);
    }

    painter.setPen(pen);


    QRectF recttemp = rect_.adjusted(-topleft.x(),-topleft.y(),-topleft.x(),-topleft.y());
	if (!text_.isEmpty())
	{
		QFont font;
		font.setPointSizeF(12 / scale);
		font.setFamily("Microsoft YaHei");
		font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
		painter.setFont(font);
		QFontMetricsF fontMetrics(font);
		qreal height = fontMetrics.height();
		painter.drawText(recttemp.left() + 6 / scale, recttemp.top() + height, text_);
	}


	if (show_only_)
	{
		//显示时,如果缺陷框较小，则先将以图像数据坐标为基准的rect外扩一下 2021-07
		QRectF extRect = recttemp;

		//保持矩形显示尺寸不小于MIN_LEN
		const double MIN_LEN = 10.0;
		double viewW = recttemp.width() * scale;
		double viewH = recttemp.height() * scale;
		if (viewW < MIN_LEN || viewH < MIN_LEN)
		{
			if (viewW < MIN_LEN)
			{
				viewW = MIN_LEN;
			}

			if (viewH < MIN_LEN)
			{
				viewH = MIN_LEN;
			}

			QPointF ptCenter = recttemp.center();
			extRect.setRect(ptCenter.x() - viewW / scale / 2.0,
							ptCenter.y() - viewH / scale / 2.0,
							viewW / scale, viewH / scale);
		}
		show_only_rect_ = extRect;
		show_only_rect_.moveCenter(rect_.center());
		painter.drawRect(extRect);
		painter.restore();
		return;
	}    

    painter.drawRect(recttemp);

    if (id_ == RectDrawString
		|| id_==RectMeasureString)
    {
		pen = QPen(QColor(251, 252, 253), pensize / scale);
		pen.setStyle(Qt::DotLine);
        painter.setPen(pen);
        painter.drawRect(recttemp);

		QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), G_Transparent_Rate);
		painter.fillRect(recttemp, QBrush(fill_color));
      
    }


    if(actived_ && !show_only_)
    {
        QRectF guideRect(0,0, guide_size_ /scale, guide_size_ /scale);

        guideRect.moveCenter(recttemp.topLeft());
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
        painter.drawRect(guideRect);

        guideRect.moveCenter(recttemp.topRight());
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
		painter.drawRect(guideRect);

        guideRect.moveCenter(recttemp.bottomLeft());
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
		painter.drawRect(guideRect);

        guideRect.moveCenter(recttemp.bottomRight());
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
		painter.drawRect(guideRect);

        guideRect.moveCenter(QPointF(recttemp.left(),recttemp.center().y()));
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
		painter.drawRect(guideRect);

        guideRect.moveCenter(QPointF(recttemp.right(),recttemp.center().y()));
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
		painter.drawRect(guideRect);

        guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.top()));
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
		painter.drawRect(guideRect);

        guideRect.moveCenter(QPointF(recttemp.center().x(),recttemp.bottom()));
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(QPen(Qt::red, pensize / scale));
		painter.drawRect(guideRect);
    }

  

    if (id_ == RectMeasureString 
		|| id_ == RectDrawString)
	{
		painter.setPen(QPen(QColor(251, 252, 253), pensize / scale));
		QFont font;
		font.setPointSizeF(12 / scale);
		font.setFamily("Microsoft YaHei");
		font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
		painter.setFont(font);
		QFontMetricsF fontMetrics(font);
		qreal height = fontMetrics.height();
        qreal font_width = fontMetrics.maxWidth();

        QString left_top_info = "X: " + QString::number(rect_.x());
		painter.drawText(recttemp.left() + 6 / scale, recttemp.top() + height, left_top_info);
		left_top_info = "Y: " + QString::number(rect_.y());
		painter.drawText(recttemp.left() + 6 / scale, recttemp.top() + 2*height, left_top_info);

		QString width_info = QString::fromLocal8Bit("宽: ") + QString::number(rect_.width());
		painter.drawText(recttemp.left()+recttemp.width() /2 + 6 / scale- font_width, recttemp.top()+ recttemp.height() + height, width_info);

		QString height_info = QString::fromLocal8Bit("高: ") + QString::number(rect_.height());
		painter.drawText(recttemp.left()+recttemp.width() + 6 / scale, recttemp.top() + recttemp.height()/2, height_info);
    }


    painter.restore();
}
//新几何体绘制，第一个参数为鼠标的像素位置，第二个参数为鼠标状态，返回值为绘制结束标志
bool GeoRect::drawNewGeomety(QPoint point,E_MouseState state)
{
    static bool mouseDown=false;
    if(state == E_LDown)
    {
        rect_.setLeft(point.x());
        rect_.setTop(point.y());
        rect_.setWidth(0);
        rect_.setHeight(0);
        mouseDown = true;
        return false;
    }
    else if(mouseDown && state == E_Move)
    {
        rect_.setRight(point.x());
        rect_.setBottom(point.y());
        return false;
    }
    else if(state == E_MouseUp)
    {
       /* if(rect_.width()<1)
            rect_.setWidth(1);
        if(rect_.height()<1)
            rect_.setHeight(1);*/


		if (rect_.width() < 0)
		{
			int width = abs(rect_.width());
			rect_.setX(rect_.x() - width);
			rect_.setWidth(width);
		}

		if (rect_.height() < 0)
		{
			int hieght = abs(rect_.height());
			rect_.setY(rect_.y() - hieght);
			rect_.setHeight(hieght);
		}

        mouseDown=false;
        emit signal_geoChanged();
        return true;
    }
    return true;
}

QRect GeoRect::getRect() 
{
	if (show_only_ && show_only_rect_.isValid())
	{
		return show_only_rect_.toRect();
	}
	return rect_; 
};