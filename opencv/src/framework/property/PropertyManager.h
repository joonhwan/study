#pragma once

#include "property/PropertySystem.h"
#include "property/RangedProperty.h"
#include "property/SimpleProperty.h"
#include "qtpropertybrowser/QtVariantPropertyManager"
#include <QObject>

class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QVariant;

class PropertyManager : public QObject
{
    Q_OBJECT
public:
    PropertyManager(const QString& title,
					PropertySystem* propertySystem=0,
					QObject* parent=0);
    virtual ~PropertyManager();
	virtual void onValueChanged(QtProperty* property,
								void* id,
								const QVariant& value) = 0;
	QtProperty* addProperty(RangedProperty<int>& property);
	QtProperty* addProperty(RangedProperty<double>& property);
	QtProperty* addProperty(SimpleProperty<QColor>& property);
	QWidget* createEditor(QWidget* parent);
protected:
	QString m_title;
	PropertySystem* m_system;
	bool m_systemAttached;

	virtual PropertySystem* createDefaultSystem() const;
};
