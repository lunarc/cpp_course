#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>
#include <vtkTransform.h>
#include <vtkUnstructuredGrid.h>

#include <array>

int main(int, char*[])
{
    vtkNew<vtkNamedColors> colors;

    // Set the background color.
    std::array<unsigned char, 4> bkg { { 26, 51, 102, 255 } };
    colors->SetColor("BkgColor", bkg.data());

    // This creates a polygonal cylinder model with eight circumferential facets
    // (i.e, in practice an octagonal prism).
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes are
    // defined.
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it around the X and Y axes.
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(
        colors->GetColor4d("Tomato").GetData());
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    vtkNew<vtkTransform> transform;
    transform->Translate(1.0, 0.0, 0.0);

    vtkNew<vtkAxesActor> axes;

    // The axes are positioned with a user transform
    axes->SetUserTransform(transform);

    vtkNew<vtkActor> dataActor;
    vtkNew<vtkDataSetMapper> dataSetMapper;

    // Get all data from the file.
    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName("dcinv.result_0.vtk");
    reader->Update();

    // All of the standard data types can be checked and obtained like this:
    if (reader->IsFilePolyData())
    {
        std::cout << "output is polydata," << std::endl;
        auto output = reader->GetPolyDataOutput();
        std::cout << "   output has " << output->GetNumberOfPoints() << " points."
                  << std::endl;
    }

    if (reader->IsFileUnstructuredGrid())
    {
        std::cout << "output is unstructured grid," << std::endl;
        auto output = reader->GetUnstructuredGridOutput();
        std::cout << "   output has " << output->GetNumberOfPoints() << " points."
                  << std::endl;

        dataSetMapper->SetInputData(output);
        dataActor->SetMapper(dataSetMapper);
    }

    if (reader->IsFileStructuredGrid())
    {
        std::cout << "output is structured grid," << std::endl;
        auto output = reader->GetStructuredGridOutput();
        std::cout << "   output has " << output->GetNumberOfPoints() << " points."
                  << std::endl;
    }

    // The renderer generates the image
    // which is then displayed on the render window.
    // It can be thought of as a scene to which the actor is added
    vtkNew<vtkRenderer> renderer;
    // renderer->AddActor(cylinderActor);
    // renderer->AddActor(axes);
    renderer->AddActor(dataActor);
    renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    // Zoom in a little by accessing the camera and invoking its "Zoom" method.
    renderer->ResetCamera();
    // renderer->GetActiveCamera()->Zoom(1.5);
    renderer->GetActiveCamera()->SetParallelProjection(false);

    // The render window is the actual GUI window
    // that appears on the computer screen
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetSize(300, 300);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("Cylinder");

    // The render window interactor captures mouse events
    // and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // This starts the event loop and as a side effect causes an initial render.
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
