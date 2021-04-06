#include <iostream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

#include "spheres.h"
#include "datastructures.h"

#define LENGTH 50.0
#define HEIGHT 50.0

void timer();

class Window 
{
    void draw_axes();

    public:
        Window(bool);

        void reshape(int, int);

        void display();

        void display3D();

        void draw_spheres2D(std::vector<Sphere>);

        void draw_spheres3D(std::vector<Sphere>);


        ~Window();
};