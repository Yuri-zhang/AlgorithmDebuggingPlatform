#include "LibImageView.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QVBoxLayout>
#include <QMenu>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>
#include "../LibCore/LockHelper.h"


static  QVector<QRgb> g_color_table_gray8;//颜色索引表
LibImageView::LibImageView(QWidget* parent):QWidget(parent)
{
	mutex_ = CreateMutex(NULL, FALSE ,NULL);
	outside_context_ = nullptr;
	m_outDrawCallback = nullptr;
	image_ops_type_ = e_Auto;
	g_color_table_gray8.resize(256);
	for (int i = 0; i < 256; i++)
	{
		g_color_table_gray8[i] = qRgb(i, i, i);
	}	

	enable_active_geo_ = true;
	drawing_ = false;
	clicked_InImage_ = false;
	drawing_geometry_ = nullptr;
	actived_geometry_ = nullptr;
	left_button_down_ = false;
	drag_imge_ = false;
	drag_geometry_ = false;
	ajust_geometry_ = false;
	right_button_down_ = false;
	drag_mode_ = true;
	auto_cursor_ = true;
	top_left_ = QPoint(0, 0);
	scale_ = 1;
	original_scale_ = 1.0;


	clearImage();
	setMouseTracking(true);
	add_contour_.setText(u8"添加");

	//m_pixmap = QPixmap(QSize(200, 200));
	//m_pixmap.fill(Qt::white);

	show_image_ = QImage(0, 0, QImage::Format_Mono);
	show_image_.fill(Qt::white);

	scale_ = 1.0;
	original_scale_ = 1.0;
	top_left_ = QPoint(0, 0);
	time_counter_ = 0;
	mouse_in_ = false;

	picture_rect_ = this->rect();

	back_brush_ = QBrush(Qt::gray);

	inited_ = false;

// 	connect(&timer_, &QTimer::timeout, this, &LibImageView::slot_timeout);
// 	timer_.start(100);

	setMouseTracking(true);


	connect(this, SIGNAL(signal_MapMouseMoveEvent(QMouseEvent*)), this, SLOT(SlotMapMouseMoveEvent(QMouseEvent*)));



	/*connect(pViewManager->m_mainImg, &CImageView::signal_mouseReleased, this, &Luster_ImageView::signal_mouseReleased);
	connect(pViewManager->m_mainImg, &CImageView::signal_viewScaled, this, &Luster_ImageView::signal_viewScaled);*/
}

LibImageView::~LibImageView()
{
	if (drawing_geometry_ != nullptr)
	{
		delete drawing_geometry_;
		drawing_geometry_ = nullptr;
	}	
	
	if (mutex_)
	{
		CloseHandle(mutex_);
		mutex_ = NULL;
	}

	ClearHistory();
}


BaseGeo* LibImageView::addGeo(BaseGeo* data, QColor color, QString name,QString tooltip)
{
	BaseGeo *item = addGeometry(data);
	if (item)
	{
		item->setText(name);
		item->setColor(color);
		//item->setActivedColor(color);
		item->setToolTip(tooltip);
		return item;
	}
	return NULL;
}



void LibImageView::drawGeometry(GEOMETRYTYPE type, IVDrawCallback cb, void* context, QString id, QColor draw_color)
{
	if (drawing_geometry_ != nullptr)
	{
		delete drawing_geometry_;
		drawing_geometry_ = nullptr;
	}
	if (type == E_Rect)
	{
		drawing_geometry_ = new GeoRect();
	}	
	else if (type == E_Point)
	{
		drawing_geometry_ = new GeoPoint();
	}
	else if (type == E_Path)
	{
		drawing_geometry_ = new GeoPath();
	}
	else if (type == E_Line)
	{
		drawing_geometry_ = new GeoLine();
	}
	else if (type == E_Ellipse)
	{
		drawing_geometry_ = new GeoEllipse();
	}
	else if (type == E_Circle)
	{
		drawing_geometry_ = new GeoCircle();
	}
	else if (type == E_Polygon)
	{
		drawing_geometry_ = new GeoPolygon();
	}
	else if (type == E_Arc)
	{
		drawing_geometry_ = new GeoArc();
	}
	else if (type == E_Arraw)
	{
		drawing_geometry_ = new GeoArraw();
	}
	drawing_geometry_->color_ = draw_color;
	drawing_geometry_->id_ = id;
	m_outDrawCallback = cb;
	outside_context_ = context;
	drawing_ = true;
	update();
}

