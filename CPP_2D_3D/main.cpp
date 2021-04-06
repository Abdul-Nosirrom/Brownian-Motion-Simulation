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


int main(int argc, char *argv[]) 
{
    int is3D;
    std::cout << "3D/2D (1/0)" << std::endl;
    std::cin >> is3D;
    glutInit(&argc, argv);
    brownian = new Window(is3D);
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
    return 0;
}