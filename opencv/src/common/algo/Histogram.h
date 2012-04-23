#pragma once

#include "algo/AlgoTypes.h"
#include "algo/AlgoPropertyManager.h"

class ColorHistogram : public AlgoPropertyManager
{
    Q_OBJECT
public:
    ColorHistogram(AlgoPropertySystem* system,
			  QObject* parent=0);
    virtual ~Histogram();
	virtual void onValueChanged(QtProperty* property,
								void* id,
								const QVariant& value);
signals:
public slots:
protected:
	RangedProperty<int> m_channel;
	ColorBuffer m_buffer
};
