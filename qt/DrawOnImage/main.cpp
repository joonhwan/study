#include "DrawOnImageWindow.h"
#include <QApplication>
#include <QTimer>
#include <vld.h>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("colorize");

	DrawOnImageWindow w;
	w.show();
	w.activateWindow();
	w.raise();
	// qWidget w;
	// w.show();
	// QTimer::singleShot(1000, &app, SLOT(quit()));

	return app.exec();
}
