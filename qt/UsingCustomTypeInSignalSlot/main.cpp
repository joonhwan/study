#include "TestClass.h"
#include "MainWindow.h"
#include <QApplication>
#include <QVariant>
#include <QDebug>
#include <QTextCodec>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("metatype");

	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	QVariant v1 = MyEnum::TRAIN;
	qDebug() << "v1 can convert enum ? : " << (v1.canConvert<MyEnum::Type>());
	qDebug() << "v1 can convert int ? : " << (v1.canConvert<int>());
	qDebug() << v1.toInt() << v1.value<MyEnum::Type>();

	QVariant v2 = QVariant::fromValue(MyEnum::TAXY);
	qDebug() << "v2 can convert to enum ? : " << (v2.canConvert<MyEnum::Type>());
	qDebug() << "v2 can convert int ? : " << (v2.canConvert<int>());
	qDebug() << v2.toInt() << v2.value<MyEnum::Type>();

	MainWindow w;
	w.show();
	w.activateWindow();
	w.raise();
	return app.exec();
}
