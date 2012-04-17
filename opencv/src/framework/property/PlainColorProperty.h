#pragma once

#include "qtpropertybrowser/qtpropertymanager.h"
#include "property/EditorImpl.h"
#include <QColor>

class PlainColorPropertyManagerPrivate;
class QLabel;
class QToolButton;

class PlainColorPropertyManager : public QtColorPropertyManager
{
    Q_OBJECT
public:
    PlainColorPropertyManager(QObject *parent = 0);
    virtual ~PlainColorPropertyManager();
protected:
	virtual void initializeProperty(QtProperty *property);
};

class PlainColorEditWidget : public QWidget
{
    Q_OBJECT
public:
    PlainColorEditWidget(QWidget *parent);
    bool eventFilter(QObject *obj, QEvent *ev);
public slots:
    void setValue(const QColor &value);
signals:
    void valueChanged(const QColor &value);
protected:
    void paintEvent(QPaintEvent *);
	QString colorToString(const QColor& color);
private slots:
    void buttonClicked();
private:
    QColor m_color;
    QLabel *m_pixmapLabel;
    QLabel *m_label;
    QToolButton *m_button;
};

class PlainColorEditorFactory : public QtAbstractEditorFactory<PlainColorPropertyManager>
							  , public EditorImpl<PlainColorEditWidget>
{
	Q_OBJECT
public:
	typedef EditorImpl<PlainColorEditWidget> Impl;
	PlainColorEditorFactory(QObject *parent = 0);
    ~PlainColorEditorFactory();
protected:
    virtual void connectPropertyManager(PlainColorPropertyManager *manager);
    virtual void disconnectPropertyManager(PlainColorPropertyManager *manager);
	virtual QWidget *createEditor(PlainColorPropertyManager *manager, QtProperty *property,
								  QWidget *parent);
private slots:
	void slotPropertyChanged(QtProperty *property, const QColor &value);
    void slotSetValue(const QColor &value);
	void slotEditorDestroyed(QObject* object);
};