bool LibImageView::setImage(QString path, bool fitwindow)
{
	QImage image;
	image.load(path);
	return setImage(image, fitwindow);
}


bool LibImageView::setImage(QImage& image, bool fitwindow)
{
	if (image.isNull())
		return false;

	ori_image_size_ = image.size();
	image_size_ = QSize(ori_image_size_.width() / original_scale_, ori_image_size_.height() / original_scale_);

	if (image.isNull())
	{
		return false;
	}
	inited_ = true;

	show_image_ = image.copy(0, 0, image.width(), image.height());
	for (int i = 0; i < geometrys_.size(); i++)
	{
		if (geometrys_[i] != nullptr)
			geometrys_[i]->SetImageSize(image_size_);
	}

	if (fitwindow)
	{
		fitToWindow();
	}

	update();

	setFocusPolicy(Qt::StrongFocus);

	return true;
}

bool LibImageView::setImage(const char *data, int width, int height, int channel, int bytesPerLine, bool fitwindow)
{
	if (data == nullptr)
	{
		return false;
	}
	bool result = false;
	if (1 == channel)
	{
		const uchar *pSrc = (const uchar*)data;
		QImage image(pSrc, width, height, bytesPerLine, QImage::Format_Grayscale8);
		image.setColorTable(g_color_table_gray8);
		result = setImage(image, fitwindow);
	}
	else if (channel == 3)
	{
		const uchar *pSrc = (const uchar*)data;
		QImage image(pSrc, width, height, bytesPerLine, QImage::Format_BGR888);
		result = setImage(image, fitwindow);
	}
	else if (channel == 4)
	{
		const uchar *pSrc = (const uchar*)data;
		QImage image(pSrc, width, height, bytesPerLine, QImage::Format_RGBA8888);
		result = setImage(image, fitwindow);
	}
	
	for (int i = 0; i < geometrys_.size(); i++)
	{
		if (geometrys_[i] != nullptr)
			geometrys_[i]->SetImageSize(image_size_);
	}

	if (fitwindow)
	{
		fitToWindow();
	}

	return result;
}


void LibImageView::setOriImageScale(double rat)
{
	if (rat < 0.000001)
	{
		return;
	}
	original_scale_ = rat;
	original_scale_ = original_scale_;
	image_size_ = QSize(ori_image_size_.width() / original_scale_, ori_image_size_.height() / original_scale_);
}



void LibImageView::clearImageView()
{
	MutexHelper mutex(mutex_);

	clearGeometrics();
	clearImage();
	updateGeometrics();
}


void LibImageView::clearGeometrics()
{
	MutexHelper mutex(mutex_);
	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		BaseGeo* geo = *iter;
		if (geo)
		{
			delete geo;
			geo = NULL;
		}
	}
	geometrys_.clear();
	updateGeometrics();
}

void LibImageView::showGeometrics(QVector<int> ids)
{
	if (ids.isEmpty())
	{
		setVisibleAll(true);
		return;
	}
}

void LibImageView::hideGeometrics(QVector<int> ids)
{
	if (ids.isEmpty())
	{
		setVisibleAll(false);
		return;
	}
}

BaseGeo* LibImageView::addRect(int x, int y, int w, int h, QString name, QColor color, QString tooltip, QString id)
{
	GeoRect *geo = new GeoRect;
	geo->setRect(x, y, w, h);
	geo->id_ = id;
	BaseGeo* new_item= addGeo(geo, color, name, tooltip);
	delete geo;

	return new_item;
}

BaseGeo* LibImageView::addEllipse(int cx, int cy, int w, int h, QString name, QColor color, QString tooltip, QString id)
{
	GeoEllipse* geo = new GeoEllipse;
	geo->setRect(cx - w / 2, cy - h / 2, w, h);
	geo->id_ = id;
	BaseGeo* new_item = addGeo(geo, color, name, tooltip);
	delete geo;
	return new_item;
}

BaseGeo* LibImageView::addPoint(int x, int y, QString name, QColor color, QString tooltip, QString id)
{
	GeoPoint* geo = new GeoPoint;
	geo->addPoint(x, y);
	geo->id_ = id;
	BaseGeo* new_item = addGeo(geo, color, name, tooltip);
	delete geo;
	return new_item;
}

BaseGeo* LibImageView::addPoints(QVector<QPoint> points, QString name, QColor color, QString tooltip, QString id)
{
	GeoPath* geo = new GeoPath;
	geo->setPoints(points);
	geo->id_ = id;
	BaseGeo* new_item = addGeo(geo, color, name, tooltip);
	delete geo;
	return new_item;
}

