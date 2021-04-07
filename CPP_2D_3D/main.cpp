#include <iostream>
#include "window.h"

Window *brownian;
//std::vector<Sphere> allSpheres;

void display()
{
    brownian->display();
    //brownian->draw_spheres2D(allSpheres);
}

void display3D()
{
    brownian->display3D();
    //brownian->draw_spheres3D(allSpheres);
}

void reshape(int w, int h)
{
    brownian->reshape(w,h);
}


int main(int argc, char *argv[]) 
{
    int is3D;
    int numSpheres;
    // Take User Input
    std::cout << "Simulate 3D (1) or 2D (0) ?" << std::endl;
    std::cin >> is3D;
    std::cout << "Enter number of particles in the system:" << std::endl;
    std::cin >> numSpheres;
    // Initialize window and openGL
    glutInit(&argc, argv);
    brownian = new Window(is3D);
    // Initialize particles
    brownian->generate_spheres(numSpheres);
    
    glutReshapeFunc(reshape);
    if (is3D) {
        glutDisplayFunc(display3D);
        glutIdleFunc(display3D);       
    }
    else {
        glutDisplayFunc(display);
        glutIdleFunc(display);
    }                    
    glutMainLoop();  
    // Add deconstructors here 
    return 0;
}