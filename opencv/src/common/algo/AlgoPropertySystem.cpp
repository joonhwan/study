#include "AlgoPropertySystem.h"
#include "property/PlainColorProperty.h"
#include "qtpropertybrowser/QtIntPropertyManager"
#include "qtpropertybrowser/QtSpinBoxFactory"

AlgoPropertySystem::AlgoPropertySystem(QObject* parent)
	: PropertySystem(parent)
{
	plainColorManager = new PlainColorPropertyManager(this);

	connect(plainColorManager, SIGNAL(valueChanged(QtProperty*, const QColor&)),
			SLOT(valueChanged(QtProperty*, const QColor&)));

	m_plainColorEditFactory = new PlainColorEditorFactory(this);
}

//virtual
AlgoPropertySystem::~AlgoPropertySystem()
{
}

//virtual
void AlgoPropertySystem::prepareEditor(QtAbstractPropertyBrowser* editor)
{
	PropertySystem::prepareEditor(editor);

	// override default color editor.
	editor->setFactoryForManager(plainColorManager, m_plainColorEditFactory);
	editor->setFactoryForManager(plainColorManager->subIntPropertyManager(), m_spinBoxFactory);
}

