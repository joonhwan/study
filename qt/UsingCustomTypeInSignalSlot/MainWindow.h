#pragma once

#include "TestClass.h"
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=0);
    virtual ~MainWindow();
signals:
	void testSignal(const MyEnum::Type& value);
	void testSignal2(const TestDataClass& tdc);
	void testSignal2_NonConst(TestDataClass& tdc);
	void testSignal3(TestDataClass* tdc);
public slots:
	void onClicked();
	void onClicked2();
	void testSlot(const MyEnum::Type& value);
	void testSlot2(const TestDataClass& tdc);
	void testSlot2_NonConst(TestDataClass& tdc);
	void testSlot2_Queued(const TestDataClass& tdc);
	void testSlot_Pointer_Queued(TestDataClass* tdc);
protected:
	MyEnum::Type m_enum;
	TestDataClass m_tdc;
};
