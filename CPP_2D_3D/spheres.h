#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <unordered_set>
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
        void draw_sphere();
        void border_collision();
        ~Sphere();
        bool operator== (const Sphere& s);
        //void grid_define(Sphere&);
        float minx();
        float maxx();
        float miny();
        float maxy();
        float minz();
        float maxz();

};

//std::vector<Sphere> initialize_spheres(int numSpheres);
void initialize_spheres(std::vector<Sphere>&, int numSpheres, bool is3D);
void border_collision(Sphere);
void intersphere_collision(std::vector<Sphere>&);
void grid_define(std::vector<Sphere>&, bool);
bool check_pairs(std::vector<std::vector<int>> pairs, int j1, int j2);
bool is_collision(double r1, double r2, vec3 pos1, vec3 pos2);
void update_collision_velocity(Sphere& C1, Sphere& C2);
void reset_partitions();
void intersphere_collisionV2();


