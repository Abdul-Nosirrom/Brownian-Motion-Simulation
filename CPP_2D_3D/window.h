#include <iostream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <memory>

#include "spheres.h"
//#include "datastructures.h"

#define LENGTH 50.0
#define HEIGHT 50.0

void timer();

class Window 
{
    bool is3D;
    //std::vector<std::unique_ptr<Sphere>> ptr_Spheres;
    //int spheresRendered;

    public:
        std::vector<Sphere> m_Spheres;

    public:
        Window(bool);

        Window(bool, int);

        void generate_spheres(int);

        void reshape(int, int);

        void display();

        void display3D();

        ~Window();

    private:
        void draw_spheres2D();

        void draw_spheres3D();

        void draw_axes();


};
