#pragma once

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=0);
    virtual ~MainWindow();
signals:
public slots:
protected:
	QScriptEngine* m_script;
	QPlainTextEdit* m_editor;
};
