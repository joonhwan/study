#include "MainWindow.h"
#include <QtGui>

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
	, m_script(new QScriptEngine(this))
{
	m_editor = new QPlainTextEdit;
	
	QVBoxLayout *layout = new QVBoxLayout(this);
}

//virtual
MainWindow::~MainWindow()
{
}
