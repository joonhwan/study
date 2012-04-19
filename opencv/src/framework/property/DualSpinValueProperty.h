#pragma once

#include "property/EditorImpl.h"
#include "qtpropertybrowser/QtIntPropertyManager"
#include "qtpropertybrowser/qteditorfactory.h"

class QSlider;
class QSpinBox;

class QT_QTPROPERTYBROWSER_EXPORT QtDualSpinPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtIntPropertyManager(QObject *parent = 0);
    ~QtIntPropertyManager();

    int value(const QtProperty *property) const;
    int minimum(const QtProperty *property) const;
    int maximum(const QtProperty *property) const;
    int singleStep(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, int val);
    void setMinimum(QtProperty *property, int minVal);
    void setMaximum(QtProperty *property, int maxVal);
    void setRange(QtProperty *property, int minVal, int maxVal);
    void setSingleStep(QtProperty *property, int step);
Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);
    void rangeChanged(QtProperty *property, int minVal, int maxVal);
    void singleStepChanged(QtProperty *property, int step);
protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    QtIntPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QtIntPropertyManager)
    Q_DISABLE_COPY(QtIntPropertyManager)
};

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