BaseGeo* LibImageView::addPolygon(QVector<QPoint> points, QString name, QColor color, QString tooltip, QString id)
{
	GeoPolygon* geo = new GeoPolygon;
	geo->setPoints(points);
	geo->id_ = id;
	BaseGeo* new_item = addGeo(geo, color, name, tooltip);
	delete geo;
	return new_item;
}


BaseGeo* LibImageView::getActivedGeometryInfo()
{
	return actived_geometry_;
}


BaseGeo* LibImageView::addGeometry(BaseGeo* data)
{
	if (data == nullptr) 
		return nullptr;

	
	if (data)
	{
		BaseGeo* new_data = NewGeo(data);

		new_data->SetImageSize(ori_image_size_);
		geometrys_.append(new_data);		
		connect(new_data, &BaseGeo::signal_GeoViewChanged, this, &LibImageView::slot_GeoViewChanged);
		connect(new_data, &BaseGeo::signal_RegionLimited, this, &LibImageView::slot_RegionLimited);		

		return new_data;
	}
	return nullptr;
}


void LibImageView::removeCurrentGeometry()
{
	if (actived_geometry_ == NULL)
	{
		return;
	}

	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		BaseGeo* geo = *iter;
		if (geo ==actived_geometry_)
		{
			if (geo)
			{
				delete geo;
				geo = NULL;
			}
			geometrys_.removeOne(*iter);
			break;
		}
	}

	updateGeometrics();
}


void LibImageView::removeGeometry(BaseGeo* geo)
{
	if (geo==NULL)
	{
		return;
	}

	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		BaseGeo* iter_geo = *iter;
		if (geo == iter_geo)
		{
			if (iter_geo)
			{
				delete iter_geo;
				iter_geo = NULL;
			}
			

			if (geo== actived_geometry_)
			{
				actived_geometry_ = NULL;
			}

			geometrys_.removeOne(*iter);
			break;
		}
	}
}



void LibImageView::updateGeometrics()
{	
	actived_geometry_ = nullptr;

	update();
}



void LibImageView::deActiveAll()
{
	QVector<BaseGeo*> geometrys;
	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		(*iter)->setActive(false);
	}	
}

//设置所有几何体可见状态
void LibImageView::setVisibleAll(bool state)
{
	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		(*iter)->setHide(!state);
	}

	updateGeometrics();
}



void LibImageView::drawFinished(bool finished)
{
	MutexHelper mutex(mutex_);
	if (!finished)
	{
		m_outDrawCallback(drawing_geometry_,outside_context_);	
		return;
	}

	if (!drawing_geometry_)
	{
		m_outDrawCallback(drawing_geometry_, outside_context_);
		return;
	}	

	if (drawing_geometry_ != nullptr)
	{	
		
		addGeometry(drawing_geometry_);

		BaseGeo temp_geo(drawing_geometry_);
		
		delete drawing_geometry_;
		drawing_geometry_ = nullptr;

		m_outDrawCallback(&temp_geo, outside_context_);

		
	}	
}

void LibImageView::slot_GeoViewChanged()
{
	emit signal_GeoViewChanged();
}

void LibImageView::slot_RegionLimited()
{
	RepaintImage();
}


void LibImageView::fitToWindow()
{
	if (image_size_.width() <= 2 || image_size_.height() <= 2)
	{
		scale_ = 0.01;
		top_left_.setX(0);
		top_left_.setY(0);
		setImagePosSize(top_left_, scale_);
		return;
	}

	double ratW = (double)rect().width() / image_size_.width();
	double ratH = (double)rect().height() / image_size_.height();

	if (ratW < ratH)
	{
		scale_ = ratW;
		top_left_.setX(0);
		top_left_.setY((image_size_.height() - rect().height() / scale_) / 2);
	}
	else
	{
		scale_ = ratH;
		top_left_.setY(0);
		top_left_.setX((image_size_.width() - rect().width() / scale_) / 2);
	}

	setImagePosSize(top_left_, scale_);
	emit signal_viewScaled(scale_);
}

void LibImageView::disableActiveGeometry(bool disable)
{
	enable_active_geo_ = !disable;
}



