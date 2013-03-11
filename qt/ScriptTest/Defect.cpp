#include "Defect.h"
#include <QDebug>

DefectObject::DefectObject(QObject* parent)
	: QObject(parent)
{
}

//virtual
DefectObject::~DefectObject()
{
}

QRectF DefectObject::boxUmInWise() const
{
	// return m_defet->boxUmInWise();
	return QRectF(10.5, 12.3,
				  5.2, 62.1);
}

int DefectObject::maxGrayLevel() const
{
	return 210;
}

int DefectObject::averageGrayLevel() const
{
	return 10;
}


void DefectObject::logDefect(const QString& message)
{
	qDebug() << "Defect Log : " << message;
}
