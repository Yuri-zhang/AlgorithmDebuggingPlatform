#include "AlgorithmDebuggingPlatform.h"
#include <Windows.h>
#include <WinUser.h>
#include <atlconv.h>
#include <QMessageBox>
#include <QProcess>
#include <QWindow>
#include <QDebug>
#include <QFileDialog>
#include "yyjson.h"
#include "../LibImageView/LibImageView.h"

//自定义结构体
struct handle_data {
	unsigned long process_id;
	HWND best_handle;
};

BOOL IsMainWindow(HWND handle);
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);
HWND FindMainWindow(unsigned long process_id);//通过进程id号获取主窗口句柄

BOOL IsMainWindow(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !IsMainWindow(handle)) {
		return TRUE;
	}
	data.best_handle = handle;
	return FALSE;
}

//通过进程id号获取主窗口句柄
HWND FindMainWindow(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.best_handle = 0;
	EnumWindows(EnumWindowsCallback, (LPARAM)&data);
	return data.best_handle;
}

void drawCallBack(BaseGeo* geos, void* context)
{
	if (context)
	{
		AlgorithmDebuggingPlatform* mainwidow = (AlgorithmDebuggingPlatform*)context;
		mainwidow->DrawFinish(geos);
	}
}

AlgorithmDebuggingPlatform::AlgorithmDebuggingPlatform(QWidget* parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	showIDE();
	m_imageShow = new LibImageView(NULL);
	ui.verticalLayoutShowImg->addWidget(m_imageShow);

	InitSystemConnection();
	InitSystemConfigur();

	//临时测试用
	QFile file("D:\\AlgorithmDebuggingPlatform\\1.bmp");
	file.open(QIODevice::ReadOnly);
	QByteArray data = file.readAll();
	CurQImg = QImage::fromData(data);
	m_imageShow->setImage(CurQImg);
}

AlgorithmDebuggingPlatform::~AlgorithmDebuggingPlatform()
{

}

void AlgorithmDebuggingPlatform::DrawFinish(BaseGeo* geos)
{

}

int AlgorithmDebuggingPlatform::InitSystemConnection()
{
	connect(ui.action_vsCode, SIGNAL(triggered()), this, SLOT(showIDE()));
	connect(ui.action_DrawCircle, SIGNAL(triggered()), this, SLOT(on_btn_circle_clicked()));
	connect(ui.action_DrawRect, SIGNAL(triggered()), this, SLOT(on_btn_drawRect_clicked()));
	connect(ui.action_DrawEllipse, SIGNAL(triggered()), this, SLOT(on_btn_drawellips_clicked()));
	connect(ui.action_DrawPolygon, SIGNAL(triggered()), this, SLOT(on_btn_drawpolygen_clicked()));
	connect(ui.action_DrawPoint, SIGNAL(triggered()), this, SLOT(on_btn_drawpoint_clicked()));
	connect(ui.action_DrawLine, SIGNAL(triggered()), this, SLOT(on_btn_drawline_clicked()));
	//connect(m_imageShow, &LibImageView::signal_mouseReleased, this, &AlgorithmDebuggingPlatform::slot_mouseReleased);
	//connect(m_imageShow, &LibImageView::signal_mouseMoved, this, &AlgorithmDebuggingPlatform::mouseMoveEvent);
	connect(ui.action_NewProject, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.action_ReadImagine, SIGNAL(triggered()), this, SLOT(readImagine()));
	return 1;
}

int AlgorithmDebuggingPlatform::InitSystemConfigur()
{
	yyjson_read_flag flag = YYJSON_READ_ALLOW_TRAILING_COMMAS;
	yyjson_read_err err;
	yyjson_doc* doc = yyjson_read_file("./Config/Setting.json", flag, NULL, &err);
	yyjson_val* val = yyjson_doc_get_root(doc);
	yyjson_val* curVal = yyjson_obj_get(val, "curTaskPath");
	std::string pointX = yyjson_get_str(curVal);
	
	return 1;
}

void AlgorithmDebuggingPlatform::slot_mouseReleased(int x, int y)
{
}

void AlgorithmDebuggingPlatform::on_btn_drawRect_clicked()
{
	m_imageShow->drawGeometry(E_Rect, drawCallBack, this);
}

void AlgorithmDebuggingPlatform::on_btn_drawellips_clicked()
{
	m_imageShow->drawGeometry(E_Ellipse, drawCallBack, this);
}

void AlgorithmDebuggingPlatform::on_btn_drawpoint_clicked()
{
	m_imageShow->drawGeometry(E_Point, drawCallBack, this);
}

void AlgorithmDebuggingPlatform::on_btn_drawpoints_clicked()
{
	m_imageShow->drawGeometry(E_Path, drawCallBack, this);
}