void LibImageView::scaleImage(double ratio)
{
	if (ratio < 0.00001 || ratio>100000)
	{
		return;
	}
	QPoint point = mapFromGlobal(this->geometry().center());

	current_sel_ptInImgee_.setX(point.x() / scale_ + top_left_.x());
	current_sel_ptInImgee_.setY(point.y() / scale_ + top_left_.y());

	scale_ *= ratio;

	top_left_.setX(current_sel_ptInImgee_.x() - point.x() / scale_);
	top_left_.setY(current_sel_ptInImgee_.y() - point.y() / scale_);

	RepaintImage();
	emit signal_viewScaled(scale_);
}

void LibImageView::getRectImage(QImage& image, QRect rect)
{
	rect = QRect(rect.x() * original_scale_, rect.y() * original_scale_ ,
		rect.width() * original_scale_, rect.height() * original_scale_);

	QRect imgRect(QPoint(0, 0), show_image_.size());
	if (!imgRect.intersected(rect).isValid())
	{
		image = QImage();
		return;
	}
	image = show_image_.copy(rect);
}
void LibImageView::getCursorPos(int& x, int& y)
{
	QPoint point = mapFromGlobal(QCursor::pos());

	x = point.x()/ scale_ + top_left_.x();
	y = point.y()/ scale_ + top_left_.y();
}

void LibImageView::CancelDraw()
{
	if (drawing_geometry_ != nullptr)
	{
		delete drawing_geometry_;
		drawing_geometry_ = nullptr;
	}

	drawing_ = false;

	update();
}

void LibImageView::clearImage()
{
	QImage img = QImage(1, 1, QImage::Format_Grayscale8);//清空图像
	setBkColor(QColor(220, 220, 220));
	setImage(img,false);
}



void LibImageView::RepaintImage()
{
	setImagePosSize(top_left_, scale_);
}



void LibImageView::updateActivedGeometry(QPoint postion, QPoint point)
{
	if (geometrys_.empty()) return;

	actived_geometry_ = nullptr;

	QVector<BaseGeo*> candiGeos;
	for (int k = 0; k < geometrys_.size(); k++)
	{
		BaseGeo* geo = geometrys_[k];
		if (geo == nullptr)
		{
			continue;
		}
		geo->deActive();

		if (geo->checkInGeo(point, enable_active_geo_)
			|| geo->checkAjust(postion,top_left_,point,scale_))
		{
			candiGeos.append(geo);
		}
	}
	actived_geometry_ = BaseGeo::selectIntersectionGeos(candiGeos, point);
	if (actived_geometry_)
	{
		actived_geometry_->setActive();
		AddHistory();
	}

	update();
}

void LibImageView::drawTempGeomety(QPoint point, ImageViewDefine::E_MouseState state)
{
	if (drawing_geometry_ != nullptr)
	{
		//完成绘制
		if (drawing_geometry_->drawNewGeomety(point, state))
		{
			drawing_ = false;			
			drawFinished(true);
		}
	}
	else 
	{
		drawFinished(true);
	}
	update();
}


void LibImageView::mousePressEvent(QMouseEvent* event)
{
	QPoint point = mapFromGlobal(event->globalPos());
	clicked_InImage_ = false;
	clicked_InImage_ = true;
	current_sel_ptInImgee_.setX(point.x() / scale_ + top_left_.x());
	current_sel_ptInImgee_.setY(point.y() / scale_ + top_left_.y());
	old_sel_ptInImage_ = current_sel_ptInImgee_;

	if (event->button() == Qt::LeftButton)
	{
		left_button_down_ = true;

		drag_imge_ = true;

		//绘制新几何体
		if (drawing_)
		{
			drawTempGeomety(current_sel_ptInImgee_, ImageViewDefine::E_LDown);
			return;
		}

		//判断是否调整尺寸
		if (actived_geometry_ != nullptr)
		{
			ajust_geometry_ = actived_geometry_->checkAjust(point,top_left_,current_sel_ptInImgee_, scale_);
		}

		//判断移动位置
		if (!ajust_geometry_)
		{
			updateActivedGeometry(point, current_sel_ptInImgee_);
			if (drag_mode_ && actived_geometry_ != nullptr)
			{
				drag_geometry_ = actived_geometry_->checkMove(current_sel_ptInImgee_);
			}
		}

		emit signal_mousePressed(current_sel_ptInImgee_.x(), current_sel_ptInImgee_.y());
	}
	else if (event->button() == Qt::RightButton)
	{
		//绘制新几何体
		if (drawing_)
		{
			drawTempGeomety(current_sel_ptInImgee_, ImageViewDefine::E_RDown);
		}
		else
		{
			//判断移动位置
			if (!ajust_geometry_)
			{
				updateActivedGeometry(point,current_sel_ptInImgee_);
			}

			if (actived_geometry_ != nullptr)
			{
				if (actived_geometry_->rightButtonDown(point, top_left_, current_sel_ptInImgee_, scale_))
				{
					RepaintImage();
					return;
				}
			}
			right_button_down_ = true;
			emit signal_rButtonPressed(current_sel_ptInImgee_.x(), current_sel_ptInImgee_.y());
		}
	}

}

