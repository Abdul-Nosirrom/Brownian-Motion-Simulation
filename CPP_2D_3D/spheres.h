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

#include "datastructures.h"


#define LENGTH 50
#define HEIGHT 50
#define DEPTH 50

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
        Sphere(GLfloat newRadius, color newColor, vec3 initPos);
        void draw_sphere();
        ~Sphere();

};

//std::vector<Sphere> initialize_spheres(int numSpheres);
void initialize_spheres(std::vector<Sphere>&, int numSpheres, bool is3D);
