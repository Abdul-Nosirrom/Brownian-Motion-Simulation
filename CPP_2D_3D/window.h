#include <iostream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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


        ~Window();
};