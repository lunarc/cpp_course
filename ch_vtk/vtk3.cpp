#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

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
#include <vtkCallbackCommand.h>
#include <vtkProp3DCollection.h>
#include <vtkColorSeries.h>


class TimerCallback : public vtkCallbackCommand
{
public:
    TimerCallback() = default;

    static TimerCallback *New()
    {
        TimerCallback *cb = new TimerCallback;
        cb->m_timerCount = 0;
        return cb;
    }

    virtual void Execute(vtkObject *caller, unsigned long eventId, void *vtkNotUsed(callData))
    {
        if (vtkCommand::TimerEvent == eventId)
        {
            ++this->m_timerCount;
        }

        auto models = modelAssembly->GetParts();
        auto clippedModels = clippedAssembly->GetParts();

        models->InitTraversal();
        clippedModels->InitTraversal();
        for (auto i=0; i<models->GetNumberOfItems(); i++)
        {
            auto currentModel = models->GetNextProp();
            auto currentClippedModel = clippedModels->GetNextProp();

            if (i == m_currentStep)
            {
                currentModel->VisibilityOn();
                currentClippedModel->VisibilityOn();
            }
            else
            {
                currentModel->VisibilityOff();
                currentClippedModel->VisibilityOff();
            }
        }
        m_currentStep++;
        
        if (m_currentStep == models->GetNumberOfItems())
            m_currentStep = 0;

        //actor->SetPosition(this->m_timerCount, this->m_timerCount, 0);        
        
        if (this->m_timerCount < this->maxCount)
        {
            vtkRenderWindowInteractor *iren =
                dynamic_cast<vtkRenderWindowInteractor *>(caller);
            iren->GetRenderWindow()->Render();
        }
        else
        {
            vtkRenderWindowInteractor *iren =
                dynamic_cast<vtkRenderWindowInteractor *>(caller);
            if (this->timerId > -1)
            {
                iren->DestroyTimer(this->timerId);
            }
        }
    }

private:
    int m_timerCount = 0;
    int m_currentStep = 0;
public:
    vtkAssembly* modelAssembly = nullptr;
    vtkAssembly* clippedAssembly = nullptr;
    int timerId = 0;
    int maxCount = -1;
};

vtkSmartPointer<vtkUnstructuredGrid>
loadModel(const std::string filename)
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

vtkSmartPointer<vtkActor> createFullModelActor(vtkSmartPointer<vtkUnstructuredGrid> model, vtkLookupTable *lut)
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

vtkSmartPointer<vtkActor> createClippedModelActor(vtkSmartPointer<vtkUnstructuredGrid> model, vtkLookupTable *lut)
{
    auto plane = vtkSmartPointer<vtkPlane>::New();
    plane->SetOrigin(model->GetCenter());
    plane->SetNormal(0.0, -1.0, 0.0);

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

    for (const auto &entry : fs::directory_iterator("./data"))
        file_list.push_back(entry.path().string());

    std::ranges::sort(file_list, [](const std::string& a, const std::string& b) 
    {
        size_t pos1 = a.find_last_of('_');
        int num1 = std::stoi(a.substr(pos1 + 1));
        size_t pos2 = b.find_last_of('_');
        int num2 = std::stoi(b.substr(pos2 + 1));
        
        return num1 < num2;
    });

    return file_list;
}

int main(int, char *[])
{
    vtkNew<vtkNamedColors> colors;

    // Create a lookup table

    vtkNew<vtkColorSeries> colorSeries;
    //colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_SPECTRAL_11);
    colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_PURPLE_ORANGE_11);
    

    vtkNew<vtkLookupTable> lut;
    lut->SetNumberOfColors(256);
    colorSeries->BuildLookupTable(lut, vtkColorSeries::ORDINAL);

    /*
    vtkNew<vtkLookupTable> lut;
    lut->SetNumberOfColors(256);
    lut->SetHueRange(0.667, 0.0);
    lut->Build();
    */

    // Set the background color.

    std::array<unsigned char, 4> bkg{{26, 51, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

    // Load models and create actors.

    vtkNew<vtkAssembly> fullModelAssembly;
    vtkNew<vtkAssembly> clippedModelAssembly;

    auto file_list = findVTKFiles();

    auto count = 0;

    for (auto &filename : file_list)
    {
        std::cout << "Loading: " << filename << std::endl;
        auto model = loadModel(filename);

        auto modelActor = createFullModelActor(model, lut);
        auto clippedActor = createClippedModelActor(model, lut);

        fullModelAssembly->AddPart(modelActor);
        clippedModelAssembly->AddPart(clippedActor);

        if (count == 10)
            break;
        count++;
    }

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
    cubeAxesActor->SetBounds(fullModelAssembly->GetBounds());
    // cubeAxesActor->SetOrientation(90.0, 0.0, 0.0);

    cubeAxesActor->DrawXGridlinesOn();
    cubeAxesActor->DrawYGridlinesOn();
    cubeAxesActor->DrawZGridlinesOn();
    cubeAxesActor->SetGridLineLocation(cubeAxesActor->VTK_GRID_LINES_FURTHEST);

    vtkNew<vtkRenderer> renderer;

    cubeAxesActor->SetCamera(renderer->GetActiveCamera());

    renderer->AddActor(fullModelAssembly);
    renderer->AddActor(clippedModelAssembly);
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
    renderWindowInteractor->Initialize();

    vtkNew<TimerCallback> cb;
    cb->modelAssembly = fullModelAssembly;
    cb->clippedAssembly = clippedModelAssembly;
    renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, cb);
    int timerId = renderWindowInteractor->CreateRepeatingTimer(200);
    cb->maxCount = 1000000;
    cb->timerId = timerId;

    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
