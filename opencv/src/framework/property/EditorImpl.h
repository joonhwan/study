#pragma once

#include "qtpropertybrowser/QtProperty"
#include <QList>
#include <QMap>

template <class Editor>
class EditorImpl
{
public:
    typedef QList<Editor *> EditorList;
    typedef QMap<QtProperty *, EditorList> PropertyToEditorListMap;
    typedef QMap<Editor *, QtProperty *> EditorToPropertyMap;

    Editor *createEditor(QtProperty *property, QWidget *parent)
	{
		Editor *editor = new Editor(parent);
		initializeEditor(property, editor);
		return editor;
	}
    void initializeEditor(QtProperty *property, Editor *editor)
	{
		PropertyToEditorListMap::iterator it = createdEditors.find(property);
		if (it == createdEditors.end()) {
			it = createdEditors.insert(property, EditorList());
		}
		it.value().append(editor);
		editorToProperty.insert(editor, property);
	}
    void slotEditorDestroyed(QObject *object)
	{
		EditorToPropertyMap::iterator it = editorToProperty.begin();
		const EditorToPropertyMap::iterator itEnd = editorToProperty.end();
		for (; it !=  itEnd; ++it) {
			if (it.key() == object) {
				Editor *editor = it.key();
				QtProperty *property = it.value();
				const  PropertyToEditorListMap::iterator pit = createdEditors.find(property);
				if (pit != createdEditors.end()) {
					pit.value().removeAll(editor);
					if (pit.value().empty())
						createdEditors.erase(pit);
				}
				editorToProperty.erase(it);
				return;
			}
		}
	}

    PropertyToEditorListMap  createdEditors;
    EditorToPropertyMap editorToProperty;
};
