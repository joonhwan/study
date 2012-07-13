#include "SpmData.h"
#include "demosource.h"
#include <QApplication>
#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QToolBar>
#include <QVTKWidget.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkContourFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkElevationFilter.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProgrammableSource.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkReverseSense.h>
#include <vtkShrinkFilter.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkVersion.h>
#include <vld.h>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("spm_tool");

	CSpmData spm;
	// spm.loadFromFile(QString::fromLatin1("c:/prj/samples/markkim/a1.spm"));
	// spm.loadFromFile(QString::fromLatin1("c:/prj/samples/markkim/50.spm"));
	// spm.loadFromFile(QString::fromLatin1("c:/prj/samples/markkim/Test1.spm"));
	// spm.loadFromFile(QString::fromLatin1("c:/prj/samples/markkim/Test2.spm"));
	spm.loadFromFile(QString::fromLatin1("c:/prj/samples/markkim/gogo.spm"));
	// // return doStructuredGridDemo(spm);
	// // return doStructuredGrid2Demo(spm);
	// // return doSurfaceFromUnorganizedPointsDemo(spm);
	return doStructuredGridQtDemo(spm, app);
	// return doRectilinearGridQtDemo(spm, app);
	// return doSimpleQtDemo(spm, app);

		// QMainWindow window;
		// QMenu* menu = window.menuBar()->addMenu("&File");
		// menu->addAction("&Quit", &window, SLOT(close()));
		// QVTKWidget* w = new QVTKWidget;

		// vtkSmartPointer<vtkConeSource> cone
		// 	= vtkSmartPointer<vtkConeSource>::New ();
		// cone->SetHeight(3.0);
		// cone->SetRadius(1.0);
		// cone->SetResolution(100);

		// vtkSmartPointer<vtkPolyDataMapper> coneMapper
		// 	= vtkSmartPointer<vtkPolyDataMapper>::New ();
		// coneMapper->SetInput(cone->GetOutput());

		// vtkSmartPointer<vtkActor> coneActor
		// 	= vtkSmartPointer<vtkActor>::New ();
		// coneActor->SetMapper(coneMapper);
		// coneActor->GetProperty()->SetColor(1.0, 0., 0.);

		// vtkSmartPointer<vtkRenderer> ren
		// 	= vtkSmartPointer<vtkRenderer>::New ();
		// ren->SetBackground(0., 0., 0);
		// ren->AddActor(coneActor);

		// w->GetRenderWindow()->AddRenderer(ren);

		// w->resize(256,256);
		// window.resize(256,256);
		// window.setCentralWidget(w );
		// window.show();
		// return app.exec();
}

