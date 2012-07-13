#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QToolBar>
#include <QVTKWidget.h>

#include <vld.h>
#include <vtkActor.h>
#include <vtkAssemblyPath.h>
#include <vtkCamera.h>
#include <vtkCell.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkContourFilter.h>
#include <vtkCornerAnnotation.h>
#include <vtkCursor3D.h>
#include <vtkDataArray.h>
#include <vtkDataSetMapper.h>
#include <vtkElevationFilter.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProgrammableSource.h>
#include <vtkPropPicker.h>
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
#include <vtkTextProperty.h>
#include <vtkVersion.h>

// The mouse motion callback, to pick the image and recover pixel values
class vtkImageInteractionCallback1 : public vtkCommand
{
public:

	static vtkImageInteractionCallback1 *New()
    {
		return new vtkImageInteractionCallback1;
    }

	vtkImageInteractionCallback1()
    {
		this->Viewer = 0;
		this->Picker = 0;
		this->Annotation = 0;
		this->PointData = vtkPointData::New();
    }

	~vtkImageInteractionCallback1()
	{
		this->Viewer = 0;
		this->Picker = 0;
		this->Annotation = 0;
		this->PointData->Delete();
	}

	void SetPicker(vtkPropPicker *picker)
    {
		this->Picker = picker;
    }

	void SetAnnotation(vtkCornerAnnotation *annotation)
    {
		this->Annotation = annotation;
    }

	void SetViewer(vtkImageViewer2 *viewer)
    {
		this->Viewer = viewer;
    }

    virtual void Execute(vtkObject *, unsigned long vtkNotUsed(event), void *)
	{
		//this->Viewer;
		vtkRenderWindowInteractor *interactor =
			this->Viewer->GetRenderWindow()->GetInteractor();
		vtkRenderer* renderer = this->Viewer->GetRenderer();
		vtkImageActor* actor = this->Viewer->GetImageActor();
		vtkImageData* image = this->Viewer->GetInput();
		vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
				interactor->GetInteractorStyle());

#if VTK_MAJOR_VERSION <= 5
		image->Update();
#endif

		// Pick at the mouse location provided by the interactor
		this->Picker->Pick( interactor->GetEventPosition()[0],
							interactor->GetEventPosition()[1],
							0.0, renderer );

		// There could be other props assigned to this picker, so
		// make sure we picked the image actor
		vtkAssemblyPath* path = this->Picker->GetPath();
		bool validPick = false;

		if( path )
        {
			vtkCollectionSimpleIterator sit;
			path->InitTraversal( sit );
			vtkAssemblyNode *node;
			for( int i = 0; i < path->GetNumberOfItems() && !validPick; ++i )
			{
				node = path->GetNextNode( sit );
				if( actor == vtkImageActor::SafeDownCast( node->GetViewProp() ) )
				{
					validPick = true;
				}
			}
        }

		if( !validPick )
        {
			this->Annotation->SetText( 0, "Off Image" );
			interactor->Render();
			// Pass the event further on
			style->OnMouseMove();
			return;
        }

		// Get the world coordinates of the pick
		double pos[3];
		this->Picker->GetPickPosition( pos );
		// Fixes some numerical problems with the picking
		double *bounds = actor->GetDisplayBounds();
		int axis = this->Viewer->GetSliceOrientation();
		pos[axis] = bounds[2*axis];

		vtkPointData* pd = image->GetPointData();
		if( !pd )
        {
			return;
        }

		this->PointData->InterpolateAllocate( pd, 1, 1 );

		// Use tolerance as a function of size of source data
		double tol2 = image->GetLength();
		tol2 = tol2 ? tol2*tol2 / 1000.0 : 0.001;

