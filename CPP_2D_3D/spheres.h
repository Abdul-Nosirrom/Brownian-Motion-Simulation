#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <memory>

//#include "datastructures.h"
#include "browniansim.h"

#define LENGTH 50
#define HEIGHT 50
#define DEPTH 50

#define VEL 15


typedef struct color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} color;

class Sphere
{
    public:
        vec3 m_position;
        vec3 m_velocity;
        GLfloat m_radius;
        color m_color;

    public:

        Sphere();
        Sphere(GLfloat newRadius, color newColor);
        Sphere(GLfloat newRadius, color newColor, vec3 initPos, vec3 initVel);
        void draw_sphere();
        void border_collision();
        ~Sphere();

};

//std::vector<Sphere> initialize_spheres(int numSpheres);
void initialize_spheres(std::vector<Sphere>&, int numSpheres, bool is3D);
void border_collision(Sphere);
