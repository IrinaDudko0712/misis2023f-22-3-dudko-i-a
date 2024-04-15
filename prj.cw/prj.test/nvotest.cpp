#include <vtkSTLWriter.h>
#include <vtkSmartPointer.h>
#include <vtkMapper.h>
#include <vtkActor.h>
#include <vtkWindowToImageFilter.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPNGWriter.h>
#include <vtkTexture.h>
#include <vtkPNGReader.h>
#include <vtkInteractorStyleTrackballCamera.h>  
#include <visualization/visualization.hpp>
#include <iostream>
#include <string>
#include <nvolib/nvolib.hpp>
#include <data/data.hpp>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " opacity radius" << std::endl;
        return 1;
    }

    double color[3] = { 1.0, 0.0, 0.0 };
    double opacity = std::stod(argv[1]);
    double radius = std::stod(argv[2]);

    Visualization visualization;
    SphericalCoordinatesGenerator generator;


    vtkSmartPointer<vtkActor> sphereActor = visualization.createRealSphere(radius, color, opacity);

 
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
    stlWriter->SetFileName("sphere.stl");
    stlWriter->SetInputData(sphereActor->GetMapper()->GetInput());
    stlWriter->Write();

     
    STLCheck stlCheck;
    std::string stlFilename = "sphere.stl";
    if (stlCheck.isBinary_STL(stlFilename)) {
        std::cout << "The STL file is binary." << std::endl;
    }
    else {
        std::cout << "The STL file is ASCII." << std::endl;
    }

 
    NVO nvoSphere;
    nvoSphere.read_triangle_mesh("sphere.stl");
    nvoSphere.per_vertex_normals();
    nvoSphere.compute_normal_distribution_on_sphere(100);

 
    TextureDrawer textureDrawer;
    textureDrawer.drawNormalsAndSaveDrawing("spherical_normals.txt", "output_texture.png");

   
    std::vector<Point> normals = generator.readPointsFromFile("spherical_normals.txt");
    if (!normals.empty()) {
 
        vtkSmartPointer<vtkRenderer> textureRenderer = vtkSmartPointer<vtkRenderer>::New();
        vtkSmartPointer<vtkActor> texturedSphereActor = visualization.Mapping("output_texture.png", radius, color, opacity);
        textureRenderer->AddActor(texturedSphereActor);

         
        vtkSmartPointer<vtkRenderWindow> textureRenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
        textureRenderWindow->SetWindowName("Texture Visualization");
        textureRenderWindow->SetSize(800, 800);
        textureRenderWindow->AddRenderer(textureRenderer);

 
        vtkSmartPointer<vtkRenderWindowInteractor> textureInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        vtkSmartPointer<vtkInteractorStyleTrackballCamera> textureStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        textureInteractor->SetInteractorStyle(textureStyle);
        textureInteractor->SetRenderWindow(textureRenderWindow);

 
        vtkSmartPointer<vtkRenderer> normalRenderer = vtkSmartPointer<vtkRenderer>::New();
        vtkSmartPointer<vtkActor> normalSphereActor = visualization.generateSphereWithPoints(normals, opacity, color, radius);
        normalRenderer->AddActor(normalSphereActor);

 
        vtkSmartPointer<vtkRenderWindow> normalRenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
        normalRenderWindow->SetWindowName("Normals Visualization");
        normalRenderWindow->SetSize(800, 800);
        normalRenderWindow->AddRenderer(normalRenderer);

         
        vtkSmartPointer<vtkRenderWindowInteractor> normalInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        vtkSmartPointer<vtkInteractorStyleTrackballCamera> normalStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        normalInteractor->SetInteractorStyle(normalStyle);
        normalInteractor->SetRenderWindow(normalRenderWindow);

  
        for (int i = 0; i < 6; ++i) {
   
            vtkSmartPointer<vtkCamera> textureCamera = vtkSmartPointer<vtkCamera>::New();
            textureCamera->SetPosition(0, 0, 5);
            textureCamera->SetFocalPoint(0, 0, 0);
            textureCamera->Azimuth(20 * i);
            textureCamera->Elevation(10 * i);
            textureRenderer->SetActiveCamera(textureCamera);
            textureRenderer->SetBackground(1.0, 1.0, 1.0);
            textureRenderWindow->Render();

 
            vtkSmartPointer<vtkWindowToImageFilter> textureWindowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
            textureWindowToImageFilter->SetInput(textureRenderWindow);
            textureWindowToImageFilter->Update();
            vtkSmartPointer<vtkPNGWriter> textureWriter = vtkSmartPointer<vtkPNGWriter>::New();
            textureWriter->SetFileName(("output_texture_visualization" + std::to_string(i) + ".png").c_str());
            textureWriter->SetInputConnection(textureWindowToImageFilter->GetOutputPort());
            textureWriter->Write();

 
            vtkSmartPointer<vtkCamera> normalCamera = vtkSmartPointer<vtkCamera>::New();
            normalCamera->SetPosition(0, 0, 5);
            normalCamera->SetFocalPoint(0, 0, 0);
            normalCamera->Azimuth(20 * i);
            normalCamera->Elevation(10 * i);
            normalRenderer->SetActiveCamera(normalCamera);
            normalRenderer->SetBackground(1.0, 1.0, 1.0);
            normalRenderWindow->Render();

  
            vtkSmartPointer<vtkWindowToImageFilter> normalWindowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
            normalWindowToImageFilter->SetInput(normalRenderWindow);
            normalWindowToImageFilter->Update();
            vtkSmartPointer<vtkPNGWriter> normalWriter = vtkSmartPointer<vtkPNGWriter>::New();
            normalWriter->SetFileName(("output_normals_visualization" + std::to_string(i) + ".png").c_str());
            normalWriter->SetInputConnection(normalWindowToImageFilter->GetOutputPort());
            normalWriter->Write();
        }

 
        textureInteractor->Start();
        normalInteractor->Start();
    }
    else {
        std::cerr << "Failed to read normals from file." << std::endl;
        return 1;
    }

    return 0;
}
