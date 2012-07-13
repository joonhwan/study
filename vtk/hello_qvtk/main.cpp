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

#define MY_CODE
#ifdef MY_CODE

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
	vtkSmartPointer<vtkConeSource> cone
		= vtkSmartPointer<vtkConeSource>::New ();
	cone->SetHeight(3.0);
	cone->SetRadius(1.0);
	cone->SetResolution(100);

	vtkSmartPointer<vtkPolyDataMapper> coneMapper
		= vtkSmartPointer<vtkPolyDataMapper>::New ();
	coneMapper->SetInput(cone->GetOutput());

	vtkSmartPointer<vtkActor> coneActor
		= vtkSmartPointer<vtkActor>::New ();
	coneActor->SetMapper(coneMapper);
	coneActor->GetProperty()->SetColor(1.0, 0., 0.);

	vtkSmartPointer<vtkRenderer> ren
		= vtkSmartPointer<vtkRenderer>::New ();
	ren->SetBackground(0., 0., 0);
	ren->AddActor(coneActor);

	w->GetRenderWindow()->AddRenderer(ren);

	// cone->Delete ();
	// coneMapper->Delete ();
	// coneActor->Delete ();
	// ren->Delete ();
	// cone->Delete ();
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

#else

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	QVTKWidget* widget = new QVTKWidget( &window );
	widget->resize(256,256);
	window.resize(256,256);
	vtkPNGReader* reader = vtkPNGReader::New();
	char* fname = "c:/prj/oss/not-mine/qtmediahub/skins/matinee/images/simple_blue_widescreen.png";
	reader->SetFileName(fname);
	vtkImageViewer* image_view = vtkImageViewer::New();
	image_view->SetInput(reader->GetOutput());
	widget->SetRenderWindow(image_view->GetRenderWindow());
	image_view->SetupInteractor(widget->GetRenderWindow()->GetInteractor());
	window.setCentralWidget( widget );
	window.show();
	return app.exec();
}

#endif	// MY_CODE
