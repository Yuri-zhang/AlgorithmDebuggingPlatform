#include "AlgorithmDebuggingPlatform.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QWidget>
#include <QWindow>
#include <Windows.h>
#include <QScreen>

int main(int argc, char *argv[])
{
   // QDesktopWidget* desktopWidget = QApplication::desktop();
    //QScreen* screen = QGuiApplication::primaryScreen();
    //QRect screenRect = screen->geometry();
	int Width = GetSystemMetrics(SM_CXSCREEN);
	int Height = GetSystemMetrics(SM_CYSCREEN);

    QApplication a(argc, argv);
    AlgorithmDebuggingPlatform w;
    w.resize(Width,Height-70);
    w.show();

    return a.exec();
}
