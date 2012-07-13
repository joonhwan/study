#include <QApplication>
#include <QAxObject>
#include <QClipboard>
#include <QImage>
#include <QSharedPointer>
#define USE_DUMPCPP_EXCEL
#ifdef USE_DUMPCPP_EXCEL
#include "excel.h"
#endif
#include <QDebug>
#include <ole2.h>
#include <QUuid>
#include "WDispatchDriver.h"

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

typedef QSharedPointer<QAxObject> QAxObjectPtr;

void test1()
{
	QAxObject excel( "Excel.Application", 0);
	excel.setProperty("Visible", true);

	QAxObjectPtr workbooks(excel.querySubObject("Workbooks"));
	QAxObjectPtr workbook(workbooks->querySubObject("Add()"));
	QAxObjectPtr sheets(workbook->querySubObject("Worksheets"));
	sheets->dynamicCall("Add()");
	QAxObjectPtr sheet(sheets->querySubObject( "Item( int )", 1 ));
	// sheet->setProperty("Name","Nova Planilha");

	QAxObjectPtr range(sheet->querySubObject("Cells(int,int)",1,1));
	range->setProperty("Value", QVariant(1234));

	QImage image("c:/Users/jhlee/Dropbox/orgwiki/img/class01.png");
	QClipboard* clip = QApplication::clipboard();
	clip->setImage(image);
	QAxObjectPtr shapes(sheet->querySubObject("Shapes"));
	sheet->dynamicCall("Paste()");
	int shapeCount = shapes->property("Count").toInt();
	QAxObjectPtr shape(shapes->querySubObject(QString::fromLatin1("Item(%1)").arg(shapeCount).toAscii()));

	// shapes->dynamicCall("AddPicture( QString&, bool, bool, double, double, double, double","c:\\Users\\jhlee\\Dropbox\\orgwiki\\img\\class01.png",true,true,100,100,70,70);

	excel.setProperty("DisplayAlerts", false);
	workbook->dynamicCall("SaveAs(QString&)", "c:\\temp\\testexcel.xlsx");
	// //workbook->dynamicCall("Close()");
	// //excel.dynamicCall("Quit()");
	// workbook->dynamicCall("Close (Boolean)", true);
	excel.dynamicCall("Quit()");
}

void test2()
{
	QAxObject* excel = new QAxObject( "Excel.Application", 0);
	excel->setProperty("Visible", true);
	excel->dynamicCall("Quit()");
	delete excel;
}

void test3()
{
#ifdef USE_DUMPCPP_EXCEL
	Excel::Application excel;
	if (excel.isNull()) {
		return;
	}
	excel.SetVisible(true);

	Excel::Workbooks* workbooks = excel.Workbooks();
	Excel::Workbook* workbook = workbooks->Add();
	Excel::Sheets* sheets = workbook->Worksheets();
	Excel::_Worksheet sheet(sheets->Item(1));
	sheet.SetName("MyName");
	Excel::Range* range = sheet.Cells();
	range->SetItem(1,1,"Hello Seoyeon..");
	range->SetItem(2,1,"Hello Myungbakiee..");

	workbook->SaveAs("c:\\temp\\test.xls");
	workbook->Close();
	excel.Quit();
#endif
}

void test4()
{
	QAxObjectPtr xcom(new QAxObject("{717b131f-e3dd-4053-87a6-c4e2b2e983c2}"));
	if (xcom->isNull()) {
		return;
	}
	QAxObjectPtr com(new QAxObject("{4701EA53-53D6-4F06-86A2-B211A4F84000}"));
	if (com->isNull()) {
		return;
	}

	{
		int value = 0;
		QList<QVariant> vars;
		vars << 10;
		vars << 20;
		vars << 0;
		com->dynamicCall("Add(int,int,int&)", vars);
		value = vars[2].toInt();
		qDebug() << "answer = " << value;
	}

	{
		IDispatch* disp = 0;
		QUuid id("{00020400-0000-0000-C000-000000000046}");
		com->queryInterface(id, (void**)&disp);
		if (disp) {
			WDispatchDriver driver;
			driver.Attach(disp);
			disp->Release();

			short data[10];
			int len = 0;
			VARIANT* v = driver.InvokeMethod("GetSampleArrayData", 10, data, &len);
			Q_ASSERT(len==8);
		}
	}
}

int main(int argc, char** argv)
{
	QApplication excel(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("QActiveXTester"); 

	// test1();
	// test2();
	// test3();
	test4();

	// return excel.exec();
	return 0;
}
