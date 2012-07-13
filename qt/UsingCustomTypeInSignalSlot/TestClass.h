#pragma once

#include <QMetaType>
#include <QStringList>

class MyEnum
{
public:
	enum Type {
		BUS = 0,
		TAXY,
		TRAIN
	};
};
Q_DECLARE_METATYPE(MyEnum::Type);

struct TestData
{
	QString name;
	QStringList children;
	int age;
	int level;
};

class TestDataClass
{
public:
	QString name;
	QStringList children;
	int age;
	int level;
};
