/********************************************************************************
** Form generated from reading UI file 'AlgorithmDebuggingPlatform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMDEBUGGINGPLATFORM_H
#define UI_ALGORITHMDEBUGGINGPLATFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
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
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tableDebug;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayoutShowImg;
    QFrame *frameIDE;
    QWidget *tableBatchProcess;
    QMenuBar *menuBar;
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
        centralWidget = new QWidget(AlgorithmDebuggingPlatformClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1881, 1041));
        QFont font;
        font.setPointSize(25);
        tabWidget->setFont(font);
        tabWidget->setIconSize(QSize(100, 100));
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
        frameIDE->setGeometry(QRect(630, 10, 1200, 940));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameIDE->sizePolicy().hasHeightForWidth());
        frameIDE->setSizePolicy(sizePolicy);
        frameIDE->setLayoutDirection(Qt::LeftToRight);
        frameIDE->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 200);"));
        frameIDE->setFrameShape(QFrame::Panel);
        frameIDE->setFrameShadow(QFrame::Raised);
        tabWidget->addTab(tableDebug, QString());
        tableBatchProcess = new QWidget();
        tableBatchProcess->setObjectName(QString::fromUtf8("tableBatchProcess"));
        tabWidget->addTab(tableBatchProcess, QString());
        AlgorithmDebuggingPlatformClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AlgorithmDebuggingPlatformClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 23));
        AlgorithmDebuggingPlatformClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AlgorithmDebuggingPlatformClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AlgorithmDebuggingPlatformClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AlgorithmDebuggingPlatformClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AlgorithmDebuggingPlatformClass->setStatusBar(statusBar);
        toolBar = new QToolBar(AlgorithmDebuggingPlatformClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        AlgorithmDebuggingPlatformClass->addToolBar(Qt::LeftToolBarArea, toolBar);

        toolBar->addAction(action_DrawRect);
        toolBar->addAction(action_DrawCircle);

        retranslateUi(AlgorithmDebuggingPlatformClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AlgorithmDebuggingPlatformClass);
    } // setupUi

    void retranslateUi(QMainWindow *AlgorithmDebuggingPlatformClass)
    {
        AlgorithmDebuggingPlatformClass->setWindowTitle(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "AlgorithmDebuggingPlatform", nullptr));
        action_DrawRect->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\237\251\345\275\242\346\241\206", nullptr));
        action_DrawCircle->setText(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\347\273\230\345\210\266\345\234\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tableDebug), QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\345\273\272\346\250\241", nullptr));
#if QT_CONFIG(tooltip)
        tableBatchProcess->setToolTip(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "<html><head/><body><p>\346\265\213\350\257\225</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget->setTabText(tabWidget->indexOf(tableBatchProcess), QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "\346\211\271\345\244\204\347\220\206", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("AlgorithmDebuggingPlatformClass", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmDebuggingPlatformClass: public Ui_AlgorithmDebuggingPlatformClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMDEBUGGINGPLATFORM_H
