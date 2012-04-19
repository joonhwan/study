#include "PropertyManager.h"
#include "PlainColorProperty.h"
#include "qtpropertybrowser/QtProperty"
#include "qtpropertybrowser/QtVariantEditorFactory"
#include "qtpropertybrowser/QtGroupBoxPropertyBrowser"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

PropertyManager::PropertyManager(const QString& title,
								 PropertySystem* propertySystem,
								 QObject* parent)
	: QObject(parent)
	, m_title(title)
	, m_system(propertySystem)
	, m_systemAttached(propertySystem ? true : false)
{
	if (!m_system) {
		m_system = createDefaultSystem();
	}
	Q_ASSERT(m_system);
}

//virtual
PropertyManager::~PropertyManager()
{
	// TODO notify of destruction to any pre-created editor widget

	// remove properies
	m_system->unmapProperty(this);

	if (!m_systemAttached) {
		delete m_system;
		m_system = 0;
	}
}

QtProperty* PropertyManager::addProperty(RangedProperty<int>& prop)
{
	QtProperty* qtProperty = m_system->intManager->addProperty(prop.name());
	if (qtProperty) {
		m_system->intManager->setMinimum(qtProperty, prop.valueMaxLimit());
		m_system->intManager->setMaximum(qtProperty, prop.valueMaxLimit());
		m_system->intManager->setValue(qtProperty, prop.value());
		// prop->setToolTip(prop.tooltip())
		// prop->setPropertyName(prop.name())

		m_system->mapProperty(this, prop.id(), qtProperty);
	}
	return qtProperty;
}

QtProperty* PropertyManager::addProperty(RangedProperty<double>& prop)
{
	QtProperty* qtProperty = m_system->doubleManager->addProperty(prop.name());
	if (qtProperty) {
		m_system->doubleManager->setMinimum(qtProperty, prop.valueMaxLimit());
		m_system->doubleManager->setMaximum(qtProperty, prop.valueMaxLimit());
		m_system->doubleManager->setValue(qtProperty, prop.value());

		m_system->mapProperty(this, prop.id(), qtProperty);
	}
	return qtProperty;
}

QtProperty* PropertyManager::addProperty(SimpleProperty<QColor>& prop)
{
	QtProperty* qtProperty = m_system->colorManager->addProperty(prop.name());
	if (qtProperty) {
		m_system->colorManager->setValue(qtProperty, prop.value());

		m_system->mapProperty(this, prop.id(), qtProperty);
	}
	return qtProperty;
}

QWidget* PropertyManager::createEditor(QWidget* parent)
{
	QtGroupBoxPropertyBrowser* editor = new QtGroupBoxPropertyBrowser(0);
	m_system->prepareEditor(editor);

	QList<QtProperty*> myProperties = m_system->propertiesOf(this);
	QListIterator<QtProperty*> it(myProperties);
	while (it.hasNext()) {
		QtProperty* prop = it.next();
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

//virtual
PropertySystem* PropertyManager::createDefaultSystem() const
{
	return new PropertySystem;
}

// void PropertyManager::valueChanged(QtProperty *prop, const QVariant &value)
// {
// 	if (m_idMap.contains(prop)) {
// 		onValueChanged((QtProperty*)prop, m_idMap[prop], value);
// 	}
// }

// void PropertyManager::forgetEditor(QObject* maybeEditor)
// {
// 	if (QtAbstractPropertyBrowser* editor =
// 		qobject_cast<QtAbstractPropertyBrowser*>(maybeEditor))
// 	{
// 		if (m_createdEditors.contains(editor)) {
// 			m_createdEditors.remove(editor);
// 		}
// 	}
// }