void AlgorithmDebuggingPlatform::on_btn_drawpolygen_clicked()
{
	m_imageShow->drawGeometry(E_Polygon, drawCallBack, this);
}

void AlgorithmDebuggingPlatform::on_btn_hideall_clicked()
{
	m_imageShow->hideGeometrics();
}

void AlgorithmDebuggingPlatform::on_btn_showall_clicked()
{
	m_imageShow->showGeometrics();
}

void AlgorithmDebuggingPlatform::on_btn_showsome_clicked()
{
	QVector<int> ids;
	for (int i = 0; i < 3 && i < m_geoIDS.size(); i++)
	{
		ids.append(m_geoIDS[i]);
	}
	m_imageShow->showGeometrics(ids);
}

void AlgorithmDebuggingPlatform::on_btn_hidesome_clicked()
{
	/*  QVector<int> ids;
	  for(int i=0;i<2 && i<m_geoIDS.size();i++)
	  {
		  ids.append(m_geoIDS[i]);
	  }
	  m_imageShow->hideGeometrics(ids);*/
	  //DebugContour countours;
	  //if (countours.ReadFile("E:/Test/debug.contour"))
	  //{
	  //	for (size_t i = 0; i < countours.Contours_.size(); i++)
	  //	{
	  //		m_imageShow->addPolygon(countours.Contours_[i]);
	  //	}
	  //	m_imageShow->updateGeometrics();
	  //}
	static double rat = 1.0;
	rat *= 0.8;
	m_imageShow->setOriImageScale(rat);
	m_imageShow->update();
}

void AlgorithmDebuggingPlatform::on_btn_circle_clicked()
{
	m_imageShow->drawGeometry(E_Circle, drawCallBack, this);
}

void AlgorithmDebuggingPlatform::on_btn_clear_clicked()
{
	m_imageShow->clearGeometrics();
}

void AlgorithmDebuggingPlatform::mouseMoveEvent(int x, int y)
{
	/*m_imageShow->setPixColor(x,y, QColor(255, 0, 0));
	m_imageShow->update();*/
}

void AlgorithmDebuggingPlatform::on_btn_drawline_clicked()
{
	m_imageShow->drawGeometry(E_Line, drawCallBack, this);
}

void AlgorithmDebuggingPlatform::newProject()
{
	QString fname;
	fname = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("新建文件夹"), "Project", QString::fromLocal8Bit("*.新建文件夹"));
	QString dir = fname.left(fname.lastIndexOf("."));
	QString fileName = dir.right(dir.length()-1-dir.lastIndexOf("/"));
	QDir tempDir(dir);
	bool ismkdir = tempDir.mkpath(dir);
	dir = dir + "/" + fileName + ".task";
	QFile file(dir);
	bool bRet = file.open(QIODevice::ReadWrite | QIODevice::Append);
}

void AlgorithmDebuggingPlatform::readImagine()
{
	QString filename;
	filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Choose Image"),"   ", tr("Images (*.*)"));

	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QByteArray data = file.readAll();
	CurQImg = QImage::fromData(data);
	m_imageShow->setImage(CurQImg);
}

int AlgorithmDebuggingPlatform::showIDE()
{
	QProcess* m_process = new QProcess(this);
	m_process->start("..//Microsoft VS Code//Code.exe", QStringList() << "");
	qint64 id = m_process->processId();//如果程序没有运行，将会返回0
	if (id == 0)
	{
		QMessageBox::information(NULL, "提示", "程序没有启动");
		return -1;
	}
	Sleep(2000);
	qDebug() << "Status: " << m_process->state();
	HWND mainwindowHwnd = FindMainWindow(id);
	qDebug() << "mainwindowHwnd: " << mainwindowHwnd;
	HWND frameIDE_Hwnd = (HWND)(ui.frameIDE->winId());
	SetParent(mainwindowHwnd, (HWND)(ui.frameIDE->winId()));
	WINDOWPLACEMENT lwndpl;
	GetWindowPlacement(frameIDE_Hwnd, &lwndpl);
	lwndpl.showCmd = 3;
	lwndpl.rcNormalPosition.left = 0;
	lwndpl.rcNormalPosition.top = 0;
	SetWindowPlacement(frameIDE_Hwnd, &lwndpl);
	MoveWindow(mainwindowHwnd, lwndpl.rcNormalPosition.left, lwndpl.rcNormalPosition.top,
		ui.frameIDE->size().width(), ui.frameIDE->size().height(), false);
	LONG lStyle = GetWindowLong(frameIDE_Hwnd, GWL_STYLE);
	SetWindowLong(frameIDE_Hwnd, GWL_STYLE, lStyle & ~WS_VISIBLE);
	SetWindowPos(frameIDE_Hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
	return 1;
}