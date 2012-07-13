#include <QApplication>
#include <QDebug>
#include "nsUniversalDetector.h"

#if defined(_DEBUG) && defined(WIN32)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
class MemLeakDetector
{
public:
	MemLeakDetector()
	{
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	}
	~MemLeakDetector()
	{
	}
} detector;
#endif

class EncodeDetector : public nsUniversalDetector
{
public:
	virtual void Report(const char* aCharset)
	{
		qDebug() << "detected " << aCharset;
	}
};


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("EncodeDetector");

	// QString testString("AbceDe");// = QString::fromLocal8Bit("¾È³çÇÏ¼¼¿ä");
	QByteArray testString("This Is Good");
	EncodeDetector detector;
	// detector.HandleData((const char*)testString.unicode(), testString.length() * 2);
	detector.HandleData(testString.constData(), testString.length());

	return 0;//app.exec();
}
