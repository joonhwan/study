#include "MainWindow.h"
#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	m_tdc.name = "Joonhwan";
	m_tdc.children << "Seyeon"
				<< "Eunseo";
	m_tdc.age = 42;
	m_tdc.level = 5;

	QPushButton* button1 = new QPushButton("Test1");
	connect(button1, SIGNAL(clicked()), SLOT(onClicked()));
	QPushButton* button2 = new QPushButton("Test2");
	connect(button2, SIGNAL(clicked()), SLOT(onClicked2()));

	// - 비 포인터형을 받을 때는 반드시 const T& 형으로 signal/slot이
	//   되어야 한다.  signal/slot에서 Queuedconnection이 된 경우,
	//   호출측에서 받는 non-const 참조형은 아무런 의미가
	//   없다. 호출측이 전달한 객체에 대한 참조가 아니라, 새로이
	//   만들어진 객체에 대한 참조를 하기 때문이다.

	// enum을 전달할 때도 사용자 타입설정과 동일한 느낌으로 하면 된다.
	qRegisterMetaType<MyEnum::Type>("MyEnum::Type");
	connect(this, SIGNAL(testSignal(const MyEnum::Type&)),
			this, SLOT(testSlot(const MyEnum::Type&)),
			Qt::QueuedConnection);

	// 아래의 내용은 qRegisterMetaType()의 호출과는 상관없이 가능하다.
	// 1. const 참조형.
	connect(this, SIGNAL(testSignal2(const TestDataClass&)),
			this, SLOT(testSlot2(const TestDataClass&)));
	// 2a. non-const 참조형 - Direct
	connect(this, SIGNAL(testSignal2_NonConst(TestDataClass&)),
			this, SLOT(testSlot2_NonConst(TestDataClass&)));
	// 2b. non-const 참조형 - Queueud
	//  ---> 동작하지 않는다. 아래와 같은 경고가 뜬다. 하지만,
	//  qRegisterMetaType<TestDataClass&>("TestDataClass&")는 컴파일이 안된다.
	//  따라서 쓸 수가 없다.
	//  QObject::connect: Cannot queue arguments of type 'TestDataClass&'
	// (Make sure 'TestDataClass&' is registered using qRegisterMetaType().)
	//
	// connect(this, SIGNAL(testSignal2_NonConst(TestDataClass&)),
	// 		this, SLOT(testSlot2_NonConst(TestDataClass&)),
	// 		Qt::QueuedConnection);

	// 3. 포인터형(const 이 아니어도 동작한다).
	connect(this, SIGNAL(testSignal3(TestDataClass*)),
			this, SLOT(testSlot_Pointer_Queued(TestDataClass*)),
			Qt::QueuedConnection);

	// 아래의 내용을 처리하지 않으면, testSlot2_Queued()는 동작하지 않는다.
	qRegisterMetaType<TestDataClass>("TestDataClass");
	connect(this, SIGNAL(testSignal2(const TestDataClass&)),
			this, SLOT(testSlot2_Queued(const TestDataClass&)),
			Qt::QueuedConnection);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(button1);
	layout->addWidget(button2);
}

//virtual
MainWindow::~MainWindow()
{
}

void MainWindow::onClicked()
{
	emit testSignal(m_enum);
}

void MainWindow::onClicked2()
{
	// TestDataClass anotherTd;
	// anotherTd = m_tdc;
	emit testSignal2(m_tdc);
	emit testSignal2_NonConst(m_tdc);
	emit testSignal3(&m_tdc);
}

void printResult(const char* func, const void* source, const void* current)
{
	qDebug() << func << ((source==current) ? "동일한 객체" : "복제된 객체");
}

void MainWindow::testSlot(const MyEnum::Type& value)
{
	printResult(__FUNCTION__, &m_enum, &value);
}

void MainWindow::testSlot2(const TestDataClass& tdc)
{
	printResult(__FUNCTION__, &m_tdc, &tdc);
}

void MainWindow::testSlot2_NonConst(TestDataClass& tdc)
{
	printResult(__FUNCTION__, &m_tdc, &tdc);
}

void MainWindow::testSlot2_Queued(const TestDataClass& tdc)
{
	printResult(__FUNCTION__, &m_tdc, &tdc);
}

void MainWindow::testSlot_Pointer_Queued(TestDataClass* tdc)
{
	printResult(__FUNCTION__, &m_tdc, tdc);
}