		// Find the cell that contains pos
		int subId;
		double pcoords[3], weights[8];
		vtkCell* cell = image->FindAndGetCell(
				pos, NULL, -1, tol2, subId, pcoords, weights );
		if( cell )
        {
			// Interpolate the point data
			this->PointData->InterpolatePoint( pd, 0, cell->PointIds, weights );
			int components =
				this->PointData->GetScalars()->GetNumberOfComponents();
			double* tuple = this->PointData->GetScalars()->GetTuple( 0 );

			std::string message = "Location: ( ";
			message += vtkVariant( pos[0] ).ToString();
			message += ", ";
			message += vtkVariant( pos[1] ).ToString();
			message += ", ";
			message += vtkVariant( pos[2] ).ToString();
			message += " )\nValue: ( ";

			for( int c = 0; c < components; ++c )
			{
				message += vtkVariant( tuple[ c ] ).ToString();
				if( c != components - 1 )
				{
					message += ", ";
				}
			}
			message += " )";
			this->Annotation->SetText( 0, message.c_str() );
			interactor->Render();
			style->OnMouseMove();
        }
    }

private:

	// Pointer to the viewer
	vtkImageViewer2 *Viewer;

	// Pointer to the picker
	vtkPropPicker *Picker;

	// Pointer to the annotation
	vtkCornerAnnotation *Annotation;

	// Interpolator
	vtkPointData* PointData;
};

int main ( int argc, char* argv[] )
{
	std::string inputFilename;

	//Verify input arguments
	if ( argc != 2 )
    {
		// std::cout << "Usage: " << argv[0]
		// 		  << " Filename(jpeg)" << std::endl;
		// return EXIT_FAILURE;
		inputFilename = "e:/prj/study/opencv/image/chariot.jpg";
    } else {
		//Parse input argument
		inputFilename= argv[1];
	}

	//Read the image
	vtkSmartPointer<vtkJPEGReader> jpegReader =
		vtkSmartPointer<vtkJPEGReader>::New();
	if( !jpegReader->CanReadFile( inputFilename.c_str() ) )
    {
		std::cout << argv[0] << ": Error reading file "
				  << inputFilename << endl << "Exiting..." << endl;
		return EXIT_FAILURE;
    }
	jpegReader->SetFileName ( inputFilename.c_str() );

	// Picker to pick pixels
	vtkSmartPointer<vtkPropPicker> propPicker =
		vtkSmartPointer<vtkPropPicker>::New();
	propPicker->PickFromListOn();

	// Give the picker a prop to pick
	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	propPicker->AddPickList( imageViewer->GetImageActor() );

	// Visualize
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetInputConnection( jpegReader->GetOutputPort() );
	imageViewer->SetupInteractor( renderWindowInteractor );
	imageViewer->SetSize( 600, 600 );

	vtkRenderer* renderer = imageViewer->GetRenderer();
	renderer->ResetCamera();
	renderer->GradientBackgroundOn();
	renderer->SetBackground(0,0,0);
	renderer->SetBackground2(1,1,1);

	// Annotate the image with window/level and mouse over pixel information
	vtkSmartPointer<vtkCornerAnnotation> cornerAnnotation =
		vtkSmartPointer<vtkCornerAnnotation>::New();
	cornerAnnotation->SetLinearFontScaleFactor( 2 );
	cornerAnnotation->SetNonlinearFontScaleFactor( 1 );
	cornerAnnotation->SetMaximumFontSize( 20 );
	cornerAnnotation->SetText( 0, "Off Image" );
	cornerAnnotation->SetText( 3, "<window>\n<level>" );
	cornerAnnotation->GetTextProperty()->SetColor( 1,0,0);

	imageViewer->GetRenderer()->AddViewProp( cornerAnnotation );

	// Callback listens to MouseMoveEvents invoked by the interactor's style
	vtkSmartPointer<vtkImageInteractionCallback1> callback =
		vtkSmartPointer<vtkImageInteractionCallback1>::New();
	callback->SetViewer( imageViewer );
	callback->SetAnnotation( cornerAnnotation );
	callback->SetPicker( propPicker );

	// InteractorStyleImage allows for the following controls:
	// 1) middle mouse + move = camera pan
	// 2) left mouse + move = window/level
	// 3) right mouse + move = camera zoom
	// 4) middle mouse wheel scroll = zoom
	// 5) 'r' = reset window/level
	// 6) shift + 'r' = reset camera
	vtkInteractorStyleImage* imageStyle = imageViewer->GetInteractorStyle();
	imageStyle->AddObserver( vtkCommand::MouseMoveEvent, callback );

	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

#ifdef PLEASE_USE_QT
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("spm_tool");

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
}
#endif
