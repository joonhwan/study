#pragma once

#include "algo/AlgoTypes.h"
#include "algo/AlgoPropertyManager.h"

class Histogram : public AlgoPropertyManager
{
    Q_OBJECT
public:
    Histogram(AlgoPropertySystem* system,
			  QObject* parent=0);
    virtual ~Histogram();
	virtual void onValueChanged(QtProperty* property,
								void* id,
								const QVariant& value);
signals:
public slots:
protected:
	RangedProperty<int> m_minLevel;
	RangedProperty<int> m_maxLevel;
};
