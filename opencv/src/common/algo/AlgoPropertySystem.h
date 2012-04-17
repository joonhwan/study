#pragma once

#include "property/PropertySystem.h"

class AlgoPropertySystem : public PropertySystem
{
    Q_OBJECT
public:
	AlgoPropertySystem(QObject* parent=0);
    virtual ~AlgoPropertySystem();
	virtual void prepareEditor(QtAbstractPropertyBrowser* editor);
	class PlainColorPropertyManager* plainColorManager;
protected:
	class PlainColorEditorFactory* m_plainColorEditFactory;
};
