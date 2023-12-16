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
#include <vtkLookupTable.h>

#include <array>

int main(int, char*[])
{
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkLookupTable> lut;
    lut->Build();

    // Set the background color.
    std::array<unsigned char, 4> bkg { { 26, 51, 102, 255 } };
    colors->SetColor("BkgColor", bkg.data());


    vtkNew<vtkActor> dataActor;
    vtkNew<vtkDataSetMapper> dataSetMapper;

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
        dataSetMapper->SelectColorArray("Resistivity(log10)");
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
