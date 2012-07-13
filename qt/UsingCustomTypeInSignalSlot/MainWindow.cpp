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

	qRegisterMetaType<MyEnum::Type>("MyEnum::Type");
	connect(this, SIGNAL(testSignal(const MyEnum::Type&)),
			this, SLOT(testSlot(const MyEnum::Type&)),
			Qt::QueuedConnection);

	// qRegisterMetaType<TestDataClass>("TestDataClass");
	connect(this, SIGNAL(testSignal2(const TestDataClass&)),
			this, SLOT(testSlot2_Queued(const TestDataClass&)),
			Qt::QueuedConnection);
	connect(this, SIGNAL(testSignal2(const TestDataClass&)),
			this, SLOT(testSlot2(const TestDataClass&)));
	connect(this, SIGNAL(testSignal3(TestDataClass*)),
			this, SLOT(testSlot3_Queued(TestDataClass*)),
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
	MyEnum::Type v = MyEnum::BUS;
	emit testSignal(v);
}

void MainWindow::onClicked2()
{
	// TestDataClass anotherTd;
	// anotherTd = m_tdc;
	emit testSignal2(m_tdc);
	emit testSignal3(&m_tdc);
}

void MainWindow::testSlot(const MyEnum::Type& value)
{
	qDebug() << "testSlot(" << value << ") is called";
}

void MainWindow::testSlot2(const TestDataClass& tdc)
{
}

void MainWindow::testSlot2_Queued(const TestDataClass& tdc)
{
}

void MainWindow::testSlot3_Queued(TestDataClass* tdc)
{
}
