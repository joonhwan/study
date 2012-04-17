#include "SliderSpinValueProperty.h"
#include "qtpropertybrowser/qtpropertybrowserutils_p.h"

#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>

// Set a hard coded left margin to account for the indentation
// of the tree view icon when switching to an editor
// from qtpropertybrowser/qteditorfactory.cpp
static inline void setupTreeViewEditorMargin(QLayout *layout)
{
    enum { DecorationMargin = 4 };
    if (QApplication::layoutDirection() == Qt::LeftToRight)
        layout->setContentsMargins(DecorationMargin, 0, 0, 0);
    else
        layout->setContentsMargins(0, 0, DecorationMargin, 0);
}

// QtColorPropertyManager

SliderSpinValuePropertyManager::SliderSpinValuePropertyManager(QObject *parent)
	: QtIntPropertyManager(parent)
{
}

//virtual
SliderSpinValuePropertyManager::~SliderSpinValuePropertyManager()
{
}

SliderSpinValueEditWidget::SliderSpinValueEditWidget(QWidget *parent)
	: QWidget(parent)
{
	m_slider = new QSlider(Qt::Horizontal);
	m_spinBox = new QSpinBox;

    connect(m_slider, SIGNAL(valueChanged(int)), SLOT(setValue(int)));
	connect(m_spinBox, SIGNAL(valueChanged(int)), SLOT(setValue(int)));

	QHBoxLayout *layout = new QHBoxLayout;
    setupTreeViewEditorMargin(layout);
    layout->setSpacing(0);
    layout->addWidget(m_slider);
    layout->addWidget(m_spinBox);
	setLayout(layout);
}

void SliderSpinValueEditWidget::setRange(int min, int max)
{
	m_slider->setRange(min, max);
	m_spinBox->setRange(min, max);
}

void SliderSpinValueEditWidget::setValue(int value)
{
    if (m_value!=value) {
		m_value = value;
		m_slider->setValue(value);
		m_spinBox->setValue(value);
		emit valueChanged(value);
	}
}

/*!
  \class SliderSpinValueEditorFactory
*/

SliderSpinValueEditorFactory::SliderSpinValueEditorFactory(QObject *parent)
	: QtAbstractEditorFactory<SliderSpinValuePropertyManager>(parent)
{
}

SliderSpinValueEditorFactory::~SliderSpinValueEditorFactory()
{
}

void SliderSpinValueEditorFactory::connectPropertyManager(SliderSpinValuePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty*,int)),
			SLOT(slotPropertyChanged(QtProperty*,int)));
}

QWidget *SliderSpinValueEditorFactory::createEditor(SliderSpinValuePropertyManager *manager,
													QtProperty *property, QWidget *parent)
{
    SliderSpinValueEditWidget *editor = Impl::createEditor(property, parent);
	editor->setRange(manager->minimum(property),
					 manager->maximum(property));
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(int)), SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)), SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void SliderSpinValueEditorFactory::disconnectPropertyManager(SliderSpinValuePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(slotPropertyChanged(QtProperty*,QColor)));
}

void SliderSpinValueEditorFactory::slotPropertyChanged(QtProperty *property, int value)
{
	if (!createdEditors.contains(property)) {
		return;
	}

	SliderSpinValuePropertyManager* manager = propertyManager(property);
	if (!manager) {
		return;
	}

	QList<SliderSpinValueEditWidget*> editors = createdEditors[property];
	QListIterator<SliderSpinValueEditWidget*> itEditor(editors);
	while (itEditor.hasNext()) {
		SliderSpinValueEditWidget* editor = itEditor.next();
		editor->setValue(value);
	}
}

void SliderSpinValueEditorFactory::slotSetValue(int value)
{
	QObject* object = sender();
	EditorToPropertyMap::iterator it = editorToProperty.begin();
	EditorToPropertyMap::iterator itEnd = editorToProperty.end();
	for (; it != itEnd; ++it) {
		if (it.key() == object) {
			QtProperty* property = it.value();
			SliderSpinValuePropertyManager* manager = propertyManager(property);
			if (manager) {
				manager->setValue(property, value);
			}
			return;
		}
	}
}

void SliderSpinValueEditorFactory::slotEditorDestroyed(QObject* object)
{
	Impl::slotEditorDestroyed(object);
}
