/********************************************************************************
** Form generated from reading UI file 'AlgorithmDebuggingPlatform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMDEBUGGINGPLATFORM_H
#define UI_ALGORITHMDEBUGGINGPLATFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlgorithmDebuggingPlatformClass
{
public:
    QAction *action_DrawRect;
    QAction *action_DrawCircle;
    QAction *action_vsCode;
    QAction *action_DrawPolygon;
    QAction *action_DrawPoint;
    QAction *action_DrawLine;
    QAction *action_DrawEllipse;
    QAction *action_OrganizeWindows;
    QAction *action_NewProject;
    QAction *action_OpenProject;
    QAction *action_SaveProject;
    QAction *action_SaveAs;
    QAction *action_ReadImagine;
    QAction *actionNeaProject;
    QAction *actionOpenProject;
    QAction *actionSaveProject;
    QWidget *centralWidget;
    QTabWidget *tabWidgetMain;
    QWidget *tableDebug;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayoutShowImg;
    QFrame *frameIDE;
    QWidget *tableBatchProcess;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *AlgorithmDebuggingPlatformClass)
    {
        if (AlgorithmDebuggingPlatformClass->objectName().isEmpty())
            AlgorithmDebuggingPlatformClass->setObjectName(QString::fromUtf8("AlgorithmDebuggingPlatformClass"));
        AlgorithmDebuggingPlatformClass->resize(1920, 1080);
        action_DrawRect = new QAction(AlgorithmDebuggingPlatformClass);
        action_DrawRect->setObjectName(QString::fromUtf8("action_DrawRect"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../Resource/ic_DrawRect.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_DrawRect->setIcon(icon);
        action_DrawCircle = new QAction(AlgorithmDebuggingPlatformClass);
        action_DrawCircle->setObjectName(QString::fromUtf8("action_DrawCircle"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../Resource/ic_DrawCircle.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_DrawCircle->setIcon(icon1);
        action_vsCode = new QAction(AlgorithmDebuggingPlatformClass);
        action_vsCode->setObjectName(QString::fromUtf8("action_vsCode"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../Resource/ic_zoom_adjust_win_size.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_vsCode->setIcon(icon2);
        action_DrawPolygon = new QAction(AlgorithmDebuggingPlatformClass);
        action_DrawPolygon->setObjectName(QString::fromUtf8("action_DrawPolygon"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../Resource/ic_DrawPolygon.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_DrawPolygon->setIcon(icon3);
        action_DrawPoint = new QAction(AlgorithmDebuggingPlatformClass);
        action_DrawPoint->setObjectName(QString::fromUtf8("action_DrawPoint"));
        action_DrawPoint->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../Resource/ic_DrawPoint.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_DrawPoint->setIcon(icon4);
        action_DrawLine = new QAction(AlgorithmDebuggingPlatformClass);
        action_DrawLine->setObjectName(QString::fromUtf8("action_DrawLine"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../Resource/ic_DrawLine.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_DrawLine->setIcon(icon5);
        action_DrawEllipse = new QAction(AlgorithmDebuggingPlatformClass);
        action_DrawEllipse->setObjectName(QString::fromUtf8("action_DrawEllipse"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../Resource/ic_DrawEllipse.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_DrawEllipse->setIcon(icon6);
        action_OrganizeWindows = new QAction(AlgorithmDebuggingPlatformClass);
        action_OrganizeWindows->setObjectName(QString::fromUtf8("action_OrganizeWindows"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../Resource/ic_organize_windows.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_OrganizeWindows->setIcon(icon7);
        action_NewProject = new QAction(AlgorithmDebuggingPlatformClass);
        action_NewProject->setObjectName(QString::fromUtf8("action_NewProject"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../Resource/ic_new.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_NewProject->setIcon(icon8);
        action_OpenProject = new QAction(AlgorithmDebuggingPlatformClass);
        action_OpenProject->setObjectName(QString::fromUtf8("action_OpenProject"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../Resource/ic_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_OpenProject->setIcon(icon9);
        action_SaveProject = new QAction(AlgorithmDebuggingPlatformClass);
        action_SaveProject->setObjectName(QString::fromUtf8("action_SaveProject"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("../Resource/ic_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_SaveProject->setIcon(icon10);
        action_SaveAs = new QAction(AlgorithmDebuggingPlatformClass);
        action_SaveAs->setObjectName(QString::fromUtf8("action_SaveAs"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("../Resource/ic_save_as.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_SaveAs->setIcon(icon11);
        action_ReadImagine = new QAction(AlgorithmDebuggingPlatformClass);
        action_ReadImagine->setObjectName(QString::fromUtf8("action_ReadImagine"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("../Resource/ic_open_graphics_wnd.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_ReadImagine->setIcon(icon12);
        actionNeaProject = new QAction(AlgorithmDebuggingPlatformClass);
        actionNeaProject->setObjectName(QString::fromUtf8("actionNeaProject"));
        actionOpenProject = new QAction(AlgorithmDebuggingPlatformClass);
        actionOpenProject->setObjectName(QString::fromUtf8("actionOpenProject"));
        actionSaveProject = new QAction(AlgorithmDebuggingPlatformClass);
        actionSaveProject->setObjectName(QString::fromUtf8("actionSaveProject"));
        centralWidget = new QWidget(AlgorithmDebuggingPlatformClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidgetMain = new QTabWidget(centralWidget);
        tabWidgetMain->setObjectName(QString::fromUtf8("tabWidgetMain"));
        tabWidgetMain->setGeometry(QRect(0, 0, 1881, 1041));
        QFont font;
        font.setPointSize(25);
        tabWidgetMain->setFont(font);
        tabWidgetMain->setIconSize(QSize(100, 100));
        tableDebug = new QWidget();
        tableDebug->setObjectName(QString::fromUtf8("tableDebug"));
        verticalLayoutWidget = new QWidget(tableDebug);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 601, 551));
        verticalLayoutShowImg = new QVBoxLayout(verticalLayoutWidget);
        verticalLayoutShowImg->setSpacing(6);
        verticalLayoutShowImg->setContentsMargins(11, 11, 11, 11);
        verticalLayoutShowImg->setObjectName(QString::fromUtf8("verticalLayoutShowImg"));
        verticalLayoutShowImg->setContentsMargins(0, 0, 0, 0);
        frameIDE = new QFrame(tableDebug);
        frameIDE->setObjectName(QString::fromUtf8("frameIDE"));
        frameIDE->setGeometry(QRect(630, 10, 1200, 900));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameIDE->sizePolicy().hasHeightForWidth());
        frameIDE->setSizePolicy(sizePolicy);
        frameIDE->setLayoutDirection(Qt::LeftToRight);
        frameIDE->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 200);"));
        frameIDE->setFrameShape(QFrame::Panel);
        frameIDE->setFrameShadow(QFrame::Raised);
        tabWidgetMain->addTab(tableDebug, QString());
        tableBatchProcess = new QWidget();
        tableBatchProcess->setObjectName(QString::fromUtf8("tableBatchProcess"));
        tabWidgetMain->addTab(tableBatchProcess, QString());
        AlgorithmDebuggingPlatformClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AlgorithmDebuggingPlatformClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        AlgorithmDebuggingPlatformClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AlgorithmDebuggingPlatformClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy1);
        AlgorithmDebuggingPlatformClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AlgorithmDebuggingPlatformClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AlgorithmDebuggingPlatformClass->setStatusBar(statusBar);
        toolBar = new QToolBar(AlgorithmDebuggingPlatformClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        AlgorithmDebuggingPlatformClass->addToolBar(Qt::LeftToolBarArea, toolBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionNeaProject);
        menu->addAction(actionOpenProject);
        menu->addAction(actionSaveProject);
        mainToolBar->addAction(action_NewProject);
        mainToolBar->addAction(action_OpenProject);
        mainToolBar->addAction(action_SaveProject);
        mainToolBar->addAction(action_SaveAs);
        mainToolBar->addAction(action_ReadImagine);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_OrganizeWindows);
        mainToolBar->addAction(action_vsCode);
        toolBar->addAction(action_DrawRect);
        toolBar->addAction(action_DrawCircle);
        toolBar->addAction(action_DrawPolygon);
        toolBar->addAction(action_DrawPoint);
        toolBar->addAction(action_DrawLine);
        toolBar->addAction(action_DrawEllipse);

        retranslateUi(AlgorithmDebuggingPlatformClass);

        tabWidgetMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AlgorithmDebuggingPlatformClass);
    } // setupUi

    void retranslateUi(QMainWindow *AlgorithmDebuggingPlatformClass)
    {
        AlgorithmDebuggingPlatformClass->setWindowTitle(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "AlgorithmDebuggingPlatform", nullptr));
        action_DrawRect->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\237\251\345\275\242\346\241\206", nullptr));
        action_DrawCircle->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\273\230\345\210\266\345\234\206", nullptr));
        action_vsCode->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\346\230\276\347\244\272vsCode", nullptr));
        action_DrawPolygon->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\273\230\345\210\266\350\275\256\345\273\223\347\272\277", nullptr));
        action_DrawPoint->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\273\230\345\210\266\347\202\271", nullptr));
        action_DrawLine->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\273\230\345\210\266\347\233\264\347\272\277", nullptr));
        action_DrawEllipse->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\273\230\345\210\266\346\244\255\345\234\206", nullptr));
        action_OrganizeWindows->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\350\277\230\345\216\237\347\273\204\344\273\266", nullptr));
        action_NewProject->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\346\226\260\345\273\272\345\267\245\347\250\213", nullptr));
        action_OpenProject->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\346\211\223\345\274\200\345\267\245\347\250\213", nullptr));
        action_SaveProject->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\344\277\235\345\255\230\345\267\245\347\250\213", nullptr));
        action_SaveAs->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\345\217\246\345\255\230\344\270\272", nullptr));
        action_ReadImagine->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\350\257\273\345\217\226\346\225\260\346\215\256", nullptr));
        actionNeaProject->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "NewProject", nullptr));
        actionOpenProject->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "OpenProject", nullptr));
        actionSaveProject->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "SaveProject", nullptr));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tableDebug), QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\345\273\272\346\250\241", nullptr));
#if QT_CONFIG(tooltip)
        tableBatchProcess->setToolTip(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "<html><head/><body><p>\346\265\213\350\257\225</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tableBatchProcess), QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\346\211\271\345\244\204\347\220\206", nullptr));
        menu->setTitle(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "Start", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmDebuggingPlatformClass: public Ui_AlgorithmDebuggingPlatformClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMDEBUGGINGPLATFORM_H
