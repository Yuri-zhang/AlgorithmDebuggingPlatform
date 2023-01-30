#ifndef LUSTERIMAGEVIEW_H
#define LUSTERIMAGEVIEW_H
#include "Defines.h"
#include "Geometry/BaseGeo.h"
#include "Geometry/GeoRect.h"
#include "Geometry/GeoPath.h"
#include "Geometry/GeoPolygon.h"
#include "Geometry/GeoPoint.h"
#include "Geometry/GeoEllipse.h"
#include "Geometry/GeoLine.h"
#include "Geometry/GeoArc.h"
#include "Geometry/GeoArraw.h"
#include "Geometry/GeoCircle.h"
#include <QWidget>
#include <QPoint>
#include <QVector>
#include <QList>
#include <QAction>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <windows.h>
#include <QList>
#include< QKeyEvent>


typedef void(*IVDrawCallback)(BaseGeo*, void*);



class PictureWidget;
class BaseGeo;
class FrameWidget;
class LIBIMAGEVIEW_API LibImageView : public QWidget
{

	struct  HisGeom
	{
		QVector<BaseGeo*> geometrics_;
		QPoint left_top_;
		QString active_id_;
	};
    Q_OBJECT
public:
    LibImageView(QWidget *parent=NULL);
    ~LibImageView();


	/*
		功能：设置显示图像
		参数：path 图像路径
	*/
	bool setImage(QString path, bool fitwindow = true);

    /*
        功能：设置显示图像
        参数：data：图像数据指针； width：图像宽；height：图像高；channel：图像通道数；bytesPerLine：图像步长
    */
	bool setImage(const char *data, int width, int height, int channel, int bytesPerLine, bool fitwindow = true);

    /*
        功能：设置显示图像
        参数：image：图像数据
    */
	bool setImage(QImage& image,bool fitwindow=true);


	/*
		功能：设置图像区背景颜色
		参数：color：背景颜色
	*/
	void setBkColor(QColor color);


	/*
		功能：原图缩放比例，图像按缩略图显示，图形区域按原图显示
		参数：ratio：缩放比例
	*/
	void setOriImageScale(double ratio);

    /*
        功能：图像显示缩放比例
        参数：ratio：缩放比例，在现有比例的基础上乘该值
    */
    void scaleImage(double ratio);

    /*
        功能：获取显示图像的一部分
        参数：image：返回的结果，rect：目标区域
    */
    void getRectImage(QImage &image, QRect rect);

	/*
		功能：获取鼠标在图像中的位置
		参数：x,y：结果坐标
	*/
	void getCursorPos(int &x, int &y);
	
	/*
		功能：获取图像某点的颜色
		参数：x,y：图像坐标
	*/
	QColor getPixColor(int x, int y);


	/*****************************************************************************
	@description : 设置像素的颜色
	@param:	
	*****************************************************************************/
	void setPixColor(int x, int y, QColor color);

	/*
		功能：  获取当前选中图形信息
		返回值：图形信息
	*/
	BaseGeo* getActivedGeometryInfo();
	  

    /*
        功能：图像适应窗口
        参数：无
    */
    void fitToWindow();

	/*
		功能：禁止激活几何体
		参数：无
	*/
	void disableActiveGeometry(bool disable = true);

    /*
        功能：清空图像及图形
        参数：无
    */
    void clearImageView();


    /*
        功能：清空图形显示
        参数：无
    */
    void clearGeometrics();

    /*
        功能：隐藏所有图形
        参数：ids:待隐藏几何体id，如果为空将隐藏所有已填加几何体
    */
    void hideGeometrics(QVector<int> ids = QVector<int>());

    /*
        功能：显示所有图形，与hideGeometrics配合使用
        参数：ids:待显示几何体id，如果为空将显示所有已填加几何体
    */
    void showGeometrics(QVector<int> ids = QVector<int>());

    /*
        功能：  填加矩形
		返回值：几何体ID
        参数：color：矩形颜色；tooltip：鼠标悬浮时的提示语
    */
	BaseGeo* addRect(int x, int y, int w, int h, QString name="", QColor color = Qt::red, QString tooltip = "",QString id="");

    /*
        功能：  填加椭圆
		返回值：几何体ID
        参数：cx：中心横坐标；cy：中心纵坐标
    */
	BaseGeo* addEllipse(int cx, int cy, int w, int h, QString name = "", QColor color = Qt::red, QString tooltip = "", QString id = "");

    /*
        功能：  填加点
		返回值：几何体ID
    */
	BaseGeo* addPoint(int x, int y, QString name = "", QColor color = Qt::red, QString tooltip = "", QString id = "");

    /*
        功能：  填加点集，点集为一个整体，每个点下显示其序号
		返回值：几何体ID
    */
	BaseGeo* addPoints(QVector<QPoint> points, QString name = "", QColor color = Qt::red, QString tooltip = "", QString id = "");

    /*
        功能：  填加多边形
		返回值：几何体ID
    */
	BaseGeo* addPolygon(QVector<QPoint> points, QString name = "", QColor color = Qt::red, QString tooltip = "", QString id = "");



    /*
        功能：  填加几何体，允许在图像显示区调整几何体，且数据会同步被修改
		返回值：几何体ID
        参数：  geo：待显示几何体数据指针，几何体数据类型需来自GeometryData.h
    */
	//添加几何体，图形不可可视化修改，数据改变时调用update自动映射到图形
    //int addGeometry(AbstractGeo* geo);

	
    //添加几何体，图形改变时自动映射到数据，数据改变时需调用update自动映射到图形
	BaseGeo* addGeometry(BaseGeo* data);

