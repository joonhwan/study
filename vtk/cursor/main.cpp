#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QToolBar>
#include <QVTKWidget.h>

#include <vtkActor.h>
#include <vtkCursor3D.h>
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

#define PLEASE_USE_QVTK
#ifdef PLEASE_USE_QVTK
	QVTKWidget* widget = new QVTKWidget;
	{
		// Create a sphere
		vtkSmartPointer<vtkSphereSource> sphereSource =
			vtkSmartPointer<vtkSphereSource>::New();
		sphereSource->SetCenter(0.0, 0.0, 0.0);
		sphereSource->SetRadius(5.0);
		sphereSource->Update();

		// Create a mapper and actor
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(sphereSource->GetOutputPort());

		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);

		// Create a renderer, render window, and interactor
		vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
		renderer->SetBackground(1,1,1); // Background color white

		// Add the actor to the scene
		renderer->AddActor(actor);

		vtkSmartPointer<vtkCursor3D> cursor =
			vtkSmartPointer<vtkCursor3D>::New();
		cursor->SetModelBounds(-10,10,-10,10,-10,10);
		cursor->AllOn();
		cursor->OutlineOff();
		cursor->Update();

		vtkSmartPointer<vtkPolyDataMapper> cursorMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		cursorMapper->SetInputConnection(cursor->GetOutputPort());
		vtkSmartPointer<vtkActor> cursorActor =
			vtkSmartPointer<vtkActor>::New();
		cursorActor->GetProperty()->SetColor(1,0,0);
		cursorActor->SetMapper(cursorMapper);
		renderer->AddActor(cursorActor);

		widget->GetRenderWindow()->AddRenderer(renderer);
	}

	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	window.resize(256,256);
	window.setCentralWidget( widget );
	window.show();

	return app.exec();
#else
	// Create a sphere
	vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(0.0, 0.0, 0.0);
	sphereSource->SetRadius(5.0);
	sphereSource->Update();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actor to the scene
	renderer->AddActor(actor);
	renderer->SetBackground(1,1,1); // Background color white

	vtkSmartPointer<vtkCursor3D> cursor =
		vtkSmartPointer<vtkCursor3D>::New();
	cursor->SetModelBounds(-10,10,-10,10,-10,10);
	cursor->AllOn();
	cursor->OutlineOff();
	cursor->Update();

	vtkSmartPointer<vtkPolyDataMapper> cursorMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	cursorMapper->SetInputConnection(cursor->GetOutputPort());
	vtkSmartPointer<vtkActor> cursorActor =
		vtkSmartPointer<vtkActor>::New();
	cursorActor->GetProperty()->SetColor(1,0,0);
	cursorActor->SetMapper(cursorMapper);
	renderer->AddActor(cursorActor);

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();
#endif
}
