#include <iostream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <list>
#include <memory>

#include "collisionhandler.h"


void timer();



class Window 
{
    bool is3D;
    double dt;

    public:
        std::vector<Sphere*> m_Spheres;
        std::vector<vec3> m_path;
        bool showParticles = false;

    public:
        Window(bool);

        Window(bool, int);

        void generate_spheres(int);

        void reshape(int, int);

        void display();

        void display3D();

        void set_deltaT(double new_dt);

        void buttons(int selection);

        ~Window();

    private:
        void draw_spheres2D();

        void draw_spheres3D();

        void update_positions();

        void draw_path();

        void draw_axes();

        FILE* outputData;



};
