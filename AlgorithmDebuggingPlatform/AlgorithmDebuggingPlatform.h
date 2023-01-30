#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AlgorithmDebuggingPlatform.h"

class LibImageView;
class BaseGeo;
class AlgorithmDebuggingPlatform : public QMainWindow
{
    Q_OBJECT

public:
    AlgorithmDebuggingPlatform(QWidget *parent = nullptr);
    ~AlgorithmDebuggingPlatform();
    void DrawFinish(BaseGeo* geos);
    int InitSystemConnection();
	int InitSystemConfigur();
    
	QAction** drawTool;
	LibImageView* m_imageShow;
	QVector<BaseGeo*>m_geos;
	QVector< unsigned long long> m_geoIDS;
	QImage CurQImg;						                          //当前显示图像


private:
    Ui::AlgorithmDebuggingPlatformClass ui;

private slots:
#pragma region "基础绘图槽函数"
	void slot_mouseReleased(int x, int y);

	void on_btn_drawRect_clicked();

	void on_btn_drawellips_clicked();

	void on_btn_drawpoint_clicked();

	void on_btn_drawpoints_clicked();

	void on_btn_drawpolygen_clicked();

	void on_btn_hideall_clicked();

	void on_btn_showall_clicked();

	void on_btn_showsome_clicked();

	void on_btn_hidesome_clicked();

	void on_btn_circle_clicked();

	void on_btn_clear_clicked();

	void mouseMoveEvent(int x, int y);

	void on_btn_drawline_clicked();

#pragma endregion

#pragma region "工具栏函数"
	void newProject();
	void readImagine();
	int showIDE();
#pragma endregion
};