void LibImageView::mouseReleaseEvent(QMouseEvent*)
{	
	if (drag_imge_
		|| drag_geometry_)
	{
		AddHistory();
	}


	left_button_down_ = false;
	drag_imge_ = false;
	drag_geometry_ = false;
	ajust_geometry_ = false;
	

	//绘制新几何体
	if (drawing_)
	{
		drawTempGeomety(current_sel_ptInImgee_, ImageViewDefine::E_MouseUp);
	}

	if (right_button_down_)
	{
		emit signal_rButtonUp(current_sel_ptInImgee_.x(), current_sel_ptInImgee_.y());
		right_button_down_ = false;
	}

	if (clicked_InImage_)
	{
		emit signal_mouseReleased(current_sel_ptInImgee_.x(), current_sel_ptInImgee_.y());
	}
}

void LibImageView::SlotMapMouseMoveEvent(QMouseEvent* event)
{
	QPoint point = mapFromGlobal(event->globalPos());
	current_sel_ptInImgee_.setX(point.x() / scale_ + top_left_.x());
	current_sel_ptInImgee_.setY(point.y() / scale_ + top_left_.y());

	emit signal_mouseMoved(current_sel_ptInImgee_.x(), current_sel_ptInImgee_.y());

	if (auto_cursor_
		&& !ajust_geometry_)
	{
		bool find_geo = false;
		for (int k = 0; k < geometrys_.size(); k++)
		{
			BaseGeo* geo = geometrys_[k];
			if (geo == nullptr)
			{
				continue;
			}
			if (geo->checkAjust(point, top_left_, current_sel_ptInImgee_, scale_))
			{
				find_geo = true; 
				if (!drawing_)
				{
					setCursor(Qt::PointingHandCursor);
				}
				break;
			}
			else if (geo->checkInGeo(current_sel_ptInImgee_, enable_active_geo_))
			{
				find_geo = true;
				if (!drawing_)
				{
					setCursor(Qt::SizeAllCursor);
				}
				
				break;
			}
		}

		if (drawing_)
		{
			setCursor(Qt::CrossCursor);
		}
		else if (!find_geo)
		{
			if (left_button_down_)
			{
				setCursor(Qt::ClosedHandCursor);
			}
			else
				setCursor(Qt::OpenHandCursor);
		}
	}


	if (!left_button_down_)
	{
		return;
	}

	int m_nXDrag = current_sel_ptInImgee_.x() - old_sel_ptInImage_.x();
	int m_nYDrag = current_sel_ptInImgee_.y() - old_sel_ptInImage_.y();

	if (drawing_)
	{
		drawTempGeomety(current_sel_ptInImgee_, ImageViewDefine::E_Move);
	}
	else if (ajust_geometry_
		&& actived_geometry_
		&& (image_ops_type_ == e_Auto
			|| image_ops_type_ == e_GeosType))
	{
		actived_geometry_->ajust(QPoint(m_nXDrag, m_nYDrag));
		update();
		old_sel_ptInImage_ = current_sel_ptInImgee_;


	}
	else if (drag_geometry_
		&& actived_geometry_
		&& event->modifiers() != Qt::ControlModifier
		&& (image_ops_type_ == e_Auto
			|| image_ops_type_ == e_GeosType))
	{
		actived_geometry_->move(QPoint(m_nXDrag, m_nYDrag));
		update();
		old_sel_ptInImage_ = current_sel_ptInImgee_;
	}
	else if (drag_imge_
		&& event->modifiers() != Qt::ControlModifier
		&& (image_ops_type_ == e_Auto
			|| image_ops_type_ == e_ImageType))
	{
		top_left_.setX(top_left_.x() - m_nXDrag);
		top_left_.setY(top_left_.y() - m_nYDrag);
		RepaintImage();
	}

	mouse_postion_ = event->globalPos();
	time_counter_ = 0;
	mouse_in_ = true;
	if (QToolTip::isVisible())
	{
		QToolTip::hideText();
	}

	BaseGeo* move_geo = NULL;
	if (drawing_)
	{
		move_geo = drawing_geometry_;

	}
	else
	{
		move_geo = getActivedGeometryInfo();
	}

	if (move_geo
		&& move_geo->rect_.height() != 0
		&& move_geo->rect_.width() != 0
		&& (move_geo->id_ == RectDrawString
			|| move_geo->id_ == EllipseDrawString
			|| move_geo->id_ == PolyDrawString))
	{
		QPoint cur_point = event->pos();
		QPoint map_point = QPoint(rect().width(), rect().height());
		if (cur_point.y() >= map_point.y() * 0.9
			&& m_nYDrag > 0)
		{
			top_left_.setY(top_left_.y() + 1);

		}

		if (cur_point.x() >= map_point.x() * 0.9
			&& m_nXDrag > 0)
		{
			top_left_.setX(top_left_.x() + 1);
		}

		update();
	}
}

