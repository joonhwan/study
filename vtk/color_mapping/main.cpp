// from http://markmail.org/message/uptb57uqf2hceqxt#query:+page:1+mid:ewlqkvhvd36ax6f4+state:results
//
// see the attachment in the article.(vtkqt4-test.tar.gz)

// #include "vldcheck.h"
#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QToolBar>
#include <QVTKWidget.h>
#include <vtkConeSource.h>
#include <vtkImageViewer.h>
#include <vtkPNGReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include <vtkStructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkStructuredGrid.h>

// #if defined(_DEBUG) && defined(WIN32)
// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>
// class MemLeakDetector
// {
// public:
// 	MemLeakDetector()
// 	{
// 		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
// 	}
// 	~MemLeakDetector()
// 	{
// 	}
// } detector;
// #endif

class QMyVtkWidget : public QVTKWidget
{
public:
	QMyVtkWidget(QWidget* parent = 0)
		: QVTKWidget(parent)
	{
	}
	virtual ~QMyVtkWidget()
	{
	}
};

void doVtk(QVTKWidget* w)
{
	vtkSmartPointer<vtkLookupTable> lut
		= vtkSmartPointer<vtkLookupTable>::New ();
	lut->SetNumberOfColors(16);
	lut->SetHueRange(0., 0.667);
	lut->Build();

	vtkSmartPointer<vtkStructuredGridReader> reader
		= vtkSmartPointer<vtkStructuredGridReader>::New ();
	reader->SetFileName("c:/Temp/subset.vtk");
	reader->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper
		= vtkSmartPointer<vtkDataSetMapper>::New ();
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetScalarRange(reader->GetOutput()->GetScalarRange());

	vtkSmartPointer<vtkActor> actors
		= vtkSmartPointer<vtkActor>::New ();
	actors->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> ren
		= vtkSmartPointer<vtkRenderer>::New ();
	ren->AddActor(actors);
	ren->SetBackground(0., 0., 0);

	w->GetRenderWindow()->AddRenderer(ren);
}

int main( int argc, char* argv[] )
{
	QApplication app(argc, argv);
	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	QVTKWidget* widget = new QMyVtkWidget;
	doVtk(widget);
	widget->resize(256,256);
	window.resize(256,256);
	window.setCentralWidget( widget );
	window.show();
	return app.exec();
};
