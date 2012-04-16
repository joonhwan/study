#include "PropertyManager.h"
#include "qtpropertybrowser/QtProperty"
#include "qtpropertybrowser/QtVariantEditorFactory"
#include "qtpropertybrowser/QtGroupBoxPropertyBrowser"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

PropertyManager::PropertyManager(const QString& title,
								 QObject* parent)
	: QObject(parent)
	, m_title(title)
{
	m_propertyManager = new QtVariantPropertyManager(this);
	m_propertyEditorFactory = new QtVariantEditorFactory(this);
	connect(m_propertyManager, SIGNAL(valueChanged(QtProperty*,const QVariant&)),
			SLOT(valueChanged(QtProperty*,const QVariant&)));
}

//virtual
PropertyManager::~PropertyManager()
{
}

QtVariantProperty* PropertyManager::addProperty(Property<int>& property)
{
	QtVariantProperty* qtProperty = m_propertyManager->addProperty(QVariant::Int, property.name());
	if (qtProperty) {
		qtProperty->setAttribute(QLatin1String("minimum"), property.min());
		qtProperty->setAttribute(QLatin1String("maximum"), property.max());
		qtProperty->setValue(property.value());
		m_idMap[qtProperty] = property.key();
	}
	return qtProperty;
}

QtVariantProperty* PropertyManager::addProperty(Property<double>& property)
{
	QtVariantProperty* qtProperty = m_propertyManager->addProperty(QVariant::Double, property.name());
	if (qtProperty) {
		qtProperty->setAttribute(QLatin1String("minimum"), property.min());
		qtProperty->setAttribute(QLatin1String("maximum"), property.max());
		qtProperty->setValue(property.value());
		m_idMap[qtProperty] = property.key();
	}
	return qtProperty;
}

QtVariantProperty* PropertyManager::addProperty(Property<ColorPixel>& property)
{
	QtVariantProperty* qtProperty = m_propertyManager->addProperty(QVariant::Color, property.name());
	if (qtProperty) {
		qtProperty->setValue(property.value().toQColor());
		m_idMap[qtProperty] = property.key();
	}
	return qtProperty;
}

QtVariantProperty* PropertyManager::addProperty(Property<QColor>& property)
{
	QtVariantProperty* qtProperty = m_propertyManager->addProperty(QVariant::Color, property.name());
	if (qtProperty) {
		qtProperty->setValue(property.value());
		m_idMap[qtProperty] = property.key();
	}
	return qtProperty;
}

QWidget* PropertyManager::createEditor(QWidget* parent)
{
	QSet<QtProperty*> properties = m_propertyManager->properties();

	QtGroupBoxPropertyBrowser* editor = new QtGroupBoxPropertyBrowser(0);
	editor->setFactoryForManager(m_propertyManager, m_propertyEditorFactory);

	for (QPropertyIdMap::iterator it = m_idMap.begin(); it != m_idMap.end(); ++it) {
		QtVariantProperty* property = (QtVariantProperty*)it.key();
		editor->addProperty(property);
	}

	QFrame* widget = new QFrame;
	widget->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(new QLabel(m_title));
	layout->addWidget(editor);
	widget->setLayout(layout);

	return widget;
}

void PropertyManager::valueChanged(QtProperty *property, const QVariant &value)
{
	if (m_idMap.contains(property)) {
		onValueChanged((QtVariantProperty*)property, m_idMap[property], value);
	}
}
