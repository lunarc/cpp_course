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
#include <vtkScalarBarActor.h>
#include <vtkLegendScaleActor.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextProperty.h>
#include <vtkPlane.h>
#include <vtkClipPolyData.h>
#include <vtkClipDataSet.h>
#include <vtkShaderProperty.h>

#include <array>

vtkSmartPointer<vtkActor> loadModel(const std::string filename, vtkLookupTable* lut)
{
    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName(filename.c_str());
    reader->Update();

    auto dataActor = vtkSmartPointer<vtkActor>::New();
    auto dataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();

    if (reader->IsFileUnstructuredGrid())
    {
        std::cout << "output is unstructured grid," << std::endl;
        auto model = reader->GetUnstructuredGridOutput();
        std::cout << "   output has " << model->GetNumberOfPoints() << " points."
            << std::endl;

        dataSetMapper->SetInputData(model);
        dataSetMapper->SelectColorArray("Resistivity(log10)");
        dataSetMapper->ScalarVisibilityOn();
        dataSetMapper->SetLookupTable(lut);
        dataSetMapper->SetScalarRange(model->GetScalarRange());

        dataActor->SetMapper(dataSetMapper);

        return dataActor;
    }
    return nullptr;
}

int main(int, char*[])
{
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkLookupTable> lut;
    lut->SetNumberOfColors(256);
    lut->SetHueRange(0.667, 0.0);
    lut->Build();

    // Set the background color.
    std::array<unsigned char, 4> bkg { { 26, 51, 102, 255 } };
    colors->SetColor("BkgColor", bkg.data());

    vtkNew<vtkActor> dataActor;
    vtkNew<vtkDataSetMapper> dataSetMapper;

    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName("dcinv.result_0.vtk");
    reader->Update();

    vtkUnstructuredGrid* model = nullptr;

    if (reader->IsFileUnstructuredGrid())
    {
        std::cout << "output is unstructured grid," << std::endl;
        model = reader->GetUnstructuredGridOutput();
        std::cout << "   output has " << model->GetNumberOfPoints() << " points."
                  << std::endl;

        dataSetMapper->SetInputData(model);
        dataSetMapper->SelectColorArray("Resistivity(log10)");
        dataSetMapper->ScalarVisibilityOn();
        dataSetMapper->SetLookupTable(lut);
        dataSetMapper->SetScalarRange(model->GetScalarRange());

        dataActor->SetMapper(dataSetMapper);
        dataActor->GetProperty()->SetOpacity(0.2);
    }

    if (model == nullptr)
        return -1;

    vtkNew<vtkPlane> plane;
    plane->SetOrigin(dataActor->GetMapper()->GetInput()->GetCenter());
    //plane->SetOrigin(model->GetCenter());
    plane->SetNormal(0.0, -1.0, 0.0);

    vtkNew<vtkClipDataSet> clipper;
    clipper->SetClipFunction(plane);
    clipper->SetInputData(model);
    clipper->SetValue(0.0);
    clipper->GenerateClippedOutputOn();
    clipper->Update();

    vtkNew<vtkDataSetMapper> clipMapper;
    clipMapper->SelectColorArray("Resistivity(log10)");
    clipMapper->ScalarVisibilityOn();
    clipMapper->SetLookupTable(lut);
    clipMapper->SetScalarRange(model->GetScalarRange());
    clipMapper->SetInputData(clipper->GetOutput());

    vtkNew<vtkActor> clipActor;
    clipActor->SetMapper(clipMapper);

    vtkNew<vtkScalarBarActor> scalarBar;
    scalarBar->SetLookupTable(lut);
    scalarBar->SetTitle("Res. log10");
    scalarBar->AnnotationTextScalingOff();
    scalarBar->SetNumberOfLabels(5);
    scalarBar->SetHeight(0.75);
    scalarBar->SetWidth(0.4);
    scalarBar->DrawColorBarOn();
    scalarBar->SetFixedAnnotationLeaderLineColor(true);
    scalarBar->SetMaximumWidthInPixels(80);
    scalarBar->AnnotationTextScalingOn();
    scalarBar->UnconstrainedFontSizeOff();
    scalarBar->SetOrientationToVertical();




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

    vtkNew<vtkCubeAxesActor> cubeAxesActor;
    cubeAxesActor->SetUseTextActor3D(1);
    cubeAxesActor->SetBounds(dataSetMapper->GetBounds());
    cubeAxesActor->SetCamera(renderer->GetActiveCamera());
    //cubeAxesActor->GetTitleTextProperty(0)->SetColor(axis1Color.GetData());
    //cubeAxesActor->GetTitleTextProperty(0)->SetFontSize(48);
    //cubeAxesActor->GetLabelTextProperty(0)->SetColor(axis1Color.GetData());

    //cubeAxesActor->GetTitleTextProperty(1)->SetColor(axis2Color.GetData());
    //cubeAxesActor->GetLabelTextProperty(1)->SetColor(axis2Color.GetData());

    //cubeAxesActor->GetTitleTextProperty(2)->SetColor(axis3Color.GetData());
    //cubeAxesActor->GetLabelTextProperty(2)->SetColor(axis3Color.GetData());

    cubeAxesActor->DrawXGridlinesOn();
    cubeAxesActor->DrawYGridlinesOn();
    cubeAxesActor->DrawZGridlinesOn();
    cubeAxesActor->SetGridLineLocation(cubeAxesActor->VTK_GRID_LINES_FURTHEST);

    renderer->AddActor(cubeAxesActor);


    renderer->AddActor(clipActor);
    renderer->AddActor(dataActor);
    renderer->AddActor2D(scalarBar);


    renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    // Zoom in a little by accessing the camera and invoking its "Zoom" method.
    renderer->ResetCamera();
    // renderer->GetActiveCamera()->Zoom(1.5);
    renderer->GetActiveCamera()->SetParallelProjection(false);

    // The render window is the actual GUI window
    // that appears on the computer screen
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetSize(800, 800);
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
