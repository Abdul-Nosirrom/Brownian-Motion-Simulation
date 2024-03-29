#include <iostream>
#include "window.h"

Window *brownian;

void display()
{
    brownian->display();
}

void display3D()
{
    brownian->display3D();
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
    int is3D, dataFile, nSteps;
    long unsigned int numSpheres;
    double dt;
    // Take User Input
    std::cout << "Generate data file (1) or not (0) ?" << std::endl;
    std::cin >> dataFile;
    if (dataFile) {
        std::cout << "Number of steps to record (Rec: 5000)" << std::endl;
        std::cin >> nSteps;
    }
    std::cout << "For data closest to Wiener process when using collision, 2D is recommended" << std::endl;
    std::cout << "Simulate 3D (1) or 2D (0) ?" << std::endl;
    std::cin >> is3D;
    std::cout << "Enter number of particles in the system (Rec: 350 for 2D, 500 for 3D), select 0 for Wiener process:" << std::endl;
    std::cin >> numSpheres;
    std::cout << "Set a delta t value (Rec: 0.05): " << std::endl;
    std::cin >> dt;
    initialize_scale_factor();

    
    // Initialize window and openGL
    glutInit(&argc, argv);
    brownian = new Window(is3D, dataFile);
    // Initialize particles
    brownian->generate_spheres(numSpheres);
    brownian->set_deltaT(dt);
    if (dataFile) brownian->numSteps = nSteps;
    
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
    return 0;
}