void LibImageView::mouseMoveEvent(QMouseEvent* event)
{
	
	emit signal_MapMouseMoveEvent(event);
}

void LibImageView::resizeEvent(QResizeEvent*)
{	
	if (scale_<0.5)
	{
		fitToWindow();
	}
	
}

void LibImageView::wheelEvent(QWheelEvent* event)
{
	//QPoint point = mapFromGlobal(event->globalPos());
	QPoint point = mapFromGlobal(QPoint(event->globalPosition().x(), event->globalPosition().y()));
	//QPoint point = event->pixelDelta();
	current_sel_ptInImgee_.setX(point.x() / scale_ + top_left_.x());
	current_sel_ptInImgee_.setY(point.y() / scale_ + top_left_.y());
	if (event->angleDelta().y() > 0)//滚轮上滚
	{
		scale_ *= 1.2;
	}
	else
	{
		scale_ *= 0.8333;
	}

	top_left_.setX(current_sel_ptInImgee_.x() - int((point.x()) / scale_));
	top_left_.setY(current_sel_ptInImgee_.y() - int((point.y()) / scale_));

	RepaintImage();
	emit signal_viewScaled(scale_);
}

void LibImageView::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Delete)
	{
		removeCurrentGeometry();
	}


}

void LibImageView::slot_timeout()
{
	if (!mouse_in_)
	{
		return;
	}
	time_counter_++;

	if (time_counter_ > 9)
	{
		if (!QToolTip::isVisible())
		{			
			BaseGeo* geo = getActivedGeometryInfo();
			if (geo
				&& !geo->toolTip_.isEmpty())
			{
				QToolTip::showText(QCursor::pos(), geo->toolTip_);//,nullptr,QRect(),950);
			}
		}
		time_counter_ = 0;
	}
}


void LibImageView::setBkColor(QColor color)
{
	back_brush_ = QBrush(color);
}


void LibImageView::setImageSize(double scale)
{
	scale_ = scale > 0.0000001 ? scale : 0.0000001;
	update();
}
void LibImageView::setImagePos(QPoint topleft)
{
	top_left_.setX(topleft.x());
	top_left_.setY(topleft.y());
	update();
}
void LibImageView::setImagePosSize(QPoint topleft, double scale)
{
	top_left_.setX(topleft.x());
	top_left_.setY(topleft.y());
	scale_ = scale > 0.0000001 ? scale : 0.0000001;
	update();
}
void LibImageView::setImagePosX(int x)
{
	top_left_.setX(x);
	update();
}
void LibImageView::setImagePosY(int y)
{
	top_left_.setY(y);
	update();
}


void LibImageView::setPixColor(int x, int y, QColor color)
{
	/*int new_x = int((x - m_validRegion.left()) / m_scale + m_topleft.x() + 0.5);
	int new_y = int((y - m_validRegion.top()) / m_scale + m_topleft.y() + 0.5);*/

	if (!show_image_.isNull()
		&& x>=0
		&& x<show_image_.width()
		&& y>=0
		&& y<show_image_.height())
	{
		show_image_.setPixelColor(QPoint(x, y), color);
	}	
}

QColor LibImageView::getPixColor(int x, int y)
{
	/*x = x * m_oriScale + 0.5;
	y = y * m_oriScale + 0.5;*/
	QRect rect = QRect(QPoint(0, 0), show_image_.size());
	if (!rect.contains(QPoint(x, y)))
	{
		return QColor(0, 0, 0);
	}

	return show_image_.pixelColor(x,y);
}


