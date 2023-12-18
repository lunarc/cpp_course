#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

#include <vtkActor.h>
#include <vtkAssembly.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkClipDataSet.h>
#include <vtkClipPolyData.h>
#include <vtkCubeAxesActor.h>
#include <vtkCylinderSource.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkLegendScaleActor.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkScalarBarActor.h>
#include <vtkShaderProperty.h>
#include <vtkStructuredGrid.h>
#include <vtkTextProperty.h>
#include <vtkTransform.h>
#include <vtkUnstructuredGrid.h>

#include <array>

vtkSmartPointer<vtkUnstructuredGrid> loadModel(const std::string filename)
{
    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName(filename.c_str());
    reader->Update();

    if (reader->IsFileUnstructuredGrid())
    {
        std::cout << "output is unstructured grid," << std::endl;
        auto model = reader->GetUnstructuredGridOutput();
        std::cout << "   output has " << model->GetNumberOfPoints() << " points."
                  << std::endl;

        return model;
    }
    return nullptr;
}

vtkSmartPointer<vtkActor> createFullModelActor(vtkSmartPointer<vtkUnstructuredGrid> model, vtkLookupTable* lut)
{
    auto dataActor = vtkSmartPointer<vtkActor>::New();
    auto dataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();

    dataSetMapper->SetInputData(model);
    dataSetMapper->SelectColorArray("Resistivity(log10)");
    dataSetMapper->ScalarVisibilityOn();
    dataSetMapper->SetLookupTable(lut);
    // dataSetMapper->SetScalarRange(model->GetScalarRange());
    dataSetMapper->SetScalarRange(2.0, 3.0);

    dataActor->SetMapper(dataSetMapper);
    dataActor->GetProperty()->SetOpacity(0.3);
    dataActor->SetOrientation(-90.0, 0.0, 0.0);

    return dataActor;
}

vtkSmartPointer<vtkActor> createClippedModelActor(vtkSmartPointer<vtkUnstructuredGrid> model, vtkLookupTable* lut)
{
    auto plane = vtkSmartPointer<vtkPlane>::New();
    plane->SetOrigin(model->GetCenter());
    plane->SetNormal(-1.0, 0.0, 0.0);

    auto clipper = vtkSmartPointer<vtkClipDataSet>::New();
    clipper->SetClipFunction(plane);
    clipper->SetInputData(model);
    clipper->SetValue(0.0);
    clipper->GenerateClippedOutputOn();
    clipper->Update();

    auto clipMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    clipMapper->SelectColorArray("Resistivity(log10)");
    clipMapper->ScalarVisibilityOn();
    clipMapper->SetLookupTable(lut);
    // clipMapper->SetScalarRange(model->GetScalarRange());
    clipMapper->SetScalarRange(2.0, 3.0);
    clipMapper->SetInputData(clipper->GetOutput());

    auto clipActor = vtkSmartPointer<vtkActor>::New();
    clipActor->SetMapper(clipMapper);
    clipActor->SetOrientation(-90.0, 0.0, 0.0);

    return clipActor;
}

std::vector<std::string> findVTKFiles()
{
    std::vector<std::string> file_list;

    for (const auto& entry : fs::directory_iterator(".\\data"))
        file_list.push_back(entry.path().string());

    return file_list;
}

int main(int, char*[])
{
    vtkNew<vtkNamedColors> colors;

    // Create a lookup table

    vtkNew<vtkLookupTable> lut;
    lut->SetNumberOfColors(256);
    lut->SetHueRange(0.667, 0.0);
    lut->Build();

    // Set the background color.

    std::array<unsigned char, 4> bkg { { 26, 51, 102, 255 } };
    colors->SetColor("BkgColor", bkg.data());

    // Load models and create actors.

    vtkNew<vtkAssembly> assembly;

    auto file_list = findVTKFiles();

    auto count = 0;

    for (auto& filename : file_list)
    {
        std::cout << "Loading: " << filename << std::endl;
        auto model = loadModel(filename);
        auto modelActor = createFullModelActor(model, lut);
        auto clippedActor = createClippedModelActor(model, lut);

        assembly->AddPart(modelActor);
        assembly->AddPart(clippedActor);

        if (count == 1)
            break;
        count++;
    }

    /*
    auto model = loadModel("dcinv.result_0.vtk");
    auto modelActor = createFullModelActor(model, lut);
    auto clippedActor = createClippedModelActor(model, lut);
    */

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

    vtkNew<vtkCubeAxesActor> cubeAxesActor;
    cubeAxesActor->SetUseTextActor3D(1);
    cubeAxesActor->SetBounds(assembly->GetBounds());
    // cubeAxesActor->SetOrientation(90.0, 0.0, 0.0);

    cubeAxesActor->DrawXGridlinesOn();
    cubeAxesActor->DrawYGridlinesOn();
    cubeAxesActor->DrawZGridlinesOn();
    cubeAxesActor->SetGridLineLocation(cubeAxesActor->VTK_GRID_LINES_FURTHEST);

    vtkNew<vtkRenderer> renderer;

    cubeAxesActor->SetCamera(renderer->GetActiveCamera());

    renderer->AddActor(assembly);
    renderer->AddActor(cubeAxesActor);
    renderer->AddActor2D(scalarBar);

    renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    renderer->ResetCamera();
    renderer->GetActiveCamera()->SetParallelProjection(false);

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetSize(800, 800);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("VTK Example");

    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
