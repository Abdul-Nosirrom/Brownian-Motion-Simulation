#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <vector>
#include <memory>
#include "browniansim.h"

#define LENGTH 20
#define HEIGHT 20
#define DEPTH 20

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
        void border_collision();
        ~Sphere();
        bool operator== (const Sphere& s);
        float minx();
        float maxx();
        float miny();
        float maxy();
        float minz();
        float maxz();

};

void initialize_spheres(std::vector<Sphere*>&, long unsigned int numSpheres, bool is3D);



