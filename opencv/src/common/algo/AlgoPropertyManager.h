#pragma once

#include "algo/AlgoTypes.h"
#include "property/PropertyManager.h"

typedef SimpleProperty<ColorPixel> ColorPixelProperty;

class AlgoPropertyManager : public PropertyManager
{
    Q_OBJECT
public:
	using PropertyManager::addProperty;

    AlgoPropertyManager(const QString& title,
						QObject* parent=0);
    virtual ~AlgoPropertyManager();
	QtVariantProperty* addProperty(ColorPixelProperty& property);
signals:
public slots:
protected:
};
