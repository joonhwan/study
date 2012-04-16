#include "AlgoPropertyManager.h"

AlgoPropertyManager::AlgoPropertyManager(const QString& title,
										 QObject* parent)
	: PropertyManager(title, parent)
{
}

//virtual
AlgoPropertyManager::~AlgoPropertyManager()
{
}

QtVariantProperty*
AlgoPropertyManager::addProperty(ColorPixelProperty& prop)
{
	SimpleProperty<QColor> _prop(prop.name(), prop.value().toQColor());
	return addProperty(_prop);
}

