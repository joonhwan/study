#include "PlainColorProperty.h"
#include "qtpropertybrowser/qtpropertybrowserutils_p.h"

#include <QApplication>
#include <QColorDialog>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QStyleOption>
#include <QPainter>

// Set a hard coded left margin to account for the indentation
// of the tree view icon when switching to an editor
// from qtpropertybrowser/qteditorfactory.cpp
static inline void setupTreeViewEditorMargin(QLayout *lt)
{
    enum { DecorationMargin = 4 };
    if (QApplication::layoutDirection() == Qt::LeftToRight)
        lt->setContentsMargins(DecorationMargin, 0, 0, 0);
    else
        lt->setContentsMargins(0, 0, DecorationMargin, 0);
}

// QtColorPropertyManager

PlainColorPropertyManager::PlainColorPropertyManager(QObject *parent)
	: QtColorPropertyManager(parent)
{
}

//virtual
PlainColorPropertyManager::~PlainColorPropertyManager()
{
}

void PlainColorPropertyManager::initializeProperty(QtProperty *property)
{
    QtColorPropertyManager::initializeProperty(property);

	// remove "alpha" sub-property.
	QList<QtProperty*> children = property->subProperties();
	foreach(QtProperty* child, children) {
		if (child->propertyName()==tr("Alpha")) {
			property->removeSubProperty(child);
			break;
		}
	}
}

PlainColorEditWidget::PlainColorEditWidget(QWidget *parent) :
    QWidget(parent),
    m_pixmapLabel(new QLabel),
    m_label(new QLabel),
    m_button(new QToolButton)
{
	m_label->setContentsMargins(4,4,4,4);

    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setFixedWidth(20);
    setFocusProxy(m_button);
    setFocusPolicy(m_button->focusPolicy());
    m_button->setText(tr("..."));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::brushValuePixmap(QBrush(m_color)));
    m_label->setText(colorToString(m_color));
}

void PlainColorEditWidget::setValue(const QColor &c)
{
    if (m_color != c) {
        m_color = c;
        m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::brushValuePixmap(QBrush(c)));
        m_label->setText(colorToString(c));
		emit valueChanged(m_color);
    }
}

void PlainColorEditWidget::buttonClicked()
{
    bool ok = false;
    QColor oldcolor = m_color;
    QColor newColor = QColorDialog::getColor(oldcolor, this);
    if (newColor.isValid() && newColor != oldcolor) {
        setValue(newColor);
    }
}

bool PlainColorEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button) {
        switch (ev->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease: { // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            switch (static_cast<const QKeyEvent*>(ev)->key()) {
            case Qt::Key_Escape:
            case Qt::Key_Enter:
            case Qt::Key_Return:
                ev->ignore();
                return true;
            default:
                break;
            }
        }
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, ev);
}

void PlainColorEditWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QString PlainColorEditWidget::colorToString(const QColor& color)
{
	return
		QString("R%1,G%2,B%3")
		.arg(color.red(), 3)
		.arg(color.green(), 3)
		.arg(color.blue(), 3);
}

/*!
    \class PlainColorEditorFactory
*/

PlainColorEditorFactory::PlainColorEditorFactory(QObject *parent)
	: QtAbstractEditorFactory<PlainColorPropertyManager>(parent)
{
}

PlainColorEditorFactory::~PlainColorEditorFactory()
{
}

void PlainColorEditorFactory::connectPropertyManager(PlainColorPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty*,QColor)),
            this, SLOT(slotPropertyChanged(QtProperty*,QColor)));
}

QWidget *PlainColorEditorFactory::createEditor(PlainColorPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    PlainColorEditWidget *editor = Impl::createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QColor)), this, SLOT(slotSetValue(QColor)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void PlainColorEditorFactory::disconnectPropertyManager(PlainColorPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(slotPropertyChanged(QtProperty*,QColor)));
}

void PlainColorEditorFactory::slotPropertyChanged(QtProperty *property, const QColor &value)
{
	if (!createdEditors.contains(property)) {
		return;
	}

	PlainColorPropertyManager* manager = propertyManager(property);
	if (!manager) {
		return;
	}

	QList<PlainColorEditWidget*> editors = createdEditors[property];
	QListIterator<PlainColorEditWidget*> itEditor(editors);
	while (itEditor.hasNext()) {
		PlainColorEditWidget* editor = itEditor.next();
		editor->setValue(value);
	}
}

void PlainColorEditorFactory::slotSetValue(const QColor &value)
{
	QObject* object = sender();
	EditorToPropertyMap::iterator it = editorToProperty.begin();
	EditorToPropertyMap::iterator itEnd = editorToProperty.end();
	for (; it != itEnd; ++it) {
		if (it.key() == object) {
			QtProperty* property = it.value();
			PlainColorPropertyManager* manager = propertyManager(property);
			if (manager) {
				manager->setValue(property, value);
			}
			return;
		}
	}
}

void PlainColorEditorFactory::slotEditorDestroyed(QObject* object)
{
	Impl::slotEditorDestroyed(object);
}
