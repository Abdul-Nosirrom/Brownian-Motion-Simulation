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

void buttons(int selection)
{
    switch(selection) {
        case 1:
            brownian->set_temperature();
            break;
        case 2:
            brownian->showParticles = false;
            break;
        case 3:
            brownian->showParticles = true;
            break;
        case 4:
            brownian->~Window();
            break;
    }
}
int main(int argc, char *argv[]) 
{
    INITIALIZE:
    int is3D;
    long unsigned int numSpheres;
    double dt;
    // Take User Input
    std::cout << "Simulate 3D (1) or 2D (0) ?" << std::endl;
    std::cin >> is3D;
    std::cout << "Enter number of particles in the system:" << std::endl;
    std::cin >> numSpheres;
    std::cout << "Set a delta t value (default 0.1): " << std::endl;
    std::cin >> dt;
    initialize_scale_factor();

    
    // Initialize window and openGL
    glutInit(&argc, argv);
    brownian = new Window(is3D);
    // Initialize particles
    brownian->generate_spheres(numSpheres);
    brownian->set_deltaT(dt);
    
    glutReshapeFunc(reshape);
    if (is3D) {
        glutDisplayFunc(display3D);
        glutIdleFunc(display3D);       
    }
    else {
        glutDisplayFunc(display);
        glutIdleFunc(display);
    }  
    glutCreateMenu(buttons);
    glutAddMenuEntry("Change Temperature", 1);
    glutAddMenuEntry("Hide Particles", 2);
    glutAddMenuEntry("Show Particles", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_LEFT_BUTTON);
                      
    glutMainLoop();  
    // Add deconstructors here 
    return 0;
}