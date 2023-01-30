#include "BaseGeo.h"
#define PI 3.1415927

int BaseGeo::G_LimitImageRect = true;

BaseGeo::BaseGeo()
{   
	reset();
}


BaseGeo::BaseGeo(BaseGeo* geo)
{
	Copy(geo);
}


void BaseGeo::reset()
{
	actived_ = false;
	drawing_ = false;
	hide_ = false;
	show_only_ = false;
	color_ = QColor(41, 242, 43);         //常规颜色
	actived_color_ = QColor(235, 235, 35);    //激活时的颜色
	type_ = E_unknownGeo;

	points_.clear();

	center_ = QPoint(0, 0);
	r_x_ = 0.0f;
	r_y_ = 0.0f;
	angle_ = 0.0f;

	id_ = "";
	text_ = "";
	toolTip_ = "";
	angle_ = 0;
	rect_.setRect(0, 0, 0, 0);
	image_size_ = QSize(0, 0);

	point1_ = QPointF(0, 0);
	point2_ = QPointF(0, 0);

	begin_angle_ = 0;
	end_angle_ = 270;

	radius_ = 0.0;

	guide_size_ = 10;

	resize_mode_ = E_RectResize_none;

	bound_rect_ = QRect(0, 0, 9999999, 9999999);
}

void BaseGeo::Copy(BaseGeo* geo)
{
	if (geo == NULL)
	{
		return;
	}
	actived_ = geo->actived_;
	drawing_ = geo->drawing_;
	hide_ = geo->hide_;
	show_only_ = geo->show_only_;
	color_ = geo->color_;         //常规颜色
	actived_color_ = geo->actived_color_;    //激活时的颜色
	type_ = geo->type_;

	id_ = geo->id_;
	text_ = geo->text_;
	toolTip_ = geo->toolTip_;
	angle_ = geo->angle_;
	rect_ = QRect(geo->rect_);
	resize_mode_ = geo->resize_mode_;

	center_ = geo->center_;
	r_x_ = geo->r_x_;
	r_y_ = geo->r_y_;
	angle_ = geo->angle_;
	begin_angle_ = geo->begin_angle_;
	end_angle_ = geo->end_angle_;

	points_ = geo->points_;
	point_ = geo->point_;

	ajust_point_index_ = geo->ajust_point_index_;
	m_quadMode = geo->m_quadMode;
	mouseDown = geo->mouseDown;

	scale_ = geo->scale_;

	created_ = geo->created_;

	m_insertID = geo->m_insertID;
	m_insertPoint = geo->m_insertPoint;
	mouseDown = geo->mouseDown;

	image_size_ = geo->image_size_;

	point1_ = geo->point1_;
	point2_ = geo->point2_;
	radius_ = geo->radius_;

	bound_rect_ = geo->bound_rect_;

	guide_size_ = geo->guide_size_;
}


void BaseGeo::deActive()
{
    actived_ = false;
    updateColor();
    emit signal_geoChanged();
}

void BaseGeo::setActive(bool active)
{
    actived_ = active;
    updateColor();
    emit signal_geoChanged();
}

class IntersectionGeo
{
public:
	IntersectionGeo(BaseGeo* geo, QPoint cursorPos)
	{
		valid_ = false;
		if (geo)
		{
			geo_ = geo;
			rect_ = geo_->getRect();
			valid_ = rect_.isValid();
		}
		if (valid_)
		{
			QPoint cpoint = rect_.center();
			centerdis_ = (cpoint.x() - cursorPos.x())*(cpoint.x() - cursorPos.x()) +
				         (cpoint.y() - cursorPos.y())*(cpoint.y() - cursorPos.y());
		}
	}
	BaseGeo* geo_;
	QRect rect_;
	bool valid_;
	int centerdis_;
};


//从多个相交的几何体中筛选一个激活几何体
BaseGeo* BaseGeo::selectIntersectionGeos(QVector<BaseGeo*> geos, QPoint cursorPos)
{
	if (geos.isEmpty())
	{
		return nullptr;
	}
	if (geos.size() == 1)
	{
		return geos[0];
	}
	QVector<IntersectionGeo> intergeos;
	for (int i = 0; i < geos.size(); i++)
	{
		intergeos.append(IntersectionGeo(geos[i], cursorPos));
	}
	for (int i = 0; i < intergeos.size(); i++)
	{
		for (int j = 0; j < intergeos.size(); j++)
		{
			if (i == j || !intergeos[j].valid_ || !intergeos[i].valid_)
			{
				continue;
			}
			if (intergeos[i].rect_.contains(intergeos[j].rect_))
			{
				intergeos[i].valid_ = false;
			}
		}
	}
	for (int i = 0; i < intergeos.size(); i++)
	{
		for (int j = 0; j < intergeos.size(); j++)
		{
			if (i == j || !intergeos[j].valid_ || !intergeos[i].valid_)
			{
				continue;
			}
			if (intergeos[i].centerdis_ > intergeos[j].centerdis_)
			{
				intergeos[i].valid_ = false;
			}
		}
	}
	for (int i = 0; i < intergeos.size(); i++)
	{
		if (intergeos[i].valid_)
		{
			return intergeos[i].geo_;
		}
	}
	return geos[0];
}


void BaseGeo::clearPoints()
{
	points_.clear();
}

void BaseGeo::addPoint(int x, int y)
{
	points_.append(QPoint(x, y));
}

void BaseGeo::setRect(int x, int y, int w, int h)
{
	setRect(QRect(x, y, w, h));
}


void BaseGeo::setRect(QRect rect)
{
	rect_ = rect;
}



void BaseGeo::setPoints(QVector<QPoint> points)
{
	points_.clear();
	points_.append(points);

	cacuRect();
}

void BaseGeo::cacuRect()
{

}



//将数据限制在区域内,这里未对功能进行实现
bool BaseGeo::regionLimit(QRect)
{
	return false;
}


void BaseGeo::setColor(QColor color)
{
	color_ = color;
}
void BaseGeo::setActivedColor(QColor color)
{
	actived_color_ = color;
}

void BaseGeo::setText(QString Text)
{
	text_ = Text;
	if (toolTip_.isEmpty())
	{
		toolTip_ = Text;
	}
}

void BaseGeo::setToolTip(QString Text)
{
	toolTip_ = Text;
}

void BaseGeo::setShowOnly(bool showOnly)
{
	show_only_ = showOnly;
}

void BaseGeo::setHide(bool hide)
{
	hide_ = hide;
}

bool BaseGeo::isActive()
{
	return  actived_;
}

void BaseGeo::SetImageSize(QSize size)
{
	image_size_ = size;
}
