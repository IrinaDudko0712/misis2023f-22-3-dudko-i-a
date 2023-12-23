#include <visualization/visualization.hpp>
#include <iostream>
#include <string>
#include <nvolib/nvolib.hpp>

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " red green blue opacity radius" << std::endl;
        return 1;
    }

    double color[3];
    for (int i = 0; i < 3; ++i) {
        color[i] = std::stod(argv[i + 1]);
    }

    double opacity = std::stod(argv[4]);
    double radius = std::stod(argv[5]);
    Visualization visualization;

    vtkSmartPointer<vtkActor> sphereActor = visualization.createSphere(radius, color, opacity);

    // Обычное сохранение в STL
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
    stlWriter->SetFileName("sphere.stl");
    stlWriter->SetInputData(sphereActor->GetMapper()->GetInput());
    stlWriter->Write();

    // Проверяем, является ли файл бинарным STL
    STLCheck stlCheck;
    std::string stlFilename = "sphere.stl";
    if (stlCheck.isBinary_STL(stlFilename)) {
        std::cout << "The STL file is binary." << std::endl;
    }
    else {
        std::cout << "The STL file is ASCII." << std::endl;
    }

    // Вычисляем нормали и сохраняем их в файл
    NVO nvoSphere;
    nvoSphere.read_triangle_mesh("sphere.stl");
    nvoSphere.per_vertex_normals();
    nvoSphere.compute_normal_distribution_on_sphere(100);

    // Создаем текстуру на основе файла с нормалями и сохраняем ее
    TextureDrawer textureDrawer;
    textureDrawer.drawNormalsAndSaveDrawing("spherical_normals.txt", "output_texture.png");
    // Визуализируем сферу с текстурой
    vtkSmartPointer<vtkActor> texturedSphereActor = visualization.Mapping("output_texture.png", "sphere.stl");

    // Создаем рендерер
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.0, 0.0, 0.0);  // черный фон

    // Добавляем актер в рендерер
    renderer->AddActor(texturedSphereActor);

    // Создаем окно для визуализации
    vtkSmartPointer<vtkRenderWindow> render_window = vtkSmartPointer<vtkRenderWindow>::New();
    render_window->SetWindowName("Rendered Sphere");
    render_window->SetSize(400, 400);
    render_window->AddRenderer(renderer);

    // Создаем интерактор
    vtkSmartPointer<vtkRenderWindowInteractor> render_window_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    render_window_interactor->SetRenderWindow(render_window);

    // Запускаем интерактор
    render_window_interactor->Start();

    return 0;
}


