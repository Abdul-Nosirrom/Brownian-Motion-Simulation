#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "datastructures.h"

std::vector<Sphere> initialize_spheres(int numSpheres);

typedef struct color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} color;

class Sphere
{
    public:
        vec3 position;
        vec3 velocity;
        GLfloat radius;
        GLfloat color[3];

    public:

        Sphere();
        Sphere(GLfloat newRadius, GLfloat color[3]);
        void draw_sphere();

};
