#pragma once

#include "Property.h"
#include "qtpropertybrowser/QtVariantPropertyManager"
#include <QObject>

class QtVariantPropertyManager;
class QtVariantEditorFactory;

class PropertyManager : public QObject
{
    Q_OBJECT
public:
    PropertyManager(QObject* parent=0);
    virtual ~PropertyManager();

	QtVariantProperty* addProperty(Property<int>& property);
	QtVariantProperty* addProperty(Property<double>& property);
	QtVariantProperty* addProperty(Property<ColorPixel>& property);
	QtVariantProperty* addProperty(Property<QColor>& property);
	QWidget* createEditor(QWidget* parent);
protected:
	virtual void onValueChanged(QtVariantProperty* property, void* id, const QVariant& value) = 0;
private slots:
	void valueChanged(QtProperty *property, const QVariant &value);
private:
	QtVariantPropertyManager* m_propertyManager;
	QtVariantEditorFactory* m_propertyEditorFactory;

	typedef QHash<QtProperty*, void*> QPropertyIdMap;
	QPropertyIdMap m_idMap;
};
