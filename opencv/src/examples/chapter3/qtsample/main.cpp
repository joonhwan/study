#include "imagedir.h"
//#include "image/Vld.h"
#include "image/WStopwatch.h"
#include "image/wimageprocessor.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef WImageBufferT<uchar, 3> ColorBuffer;
typedef WImageBufferT<uchar, 1> MonoBuffer;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	MainWindow window;
	window.show();
	return app.exec();
}
