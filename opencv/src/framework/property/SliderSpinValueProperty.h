#pragma once

#include "property/EditorImpl.h"
#include "qtpropertybrowser/QtIntPropertyManager"
#include "qtpropertybrowser/qteditorfactory.h"

class QSlider;
class QSpinBox;

class SliderSpinValuePropertyManager : public QtIntPropertyManager
{
    Q_OBJECT
public:
    SliderSpinValuePropertyManager(QObject* parent=0);
    virtual ~SliderSpinValuePropertyManager();
};

class SliderSpinValueEditWidget : public QWidget
{
    Q_OBJECT
public:
    SliderSpinValueEditWidget(QWidget *parent);
	void setRange(int min, int max);
public slots:
    void setValue(int value);
signals:
    void valueChanged(int value);
private:
	int m_value;
	QSlider* m_slider;
	QSpinBox* m_spinBox;
};

class SliderSpinValueEditorFactory : public QtAbstractEditorFactory<SliderSpinValuePropertyManager>
								   , public EditorImpl<SliderSpinValueEditWidget>
{
	Q_OBJECT
public:
	typedef EditorImpl<SliderSpinValueEditWidget> Impl;
	SliderSpinValueEditorFactory(QObject *parent = 0);
    ~SliderSpinValueEditorFactory();
protected:
    virtual void connectPropertyManager(SliderSpinValuePropertyManager *manager);
    virtual void disconnectPropertyManager(SliderSpinValuePropertyManager *manager);
	virtual QWidget *createEditor(SliderSpinValuePropertyManager *manager, QtProperty *property,
								  QWidget *parent);
private slots:
	void slotPropertyChanged(QtProperty *property, int value);
    void slotSetValue(int value);
	void slotEditorDestroyed(QObject* object);
};
