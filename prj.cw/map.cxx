#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPNGReader.h>
#include <vtkTexture.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkCamera.h> 
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>


int main() {
    // Создаем сферу
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetThetaResolution(100);
    sphere->SetPhiResolution(50);

    // Создаем маппер
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort());

    // Создаем актер
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Задаем текстурные координаты
    sphere->Update();
    vtkPoints* points = sphere->GetOutput()->GetPoints();
    vtkSmartPointer<vtkFloatArray> textureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
    textureCoordinates->SetNumberOfComponents(2);

    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double coord[3];
        points->GetPoint(i, coord);
        double phi = atan2(coord[1], coord[0]);
        double theta = acos(coord[2] / sphere->GetRadius());

        double s = static_cast<double>(phi + vtkMath::Pi()) / (2.0 * vtkMath::Pi());
        double t = static_cast<double>(theta) / vtkMath::Pi();

        textureCoordinates->InsertNextTuple2(s, t);
    }

    sphere->GetOutput()->GetPointData()->SetTCoords(textureCoordinates);

    // Создаем текстурный объект и читаем изображение в формате PNG
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName("C:/vsphotos/stars.png");  // Указываем путь к файлу PNG
    texture->SetInputConnection(reader->GetOutputPort());

    // Применяем текстуру к актеру
    actor->SetTexture(texture);

    // Создаем рендерер
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1.0, 1.0, 1.0);  // белый фон

    // Добавляем актер в рендерер
    renderer->AddActor(actor);

    // Создаем окно для визуализации
    vtkSmartPointer<vtkRenderWindow> render_window = vtkSmartPointer<vtkRenderWindow>::New();
    render_window->SetWindowName("Texture Mapping");
    render_window->SetSize(800, 500);
    render_window->AddRenderer(renderer);

    // Создаем интерактор
    vtkSmartPointer<vtkRenderWindowInteractor> render_window_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    render_window_interactor->SetRenderWindow(render_window);

    // Устанавливаем камеру
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);

    // Запускаем рендеринг
    render_window->Render();

    // Сохраняем результат в файл в формате PNG
    vtkSmartPointer<vtkWindowToImageFilter> render_window_to_image_filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
    render_window_to_image_filter->SetInput(render_window);
    render_window_to_image_filter->Update();

    vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("output.png");
    writer->SetInputConnection(render_window_to_image_filter->GetOutputPort());
    writer->Write();

    // Запускаем интерактор
    render_window_interactor->Start();

    return 0;
}
