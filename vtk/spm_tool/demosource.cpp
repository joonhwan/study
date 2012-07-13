#include "SpmData.h"

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
#include <vtkCubeAxesActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkElevationFilter.h>
#include <vtkFloatArray.h>
#include <vtkLight.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataWriter.h>
#include <vtkProgrammableSource.h>
#include <vtkProperty.h>
#include <vtkRectilinearGrid.h>
#include <vtkRectilinearGridGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkReverseSense.h>
#include <vtkShrinkFilter.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridWriter.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkVersion.h>

#include "MouseInteractorStyle.h"
vtkStandardNewMacro(MouseInteractorStyle);

int doStructuredGridDemo(CSpmData& spm)
{
		// Create a grid
	vtkSmartPointer<vtkStructuredGrid> structuredGrid =
		vtkSmartPointer<vtkStructuredGrid>::New();

	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	unsigned int numi = spm.countX();
	unsigned int numj = spm.countY();
	unsigned int numk = 1;

	for(unsigned int k = 0; k < numk; k++)
    {
		for(unsigned int j = 0; j < numj; j++)
		{
			for(unsigned int i = 0; i < numi; i++)
			{
				points->InsertNextPoint(i, j, spm.heightAt(i, j));
			}
		}
    }

	// Specify the dimensions of the grid
	structuredGrid->SetDimensions(numi, numj, numk);
	structuredGrid->SetPoints(points);

	std::cout << "There are "
			  << structuredGrid->GetNumberOfPoints() << " points."
			  << std::endl;
	std::cout << "There are "
			  << structuredGrid->GetNumberOfCells() << " cells."
			  << std::endl;

	vtkSmartPointer<vtkShrinkFilter> shrinkFilter =
		vtkSmartPointer<vtkShrinkFilter>::New();
#if VTK_MAJOR_VERSION <= 5
	shrinkFilter->SetInputConnection(structuredGrid->GetProducerPort());
#else
	shrinkFilter->SetInputData(structuredGrid);
#endif
	shrinkFilter->SetShrinkFactor(.8);

	// Create a mapper and actor
	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(shrinkFilter->GetOutputPort());
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
	renderer->SetBackground(.2, .3, .4);

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

int doStructuredGrid2Demo(CSpmData& spm)
{
		// Create a grid
	vtkSmartPointer<vtkStructuredGrid> structuredGrid =
		vtkSmartPointer<vtkStructuredGrid>::New();

	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	unsigned int numi = spm.countX();
	unsigned int numj = spm.countY();
	unsigned int numk = 1;

	// for(unsigned int k = 0; k < numk; k++)
    {
		for(unsigned int j = 0; j < numj; j++)
		{
			for(unsigned int i = 0; i < numi; i++)
			{
				points->InsertPoint(i + j*numi,
									i,
									j,
									spm.heightAt(i, j));
			}
		}
    }

	// Specify the dimensions of the grid
	structuredGrid->SetDimensions(numi, numj, numk);
	structuredGrid->SetPoints(points);

	std::cout << "There are "
			  << structuredGrid->GetNumberOfPoints() << " points."
			  << std::endl;
	std::cout << "There are "
			  << structuredGrid->GetNumberOfCells() << " cells."
			  << std::endl;

	vtkSmartPointer<vtkStructuredGridGeometryFilter> sggFilter =
		vtkSmartPointer<vtkStructuredGridGeometryFilter>::New ();
	sggFilter->SetInput(structuredGrid);

	// lookup table
	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New ();
	QList<float> minMax = spm.minMax();
	lut->SetTableRange(minMax[0], minMax[1]);
	lut->SetHueRange(0.667, 0.);
	lut->SetRampToLinear();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sggFilter->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetUseLookupTableScalarRange(1);

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
	renderer->SetBackground(.2, .3, .4);

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

int doStructuredGrid3Demo(CSpmData& spm)
{
		// Create a grid
	vtkSmartPointer<vtkStructuredGrid> structuredGrid =
		vtkSmartPointer<vtkStructuredGrid>::New();

	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	unsigned int numi = spm.countX();
	unsigned int numj = spm.countY();
	unsigned int numk = 1;

	// for(unsigned int k = 0; k < numk; k++)
    {
		for(unsigned int j = 0; j < numj; j++)
		{
			for(unsigned int i = 0; i < numi; i++)
			{
				points->InsertPoint(i + j*numi,
									i,
									j,
									spm.heightAt(i, j));
			}
		}
    }

	// Specify the dimensions of the grid
	structuredGrid->SetDimensions(numi, numj, numk);
	structuredGrid->SetPoints(points);

	std::cout << "There are "
			  << structuredGrid->GetNumberOfPoints() << " points."
			  << std::endl;
	std::cout << "There are "
			  << structuredGrid->GetNumberOfCells() << " cells."
			  << std::endl;

	vtkSmartPointer<vtkStructuredGridGeometryFilter> sggFilter =
		vtkSmartPointer<vtkStructuredGridGeometryFilter>::New ();
	sggFilter->SetInput(structuredGrid);

	vtkSmartPointer<vtkElevationFilter> elvFilter =
		vtkSmartPointer<vtkElevationFilter>::New ();
	elvFilter->SetInputConnection(sggFilter->GetOutputPort());

	// Create a mapper and actor
	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(elvFilter->GetOutputPort());

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
	renderer->SetBackground(.2, .3, .4);

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

int doRectilinearGridQtDemo(CSpmData& spm, QApplication& app)
{
	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	QVTKWidget* widget = new QVTKWidget;

	int i;
	static float x[47]={
		-1.22396, -1.17188, -1.11979, -1.06771, -1.01562, -0.963542,
		-0.911458, -0.859375, -0.807292, -0.755208, -0.703125, -0.651042,
		-0.598958, -0.546875, -0.494792, -0.442708, -0.390625, -0.338542,
		-0.286458, -0.234375, -0.182292, -0.130209, -0.078125, -0.026042,
		0.0260415, 0.078125, 0.130208, 0.182291, 0.234375, 0.286458,
		0.338542, 0.390625, 0.442708, 0.494792, 0.546875, 0.598958,
		0.651042, 0.703125, 0.755208, 0.807292, 0.859375, 0.911458,
		0.963542, 1.01562, 1.06771, 1.11979, 1.17188};
	static float y[33]={-1.25, -1.17188, -1.09375, -1.01562, -0.9375, -0.859375,
						-0.78125, -0.703125, -0.625, -0.546875, -0.46875, -0.390625,
						-0.3125, -0.234375, -0.15625, -0.078125, 0, 0.078125,
						0.15625, 0.234375, 0.3125, 0.390625, 0.46875, 0.546875,
						0.625, 0.703125, 0.78125, 0.859375, 0.9375, 1.01562,
						1.09375, 1.17188, 1.25};
	static float z[44]={0, 0.1, 0.2, 0.3, 0.4, 0.5,
						0.6, 0.7, 0.75, 0.8, 0.9, 1,
						1.1, 1.2, 1.3, 1.4, 1.5, 1.6,
						1.7, 1.75, 1.8, 1.9, 2, 2.1,
						2.2, 2.3, 2.4, 2.5, 2.6, 2.7,
						2.75, 2.8, 2.9, 3, 3.1, 3.2,
						3.3, 3.4, 3.5, 3.6, 3.7, 3.75,
						3.8, 3.9};

	// Create a rectilinear grid by defining three arrays specifying the
	// coordinates in the x-y-z directions.
	vtkFloatArray *xCoords = vtkFloatArray::New();
	for (i=0; i<47; i++) xCoords->InsertNextValue(x[i]);

	vtkFloatArray *yCoords = vtkFloatArray::New();
	for (i=0; i<33; i++) yCoords->InsertNextValue(y[i]);

	vtkFloatArray *zCoords = vtkFloatArray::New();
	for (i=0; i<44; i++) zCoords->InsertNextValue(z[i]);

	// The coordinates are assigned to the rectilinear grid. Make sure that
	// the number of values in each of the XCoordinates, YCoordinates,
	// and ZCoordinates is equal to what is defined in SetDimensions().
	//
	vtkRectilinearGrid *rgrid = vtkRectilinearGrid::New();
    rgrid->SetDimensions(47,33,44);
    rgrid->SetXCoordinates(xCoords);
    rgrid->SetYCoordinates(yCoords);
    rgrid->SetZCoordinates(zCoords);

    // Extract a plane from the grid to see what we've got.
	vtkRectilinearGridGeometryFilter *plane = vtkRectilinearGridGeometryFilter::New();
    plane->SetInput(rgrid);
    plane->SetExtent(0,46, 16,16, 0,43);

	vtkPolyDataMapper *rgridMapper = vtkPolyDataMapper::New();
	rgridMapper->SetInputConnection(plane->GetOutputPort());

	// Create the usual rendering stuff.
	vtkRenderer *renderer = vtkRenderer::New();

	vtkActor *wireActor = vtkActor::New();
	wireActor->SetMapper(rgridMapper);
	// wireActor->GetProperty()->SetRepresentationToWireframe();
	wireActor->GetProperty()->SetColor(0,0,0);
	renderer->AddActor(wireActor);

	vtkCubeAxesActor* cubeAxesActor = vtkCubeAxesActor::New();
 	cubeAxesActor->SetBounds(plane->GetOutput()->GetBounds());
	cubeAxesActor->SetCamera(renderer->GetActiveCamera());
	renderer->AddActor(cubeAxesActor);

	renderer->SetBackground(1,1,1);
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Elevation(60.0);
	renderer->GetActiveCamera()->Azimuth(30.0);
	renderer->GetActiveCamera()->Zoom(1.0);

	widget->GetRenderWindow()->AddRenderer(renderer);

	widget->resize(256,256);
	window.resize(256,256);
	window.setCentralWidget(widget);
	window.show();
	return app.exec();
}


int doStructuredGridQtDemo(CSpmData& spm, QApplication& app)
{
	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	QVTKWidget* widget = new QVTKWidget;

	// Create a grid
	vtkSmartPointer<vtkStructuredGrid> structuredGrid =
		vtkSmartPointer<vtkStructuredGrid>::New();

	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	unsigned int numi = spm.countX();
	unsigned int numj = spm.countY();
	unsigned int numk = 1;

	vtkSmartPointer<vtkDoubleArray> sc =
		vtkSmartPointer<vtkDoubleArray>::New ();

	// for(unsigned int k = 0; k < numk; k++)
    {
		for(unsigned int j = 0; j < numj; j++)
		{
			for(unsigned int i = 0; i < numi; i++)
			{
				double height = spm.heightAt(i, j);
				points->InsertPoint(i + j*numi,
									i,
									j,
									height);
				sc->InsertTuple1(i + j*numi,
									 height);
			}
		}
    }

	// Specify the dimensions of the grid
	structuredGrid->SetDimensions(numi, numj, numk);
	structuredGrid->SetPoints(points);
	structuredGrid->GetPointData()->SetScalars(sc);

	if (0)
	{
		vtkNew<vtkStructuredGridWriter> writer;
		writer->SetFileName("c:/temp/spm-grid.vtk");
		writer->SetInput( structuredGrid );
		writer->Write();
	}

	std::cout << "There are "
			  << structuredGrid->GetNumberOfPoints() << " points."
			  << std::endl;
	std::cout << "There are "
			  << structuredGrid->GetNumberOfCells() << " cells."
			  << std::endl;

	vtkSmartPointer<vtkStructuredGridGeometryFilter> sggFilter =
		vtkSmartPointer<vtkStructuredGridGeometryFilter>::New ();
	sggFilter->SetInput(structuredGrid);

	if (0)
	{
		vtkNew<vtkPolyDataWriter> writer;
		writer->SetFileName("c:/temp/spm.vtk");
		writer->SetInputConnection(sggFilter->GetOutputPort());
		writer->Write();
	}

	// vtkSmartPointer<vtkElevationFilter> elevFilter =
	// 	vtkSmartPointer<vtkElevationFilter>::New ();
	// elevFilter->SetInputConnection(sggFilter->GetOutputPort());

	// QList<float> minMax = spm.minMax();
	// elevFilter->SetLowPoint(0,0,minMax[0]);
	// elevFilter->SetHighPoint(0,0,minMax[1]);

	// lookup table
	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New ();
	QList<float> minMax = spm.minMax();
	lut->SetTableRange(minMax[0], minMax[1]);
	lut->SetHueRange(0.667, 0.);
	lut->SetRampToLinear();
	lut->Build();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sggFilter->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetUseLookupTableScalarRange(1);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	// actor->GetProperty()->EdgeVisibilityOn();
	actor->GetProperty()->ShadingOn();

	// vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor
	// 				= vtkSmartPointer<vtkCubeAxesActor>::New();
	// cubeAxesActor->SetMapper(mapper);
    // cubeAxesActor->SetBounds(points->GetBounds());

	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(0., 0., 0);
	renderer->AddActor(actor);
	// cubeAxesActor->SetCamera(renderer->GetActiveCamera());
	// renderer->AddActor(cubeAxesActor);

#ifdef TEST_MOUSE_PICK
	// Set the custom stype to use for interaction.
	vtkSmartPointer<MouseInteractorStyle> style =
		vtkSmartPointer<MouseInteractorStyle>::New();
	style->SetDefaultRenderer(renderer);
	style->Data = sggFilter->GetOutput();
	widget->GetInteractor()->SetInteractorStyle(style);
#endif

	// Set up the lighting.    //
	{
		vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
		light->SetFocalPoint(1.875,0.6125,0);
		light->SetPosition(0.875,1.6125,800);
		// light->SetAmbientColor(1., 0., 0.);
		renderer->AddLight(light);
	}

	{
		vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
		light->SetFocalPoint(1.875,0.6125,0);
		light->SetPosition(0.875,1.6125,-800);
		// light->SetAmbientColor(1., 0., 0.);
		renderer->AddLight(light);
	}

	widget->GetRenderWindow()->AddRenderer(renderer);

	widget->resize(256,256);
	window.resize(256,256);
	window.setCentralWidget( widget );
	window.show();
	return app.exec();
}

int __doStructuredGridQtDemo(CSpmData& spm, QApplication& app)
{
	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	QVTKWidget* widget = new QVTKWidget;

	// Create a grid
	vtkSmartPointer<vtkStructuredGrid> structuredGrid =
		vtkSmartPointer<vtkStructuredGrid>::New();

	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	unsigned int numi = spm.countX();
	unsigned int numj = spm.countY();
	unsigned int numk = 1;

	// for(unsigned int k = 0; k < numk; k++)
    {
		for(unsigned int j = 0; j < numj; j++)
		{
			for(unsigned int i = 0; i < numi; i++)
			{
				points->InsertPoint(i + j*numi,
									i,
									j,
									spm.heightAt(i, j));
			}
		}
    }

	// Specify the dimensions of the grid
	structuredGrid->SetDimensions(numi, numj, numk);
	structuredGrid->SetPoints(points);

	std::cout << "There are "
			  << structuredGrid->GetNumberOfPoints() << " points."
			  << std::endl;
	std::cout << "There are "
			  << structuredGrid->GetNumberOfCells() << " cells."
			  << std::endl;

	vtkSmartPointer<vtkStructuredGridGeometryFilter> sggFilter =
		vtkSmartPointer<vtkStructuredGridGeometryFilter>::New ();
	sggFilter->SetInput(structuredGrid);

	// vtkSmartPointer<vtkElevationFilter> elevFilter =
	// 	vtkSmartPointer<vtkElevationFilter>::New ();
	// elevFilter->SetInputConnection(sggFilter->GetOutputPort());

	// QList<float> minMax = spm.minMax();
	// elevFilter->SetLowPoint(0,0,minMax[0]);
	// elevFilter->SetHighPoint(0,0,minMax[1]);

	// // lookup table
	// vtkSmartPointer<vtkLookupTable> lut =
	// 	vtkSmartPointer<vtkLookupTable>::New ();
	// QList<float> minMax = spm.minMax();
	// lut->SetTableRange(minMax[0], minMax[1]);
	// lut->SetHueRange(0.667, 0.);
	// lut->SetRampToLinear();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sggFilter->GetOutputPort());
	// mapper->SetLookupTable(lut);
	// mapper->SetUseLookupTableScalarRange(1);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	// actor->GetProperty()->EdgeVisibilityOn();
	actor->GetProperty()->ShadingOn();

	// vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor
	// 				= vtkSmartPointer<vtkCubeAxesActor>::New();
	// cubeAxesActor->SetMapper(mapper);
    // cubeAxesActor->SetBounds(points->GetBounds());

	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(0., 0., 0);
	renderer->AddActor(actor);
	// cubeAxesActor->SetCamera(renderer->GetActiveCamera());
	// renderer->AddActor(cubeAxesActor);


	// Set up the lighting.    //
	{
		vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
		light->SetFocalPoint(1.875,0.6125,0);
		light->SetPosition(0.875,1.6125,400);
		// light->SetAmbientColor(1., 0., 0.);
		renderer->AddLight(light);
	}

	{
		vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
		light->SetFocalPoint(1.875,0.6125,0);
		light->SetPosition(0.875,1.6125,-400);
		// light->SetAmbientColor(1., 0., 0.);
		renderer->AddLight(light);
	}

	widget->GetRenderWindow()->AddRenderer(renderer);

	widget->resize(256,256);
	window.resize(256,256);
	window.setCentralWidget( widget );
	window.show();
	return app.exec();
}

int doStructuredGridQt2Demo(CSpmData& spm, QApplication& app)
{
	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	QVTKWidget* widget = new QVTKWidget;

	// Create a grid
	vtkSmartPointer<vtkStructuredGrid> structuredGrid =
		vtkSmartPointer<vtkStructuredGrid>::New();

	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	unsigned int numi = spm.countX();
	unsigned int numj = spm.countY();
	unsigned int numk = 1;

	// for(unsigned int k = 0; k < numk; k++)
    {
		for(unsigned int j = 0; j < numj; j++)
		{
			for(unsigned int i = 0; i < numi; i++)
			{
				points->InsertPoint(i + j*numi,
									i,
									j,
									spm.heightAt(i, j));
			}
		}
    }

	// Specify the dimensions of the grid
	structuredGrid->SetDimensions(numi, numj, numk);
	structuredGrid->SetPoints(points);

	std::cout << "There are "
			  << structuredGrid->GetNumberOfPoints() << " points."
			  << std::endl;
	std::cout << "There are "
			  << structuredGrid->GetNumberOfCells() << " cells."
			  << std::endl;

	vtkSmartPointer<vtkStructuredGridGeometryFilter> sggFilter =
		vtkSmartPointer<vtkStructuredGridGeometryFilter>::New ();
	sggFilter->SetInput(structuredGrid);

	// lookup table
	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New ();
	QList<float> minMax = spm.minMax();
	lut->SetTableRange(minMax[0], minMax[1]);
	lut->SetHueRange(0.667, 0.);
	lut->SetRampToLinear();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sggFilter->GetOutputPort());
	mapper->SetLookupTable(lut);
	mapper->SetUseLookupTableScalarRange(1);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(0., 0., 0);
	renderer->AddActor(actor);

	 // Set up the lighting.    //
	{
		vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
		light->SetFocalPoint(1.875,0.6125,0);
		light->SetPosition(0.875,1.6125,400);
		// light->SetAmbientColor(1., 0., 0.);
		renderer->AddLight(light);
	}

	{
		vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
		light->SetFocalPoint(1.875,0.6125,0);
		light->SetPosition(0.875,1.6125,-400);
		// light->SetAmbientColor(1., 0., 0.);
		renderer->AddLight(light);
	}

	widget->GetRenderWindow()->AddRenderer(renderer);

	widget->resize(256,256);
	window.resize(256,256);
	window.setCentralWidget( widget );
	window.show();
	return app.exec();
}

int doSimpleQtDemo(CSpmData& spm, QApplication& app)
{
	QMainWindow window;
	QMenu* menu = window.menuBar()->addMenu("&File");
	menu->addAction("&Quit", &window, SLOT(close()));
	QVTKWidget* widget = new QVTKWidget;

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

	widget->GetRenderWindow()->AddRenderer(ren);

	widget->resize(256,256);
	window.resize(256,256);
	window.setCentralWidget(widget );
	window.show();
	return app.exec();
}


int doSurfaceFromUnorganizedPointsDemo(CSpmData& spm)
{
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	unsigned int numi = spm.countX();
	unsigned int numj = spm.countY();
	unsigned int numk = 1;

	for(unsigned int k = 0; k < numk; k++)
    {
		for(unsigned int j = 0; j < numj; j++)
		{
			for(unsigned int i = 0; i < numi; i++)
			{
				points->InsertNextPoint(i, j, spm.heightAt(i, j));
			}
		}
    }

	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	// Construct the surface and create isosurface.
	vtkSmartPointer<vtkSurfaceReconstructionFilter> surf =
		vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
#if VTK_MAJOR_VERSION <= 5
	surf->SetInput(polydata);
#else
	surf->SetInputData(polydata);
#endif

	vtkSmartPointer<vtkContourFilter> cf =
		vtkSmartPointer<vtkContourFilter>::New();
	cf->SetInputConnection(surf->GetOutputPort());
	cf->SetValue(0, 0.0);

	// Sometimes the contouring algorithm can create a volume whose gradient
	// vector and ordering of polygon (using the right hand rule) are
	// inconsistent. vtkReverseSense cures this problem.
	vtkSmartPointer<vtkReverseSense> reverse =
		vtkSmartPointer<vtkReverseSense>::New();
	reverse->SetInputConnection(cf->GetOutputPort());
	reverse->ReverseCellsOn();
	reverse->ReverseNormalsOn();

	vtkSmartPointer<vtkPolyDataMapper> map =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	map->SetInputConnection(reverse->GetOutputPort());
	map->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> surfaceActor =
		vtkSmartPointer<vtkActor>::New();
	surfaceActor->SetMapper(map);

	// Create the RenderWindow, Renderer and both Actors
	vtkSmartPointer<vtkRenderer> ren =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	// Add the actors to the renderer, set the background and size
	ren->AddActor(surfaceActor);
	ren->SetBackground(.2, .3, .4);

	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}
