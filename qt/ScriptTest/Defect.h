#pragma once

#include <QObject>
#include <QRectF>

class DefectObject : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QRectF boxUmInWise READ boxUmInWise)
	Q_PROPERTY(int maxGrayLevel READ maxGrayLevel)
	Q_PROPERTY(int averageGrayLevel READ averageGrayLevel);
public:
    DefectObject(QObject* parent=0);
    virtual ~DefectObject();
	// void setDefect(const CDefectPtr& defect) {
	// 	m_defect = defect;
	// }
	QRectF boxUmInWise() const;
	int maxGrayLevel() const;
	int averageGrayLevel() const;
	
signals:
public slots:
	void logDefect(const QString& message);
protected:
	// CDefectPtr m_defect;
};
