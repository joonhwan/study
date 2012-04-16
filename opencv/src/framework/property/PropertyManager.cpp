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

QtVariantProperty* PropertyManager::addProperty(RangedProperty<int>& prop)
{
	QtVariantProperty* qtProperty = m_propertyManager->addProperty(QVariant::Int, prop.name());
	if (qtProperty) {
		qtProperty->setAttribute(QLatin1String("minimum"), prop.min());
		qtProperty->setAttribute(QLatin1String("maximum"), prop.max());
		qtProperty->setValue(prop.value());
		m_idMap[qtProperty] = prop.key();
	}
	return qtProperty;
}

QtVariantProperty* PropertyManager::addProperty(RangedProperty<double>& prop)
{
	QtVariantProperty* qtProperty = m_propertyManager->addProperty(QVariant::Double, prop.name());
	if (qtProperty) {
		qtProperty->setAttribute(QLatin1String("minimum"), prop.min());
		qtProperty->setAttribute(QLatin1String("maximum"), prop.max());
		qtProperty->setValue(prop.value());
		m_idMap[qtProperty] = prop.key();
	}
	return qtProperty;
}

QtVariantProperty* PropertyManager::addProperty(SimpleProperty<QColor>& prop)
{
	QtVariantProperty* qtProperty = m_propertyManager->addProperty(QVariant::Color, prop.name());
	if (qtProperty) {
		qtProperty->setValue(prop.value());
		m_idMap[qtProperty] = prop.key();
	}
	return qtProperty;
}

QWidget* PropertyManager::createEditor(QWidget* parent)
{
	QSet<QtProperty*> properties = m_propertyManager->properties();

	QtGroupBoxPropertyBrowser* editor = new QtGroupBoxPropertyBrowser(0);
	editor->setFactoryForManager(m_propertyManager, m_propertyEditorFactory);

	for (QPropertyIdMap::iterator it = m_idMap.begin(); it != m_idMap.end(); ++it) {
		QtVariantProperty* prop = (QtVariantProperty*)it.key();
		editor->addProperty(prop);
	}

	QFrame* widget = new QFrame;
	widget->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(new QLabel(m_title));
	layout->addWidget(editor);
	widget->setLayout(layout);

	return widget;
}

void PropertyManager::valueChanged(QtProperty *prop, const QVariant &value)
{
	if (m_idMap.contains(prop)) {
		onValueChanged((QtVariantProperty*)prop, m_idMap[prop], value);
	}
}