    /*
        功能：绘制几何体
        参数：type：几何体类型，可选值有："DrawRect"、"DrawEllipse"、"DrawPoint"、"DrawPoints"、"DrawPolygon"
             callback：回调函数，绘制结束时调用
                       回调参数：1：绘制结果（矩形、椭圆返回左上角与右下角）
                               2：上下文指针（回传给用户，用户区分几何体从属）
             context：回调时将该参数回传
    */
    void drawGeometry(GEOMETRYTYPE  type, IVDrawCallback callback, void* context,QString id="",QColor draw_color= QColor(41, 242, 43));
    
  
	/*****************************************************************************
	@description : 删除图形
	@param:	
	*****************************************************************************/
	void removeGeometry(BaseGeo* data);

	/*****************************************************************************
	@description : 删除当前图形
	@param:	
	*****************************************************************************/
	void removeCurrentGeometry();

	/*****************************************************************************
	@description : 清空图像
	@param:	
	*****************************************************************************/
	void clearImage();

	/*****************************************************************************
	@description : 取消绘制
	@param:	
	*****************************************************************************/
	void CancelDraw();


	//更新图像显示（改变位置或尺度后更新）
	void RepaintImage();
	
	
	//设置图像位置及尺度
	void setImagePosSize(QPoint topleft, double scale);
	
	//获取图像大小
	QSize getImageSize();


	//重新显示几何体，填加或移除几何体后需调用该函数才能生效
	void updateGeometrics();	


	/*****************************************************************************
	@description : 根据id找到指定图形
	@param:	
	*****************************************************************************/
	BaseGeo* findGeo(QString id);


	/*****************************************************************************
	@description : 激活指定图形
	@param:	
	*****************************************************************************/
	void ActiveGeo(BaseGeo* data);

	/*****************************************************************************
	@description : 设置操作模式
	@param:	
	*****************************************************************************/
	void setOpeType(ImageViewDefine::EImageOpsType type);


	void AutoCursor(bool auto_cursor);

	void ForwordHistory();

	void BackForwordHistory();

	void AddHistory();

	void ClearHistory();
	
	bool CanForwardHistory();

	bool CanBackForwardHistory();

	QVector<QString> GetAllGeometryID();

 protected:
	 // 鼠标按下事件
	 virtual void mousePressEvent(QMouseEvent* event);
	 // 鼠标释放事件
	 virtual void mouseReleaseEvent(QMouseEvent* event);
	 // 鼠标移动事件
	 virtual void mouseMoveEvent(QMouseEvent* event);
	 // 设置窗体大小
	 virtual void resizeEvent(QResizeEvent* event);
	 // 鼠标滚轮事件
	 virtual void wheelEvent(QWheelEvent* event);

	 //删除当前几何体
	 virtual void keyPressEvent(QKeyEvent* event);

	 BaseGeo*  addGeo(BaseGeo* data, QColor color,QString name, QString tooltip);		

	//所有几何体取消激活
	void deActiveAll();

	//设置所有几何体可见状态
	void setVisibleAll(bool state);

	void setImageSize(double scale);

	void setImagePos(QPoint topleft);

	void setImagePosX(int x);

	void setImagePosY(int y);	

	BaseGeo* NewGeo(BaseGeo* geo);
	
private:

	//图形绘制完成后该函数被调用
	void drawFinished(bool finish);

	void updateActivedGeometry(QPoint position, QPoint point);

	void drawTempGeomety(QPoint, ImageViewDefine::E_MouseState);	

	void paintEvent(QPaintEvent* event);

signals:
	//有几何体图形被修改
	void signal_GeoViewChanged();
	void signal_mousePressed(int x, int y);
	void signal_mouseReleased(int x, int y);
	void signal_viewScaled(double ratio);
	void signal_rButtonPressed(int x,int y);
	void signal_rButtonUp(int x,int y);
	void signal_mouseMoved(int x, int y);
	void signal_ContextMenuEvent(QContextMenuEvent* event);

	void signal_MapMouseMoveEvent(QMouseEvent* event);
private slots:
	void slot_timeout();
	void slot_GeoViewChanged();
	void slot_RegionLimited();	

	void SlotMapMouseMoveEvent(QMouseEvent* event);
public:
	QPoint top_left_;						//图像可见部分左上角
	double scale_;							//图像缩放比例
	double original_scale_;                     //原图缩放比例
	BaseGeo* actived_geometry_;				//激活的几何体
	bool left_button_down_;						//左键按下
	bool right_button_down_;                     //右键按下
	bool drawing_;							//正在绘制几何体
	QSize ori_image_size_;						//记录当前图像尺寸
	QSize image_size_;						//记录当前图像尺寸
	BaseGeo* drawing_geometry_;
	QImage show_image_;
private:


	QVector<BaseGeo*> geometrys_;		  //所有待显示几何体

	int history_index_;

	QList<HisGeom> his_geometrys_;


	void* outside_context_;
	IVDrawCallback m_outDrawCallback;

	bool enable_active_geo_;
	bool drag_imge_;						//拖动图像
	bool drag_geometry_;					//拖动几何体
	bool ajust_geometry_;					//调整几何体
	bool drag_mode_;

	QPoint current_sel_ptInImgee_;				//当前鼠标在图像中的位置
	QPoint old_sel_ptInImage_;				//上次鼠标在图像中的位置



	bool clicked_InImage_;                  //鼠标点击在图上
	QAction add_contour_;
	
	QRect picture_rect_;//图像占用区域

	bool inited_;
	bool mouse_in_;//鼠标在显示范围
	QPoint mouse_postion_;//鼠标位置
	QTimer timer_;
	int time_counter_;
	QBrush back_brush_;//背景颜色
	HANDLE mutex_;

	bool auto_cursor_;

	ImageViewDefine::EImageOpsType image_ops_type_;
};

#endif
