// #include "MainWindow.h"
#include <QtGui>
#include <QtScript>
#include "Defect.h"
#include <QDebug>

void printValueStatus(const QString& name, const QScriptValue& value)
{
	qDebug() << "Object:" << name << " --> " << value.toQObject() << endl
			 << "  isValid?:" << value.isValid() << endl
			 << "  isError?:" << value.isError() << endl
			 << "  isNull?:" << value.isNull() << endl
			 << "  isFunction?:" << value.isFunction() << endl
			 << "  isObject?:" << value.isObject() << endl
			 << "  isBool?:" << value.isBool() << endl
			 << "  isNumber?:" << value.isNumber() << endl
		;
}


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("ScriptTest");

	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	// Step 1 : QScriptEngine 객체 구성
	QScriptEngine engine;

	// Step 2 : 사용자 C++객체 및 Javascript객체 생성
	DefectObject* defect = new DefectObject(&engine);
	QScriptValue defectObj = engine.newQObject (defect);

	// Step 3 : 전역공간에 Step2 의 객체 저장
	printValueStatus("defectObj", defectObj);

	// Step 4 : 처리할 Javascript 함수 등록
	//         아래 예는 결함 객체 1개를 인자로 받음.
	QScriptValue func = engine.evaluate("(function (defect) {"
										"   if(defect.averageGrayLevel < 12) {"
										"       defect.logDefect(\"hey...\");"
										"       return false;"
										"   }"
										"   return true;"
										"})");
	printValueStatus("func", func);

	QScriptValue badPredicator = engine.globalObject().property("isUknownDefect");
	printValueStatus("isUnknownDefect", badPredicator);

	QScriptValue badResult = badPredicator.call(QScriptValue(), defectObj);
	printValueStatus("badResult", badResult);

	// QScriptValue predicator = engine.globalObject().property("isDummyDefect");
	printValueStatus("predicator", func);

	// Step 4 : 등록된 Javascript 함수 호출 및 반환값 저장
	QScriptValue result = func.call(QScriptValue(), QScriptValueList() << defectObj);

	printValueStatus("result", result);

	// Step 5 : 반환값의 내용 확인.
	qDebug() << "result is " << result.toBool();

	// MainWindow w;
	// w.show();
	// w.activateWindow();
	// w.raise();
	// return app.exec();
}