void LibImageView::paintEvent(QPaintEvent* event)
{
	MutexHelper mutex(mutex_);
	Q_UNUSED(event);
	if (!inited_) 
		return;

	if (show_image_.isNull())
	{
		return;
	}


	QRect bkrect = rect();

	QPainter painter(this);
	painter.setBackground(back_brush_);
	painter.eraseRect(rect());
	painter.setRenderHint(QPainter::Antialiasing, true);

	painter.save();
	painter.scale(scale_ / original_scale_, scale_ / original_scale_);
	QPointF point1 = QPointF(0, 0);
	double x = top_left_.x() * original_scale_;
	double y = top_left_.y() * original_scale_;
	double w = show_image_.width() - x;
	double h = show_image_.height() - y;
	QRectF rect2 = QRectF(x, y, w, h);
	
	if (show_image_.width()>1
		&& show_image_.height()>1)
	{
		painter.drawImage(point1, show_image_, rect2);
	}
	painter.restore();

	if (drawing_geometry_ != nullptr)
	{
		drawing_geometry_->draw(painter, top_left_, scale_);
		QString text;
		if (drawing_geometry_->type_ == E_Point)
			text = QString::fromLocal8Bit("● 开始绘制点:左键单击绘制");	
		else if (drawing_geometry_->type_ == E_Arc)
			text = QString::fromLocal8Bit("● 开始绘制弧:左键按下开始绘制，松开停止");
		else if (drawing_geometry_->type_ == E_Ellipse)
			text = QString::fromLocal8Bit("● 开始绘制椭圆:左键按下开始绘制，松开停止");
		else if (drawing_geometry_->type_ == E_Circle)
			text = QString::fromLocal8Bit("● 开始绘制圆:左键按下开始绘制，松开停止");
		else if (drawing_geometry_->type_ == E_Arraw)
			text = QString::fromLocal8Bit("● 开始绘制箭头:左键按下开始绘制，松开停止");
		else if (drawing_geometry_->type_ == E_Line)
			text = QString::fromLocal8Bit("● 开始绘制直线:左键按下开始绘制，松开停止");
		else if (drawing_geometry_->type_ == E_Rect)
			text = QString::fromLocal8Bit("● 开始绘制矩形:左键按下开始绘制，松开停止");	
		else if (drawing_geometry_->type_ == E_Path)
			text = QString::fromLocal8Bit("● 开始绘制路径:\n左键按下开始绘制，右键松开停止");	
		else if (drawing_geometry_->type_ == E_Polygon)
			text = QString::fromLocal8Bit("● 开始绘制多边形:左键按下开始绘制，右键松开停止");

		if (drawing_geometry_->id_== EllipseDrawString
			|| drawing_geometry_->id_==CircleDrawString
			|| drawing_geometry_->id_==RectDrawString)
		{
			text+= QString::fromLocal8Bit("。回车确认");
		}
		QFont font;
		font.setPointSizeF(15);
		font.setBold(true);
		font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
		painter.setPen(QPen(QColor(255, 31, 32)));
		painter.setFont(font);
		painter.drawText(5, 30, text);

	}
	if (geometrys_.size() > 0)
	{
		for (int i = 0; i < geometrys_.size(); i++)
		{
			if (geometrys_[i] != nullptr)
				geometrys_[i]->draw(painter, top_left_, scale_);
		}
	}
}

QSize LibImageView::getImageSize()
{
	return image_size_;
}


BaseGeo* LibImageView::findGeo(QString id)
{
	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		BaseGeo* geo = *iter;
		if (geo->id_==id)
		{
			return geo;
		}
	}

	return NULL;
}


void LibImageView::ActiveGeo(BaseGeo* data)
{
	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		BaseGeo* geo = *iter;
		if (geo)
		{
			geo->actived_ = false;
		}
	}

	if (data)
	{
		data->actived_ = true;
	}	

	actived_geometry_ = data;

	update();
}


void LibImageView::setOpeType(ImageViewDefine::EImageOpsType type)
{
	image_ops_type_ = type;
}


void LibImageView::AutoCursor(bool cursor)
{
	auto_cursor_ = cursor;
}


BaseGeo* LibImageView::NewGeo(BaseGeo* geo)
{
	BaseGeo* new_data = NULL;
	switch (geo->type_)
	{
	case E_Point:
		new_data = new GeoPoint(geo);
		break;
	case E_Ellipse:
		new_data = new GeoEllipse(geo);
		break;
	case E_Line:
		new_data = new GeoLine(geo);
		break;
	case E_Rect:
		new_data = new GeoRect(geo);
		break;
	case E_Path:
		new_data = new GeoPath(geo);
		break;
	case E_Polygon:
		new_data = new GeoPolygon(geo);
		break;
	case E_Arc:
		new_data = new GeoArc(geo);
		break;
	case E_Arraw:
		new_data = new GeoArraw(geo);
		break;
	case E_Circle:
		new_data = new GeoCircle(geo);
		break;
	default:
		return NULL;
		break;
	}

	return new_data;
}


