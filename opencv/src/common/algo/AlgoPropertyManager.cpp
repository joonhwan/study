#include "AlgoPropertyManager.h"
#include "AlgoPropertySystem.h"
#include "property/PlainColorProperty.h"
#include "property/SliderSpinValueProperty.h"

AlgoPropertyManager::AlgoPropertyManager(const QString& title,
										 AlgoPropertySystem* system,
										 QObject* parent)
	: PropertyManager(title, system, parent)
{
}

//virtual
AlgoPropertyManager::~AlgoPropertyManager()
{
}

QtProperty*
AlgoPropertyManager::addProperty(RangedProperty<int>& prop)
{
	QtProperty* qtProperty = m_system->sliderSpinManager->addProperty(prop.name());
	if (qtProperty) {
		m_system->sliderSpinManager->setMinimum(qtProperty, prop.valueMinLimit());
		m_system->sliderSpinManager->setMaximum(qtProperty, prop.valueMaxLimit());
		m_system->sliderSpinManager->setValue(qtProperty, prop.value());
		// prop->setToolTip(prop.tooltip())
		// prop->setPropertyName(prop.name())

		m_system->mapProperty(this, prop.id(), qtProperty);
	}
	return qtProperty;
}

QtProperty*
AlgoPropertyManager::addProperty(ColorPixelProperty& prop)
{
	AlgoPropertySystem* system = (AlgoPropertySystem*)m_system;
	QtProperty* qtProperty = system->plainColorManager->addProperty(prop.name());
	if (qtProperty) {
		m_system->colorManager->setValue(qtProperty, prop.value().toQColor());

		m_system->mapProperty(this, prop.id(), qtProperty);
	}
	return qtProperty;
}

//virtual
PropertySystem* AlgoPropertyManager::createDefaultSystem() const
{
	return new AlgoPropertySystem;
}

