#pragma once

#include <QHash>
#include <QObject>

class PropertyManager;
class QColor;
class QFont;
class QPoint;
class QSize;
class QString;
class QtProperty;
class QtAbstractPropertyBrowser;

class PropertySystem : public QObject
{
    Q_OBJECT
	struct MapDataItem
	{
		void* id;
		PropertyManager* manager;
	};
public:
	PropertySystem(QObject* parent=0);
    virtual ~PropertySystem();
	virtual void prepareEditor(QtAbstractPropertyBrowser* editor);
	QList<QtProperty*> propertiesOf(PropertyManager* manager);
	void mapProperty(PropertyManager* manager,
					 void* id,
					 QtProperty* prop);
	void unmapProperty(PropertyManager* manager);
	class QtIntPropertyManager* intManager;
	class QtDoublePropertyManager *doubleManager;
    class QtStringPropertyManager *stringManager;
    class QtColorPropertyManager *colorManager;
    // class QtFontPropertyManager *fontManager;
    // class QtPointPropertyManager *pointManager;
    // class QtSizePropertyManager *sizeManager;
	class SliderSpinValuePropertyManager* sliderSpinManager;
private slots:
	void valueChanged(QtProperty *property, int value);
	void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, const QString &value);
    void valueChanged(QtProperty *property, const QColor &value);
    void valueChanged(QtProperty *property, const QFont &value);
    void valueChanged(QtProperty *property, const QPoint &value);
    void valueChanged(QtProperty *property, const QSize &value);
protected:
	class QtDoubleSpinBoxFactory *m_doubleSpinBoxFactory;
	class QtSpinBoxFactory *m_spinBoxFactory;
	class SliderSpinValueEditorFactory* m_sliderSpinFactory;
    // class QtCheckBoxFactory *m_checkBoxFactory;
    // class QtEnumEditorFactory *m_comboBoxFactory;
	class QtLineEditFactory *m_lineEditFactory;

	typedef QHash<QtProperty*, MapDataItem> PropertyToManager;
	PropertyToManager m_propToManager;
};