void  LibImageView::AddHistory()
{
	HisGeom geos;
	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{		
		BaseGeo* geo=NewGeo(*iter);
		if (geo==NULL)
		{
			return;
		}
		geos.geometrics_.push_back(geo);
	}

	if (actived_geometry_)
	{
		geos.active_id_ = actived_geometry_->id_;
	}
	else
		geos.active_id_ = "";
	
	geos.left_top_ = top_left_;
	his_geometrys_.push_back(geos);

	history_index_ = his_geometrys_.size()-1;

	if (his_geometrys_.size() > 50)
	{
		HisGeom item = his_geometrys_.front();
		QVector<BaseGeo*>::iterator iter = item.geometrics_.begin();
		for (; iter != item.geometrics_.end(); iter++)
		{
			BaseGeo* geo = *iter;
			if (geo)
			{
				delete geo;
				geo = NULL;
			}
		}
		item.geometrics_.clear();
		his_geometrys_.pop_front();
	}
}


void  LibImageView::ForwordHistory()
{
	if (0 == his_geometrys_.size())
	{
		return;
	}

	if (history_index_+1>= his_geometrys_.size())
	{
		return;
	}	

	history_index_++;

	clearGeometrics();

	QVector<BaseGeo*> his_geo = his_geometrys_[history_index_].geometrics_;

	QVector<BaseGeo*>::iterator iter = his_geo.begin();
	for (; iter != his_geo.end(); iter++)
	{
		BaseGeo* geo = NewGeo(*iter);
		if (geo == NULL)
		{
			return;
		}

		if (his_geometrys_[history_index_].active_id_ == geo->id_)
		{
			ActiveGeo(geo); 
			actived_geometry_ = geo;
		}
		geometrys_.push_back(geo);
	}

	//top_left_ = his_geometrys_[history_index_].left_top_;
	update();

}

void  LibImageView::BackForwordHistory()
{
	if (history_index_==0)
	{
		return;
	}

	history_index_--;

	if (history_index_>= his_geometrys_.size())
	{
		return;
	}

	clearGeometrics();

	if (his_geometrys_.size()==0)
	{
		return;
	}

	QVector<BaseGeo*> his_geo = his_geometrys_[history_index_].geometrics_;

	QVector<BaseGeo*>::iterator iter = his_geo.begin();
	for (; iter != his_geo.end(); iter++)
	{
		BaseGeo* geo = NewGeo(*iter);
		if (geo == NULL)
		{
			return;
		}

		if (his_geometrys_[history_index_].active_id_ == geo->id_)
		{
			ActiveGeo(geo);
			actived_geometry_ = geo;
		}
		
		geometrys_.push_back(geo);
	}

	//top_left_ = his_geometrys_[history_index_].left_top_;
	update();

	
}


void LibImageView::ClearHistory()
{
	history_index_ = 0;
	QList<HisGeom>::iterator iter_all = his_geometrys_.begin();
	for (; iter_all != his_geometrys_.end(); iter_all++)
	{
		QVector<BaseGeo*>::iterator iter = (*iter_all).geometrics_.begin();
		for (; iter != (*iter_all).geometrics_.end(); iter++)
		{
			BaseGeo* geo = *iter;
			if (geo)
			{
				delete geo;
				geo = NULL;
			}
		}
		(*iter_all).geometrics_.clear();
	}
	his_geometrys_.clear();
}


bool LibImageView::CanForwardHistory()
{
	if (0 == his_geometrys_.size())
	{
		return false;
	}

	if (history_index_ + 1 >= his_geometrys_.size())
	{
		return false;
	}

	return true;
}

bool LibImageView::CanBackForwardHistory()
{
	if (history_index_ == 0)
	{
		return false;
	}

	return true;

}


QVector<QString> LibImageView::GetAllGeometryID()
{
	QVector<QString> ids;

	QVector<BaseGeo*>::iterator iter = geometrys_.begin();
	for (; iter != geometrys_.end(); iter++)
	{
		BaseGeo* iter_geo = *iter;
		ids.push_back(iter_geo->id_);
	}

	return ids;
}