#include "PropertySystem.h"
#include "PlainColorProperty.h"
#include "PropertyManager.h"
#include "SliderSpinValueProperty.h"
#include "qtpropertybrowser/QtProperty"
#include "qtpropertybrowser/QtIntPropertyManager"
#include "qtpropertybrowser/QtDoublePropertyManager"
#include "qtpropertybrowser/QtStringPropertyManager"
#include "qtpropertybrowser/QtDoubleSpinBoxFactory"
#include "qtpropertybrowser/QtSpinBoxFactory"
#include "qtpropertybrowser/QtGroupBoxPropertyBrowser"
#include <QColor>
#include <QFont>
#include <QPoint>
#include <QSize>
#include <QString>

PropertySystem::PropertySystem(QObject* parent)
	: QObject(parent)
	, intManager(0)
	, doubleManager(0)
	, stringManager(0)
	, colorManager(0)
	, sliderSpinManager(0)
{
	intManager = new QtIntPropertyManager(this);
	intManager = new SliderSpinValuePropertyManager(this);
	doubleManager = new QtDoublePropertyManager(this);
    stringManager = new QtStringPropertyManager(this);
    colorManager = new PlainColorPropertyManager(this);
    // fontManager = new QtFontPropertyManager(this);
    // pointManager = new QtPointPropertyManager(this);
    // sizeManager = new QtSizePropertyManager(this);
	sliderSpinManager = new SliderSpinValuePropertyManager(this);

	m_doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
	m_spinBoxFactory = new QtSpinBoxFactory(this);
    // m_checkBoxFactory = new QtCheckBoxFactory(this);
    // m_comboBoxFactory = new QtEnumEditorFactory(this);
	m_lineEditFactory = new QtLineEditFactory(this);
	m_sliderSpinFactory = new SliderSpinValueEditorFactory(this);

	connect(intManager, SIGNAL(valueChanged(QtProperty*, int)),
			SLOT(valueChanged(QtProperty*, int)));
	connect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)),
			SLOT(valueChanged(QtProperty*, double)));
    connect(stringManager, SIGNAL(valueChanged(QtProperty *, const QString &)),
			SLOT(valueChanged(QtProperty *, const QString &)));
    connect(colorManager, SIGNAL(valueChanged(QtProperty *, const QColor &)),
			SLOT(valueChanged(QtProperty *, const QColor &)));
    // connect(fontManager, SIGNAL(valueChanged(QtProperty *, const QFont &)),
	// 		SLOT(valueChanged(QtProperty *, const QFont &)));
    // connect(pointManager, SIGNAL(valueChanged(QtProperty *, const QPoint &)),
	// 		SLOT(valueChanged(QtProperty *, const QPoint &)));
    // connect(sizeManager, SIGNAL(valueChanged(QtProperty *, const QSize &)),
	// 		SLOT(valueChanged(QtProperty *, const QSize &)));
	connect(sliderSpinManager, SIGNAL(valueChanged(QtProperty*,int)),
			SLOT(valueChanged(QtProperty*, int)));
}

//virtual
PropertySystem::~PropertySystem()
{
}

//virtual
void PropertySystem::prepareEditor(QtAbstractPropertyBrowser* editor)
{
	editor->setFactoryForManager(intManager, m_spinBoxFactory);
    editor->setFactoryForManager(doubleManager, m_doubleSpinBoxFactory);
    editor->setFactoryForManager(stringManager, m_lineEditFactory);
	editor->setFactoryForManager(colorManager->subIntPropertyManager(), m_spinBoxFactory);
    // editor->setFactoryForManager(fontManager->subIntPropertyManager(), m_spinBoxFactory);
    // editor->setFactoryForManager(fontManager->subBoolPropertyManager(), m_checkBoxFactory);
    // editor->setFactoryForManager(fontManager->subEnumPropertyManager(), m_comboBoxFactory);
    // editor->setFactoryForManager(pointManager->subIntPropertyManager(), m_spinBoxFactory);
    // editor->setFactoryForManager(sizeManager->subIntPropertyManager(), m_spinBoxFactory);
	editor->setFactoryForManager(sliderSpinManager, m_sliderSpinFactory);
}

QList<QtProperty*> PropertySystem::propertiesOf(PropertyManager* manager)
{
	QList<QtProperty*> properties;
	PropertyToManager::iterator it = m_propToManager.begin();
	for (; it != m_propToManager.end(); ++it) {
		if (it.value().manager == manager) {
			properties.push_back(it.key());
		}
	}
	return properties;
}

//virtual
void PropertySystem::mapProperty(PropertyManager* manager,
								 void* id,
								 QtProperty* prop)
{
	MapDataItem item;
	item.id = id;
	item.manager = manager;
	m_propToManager[prop] = item;
}

//virtual
void PropertySystem::unmapProperty(PropertyManager* manager)
{
	PropertyToManager::iterator it = m_propToManager.begin();
	while (it != m_propToManager.end()) {
		if (it.value().manager == manager) {
			it = m_propToManager.erase(it);
		} else {
			++it;
		}
	}
}

void PropertySystem::valueChanged(QtProperty *property, int value)
{
	PropertyToManager::iterator it = m_propToManager.find(property);
	if (it != m_propToManager.end()) {
		MapDataItem& item = it.value();
		item.manager->onValueChanged(property, item.id, QVariant(value));
	}
}

void PropertySystem::valueChanged(QtProperty *property, double value)
{
	PropertyToManager::iterator it = m_propToManager.find(property);
	if (it != m_propToManager.end()) {
		MapDataItem& item = it.value();
		item.manager->onValueChanged(property, item.id, QVariant(value));
	}
}

void PropertySystem::valueChanged(QtProperty *property, const QString &value)
{
	PropertyToManager::iterator it = m_propToManager.find(property);
	if (it != m_propToManager.end()) {
		MapDataItem& item = it.value();
		item.manager->onValueChanged(property, item.id, QVariant(value));
	}
}

void PropertySystem::valueChanged(QtProperty *property, const QColor &value)
{
	PropertyToManager::iterator it = m_propToManager.find(property);
	if (it != m_propToManager.end()) {
		MapDataItem& item = it.value();
		item.manager->onValueChanged(property, item.id, QVariant(value));
	}
}

void PropertySystem::valueChanged(QtProperty *property, const QFont &value)
{
	PropertyToManager::iterator it = m_propToManager.find(property);
	if (it != m_propToManager.end()) {
		MapDataItem& item = it.value();
		item.manager->onValueChanged(property, item.id, QVariant(value));
	}
}

void PropertySystem::valueChanged(QtProperty *property, const QPoint &value)
{
	PropertyToManager::iterator it = m_propToManager.find(property);
	if (it != m_propToManager.end()) {
		MapDataItem& item = it.value();
		item.manager->onValueChanged(property, item.id, QVariant(value));
	}
}

void PropertySystem::valueChanged(QtProperty *property, const QSize &value)
{
	PropertyToManager::iterator it = m_propToManager.find(property);
	if (it != m_propToManager.end()) {
		MapDataItem& item = it.value();
		item.manager->onValueChanged(property, item.id, QVariant(value));
	}
}

