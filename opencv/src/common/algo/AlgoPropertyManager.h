#pragma once

#include "algo/AlgoTypes.h"
#include "property/PropertyManager.h"

typedef SimpleProperty<ColorPixel> ColorPixelProperty;
class AlgoPropertySystem;

class AlgoPropertyManager : public PropertyManager
{
    Q_OBJECT
public:
	using PropertyManager::addProperty;
    AlgoPropertyManager(const QString& title,
						AlgoPropertySystem* system,
						QObject* parent=0);
    virtual ~AlgoPropertyManager();
	QtProperty* addProperty(RangedProperty<int>& property);
	QtProperty* addProperty(ColorPixelProperty& property);
	virtual PropertySystem* createDefaultSystem() const;
};
