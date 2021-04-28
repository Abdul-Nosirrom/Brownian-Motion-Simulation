#include "spheres.h"
#include <iostream>
#include <algorithm>

// Operator overload
bool Sphere::operator==(const Sphere& s2) {
    return (m_radius == s2.m_radius && m_position.x == s2.m_position.x 
            && m_position.y == s2.m_position.y && m_position.z == s2.m_position.z);}


void initialize_spheres(std::vector<Sphere*>& spheresGL, long unsigned int numSpheres, bool is3D)
{
    Sphere *sphereStack;
    vec3 posRandomizer;
    vec3 posDistr;
    vec3 velRandomizer;
    color particleColor;

    float mainRadius = 3;
    float rad = 0.8;

    float spacing = LENGTH/sqrt(numSpheres);
    if (is3D) spacing = LENGTH/(pow(numSpheres, 1/3));

    if (!is3D) particleColor = {1.0,1.0,1.0};
    else particleColor = {0.0, 0.0, 0.0};

    long unsigned int i;
    float x=-LENGTH + rad,y=-HEIGHT + rad;//z=-DEPTH + rad;

    sphereStack = new Sphere(mainRadius, {1,0,0});
    spheresGL.push_back(sphereStack);

    //std::cout << spheresGL.capacity() <<std::endl;
    /*for (i=0; i<numSpheres; i++) {
        velRandomizer = {rand()%(VEL)-VEL, rand()%(VEL)-VEL, rand()%(VEL)-VEL};
        posRandomizer = {rand()%(2*(LENGTH-1))-LENGTH+1, rand()%(2*(HEIGHT-1))-(HEIGHT-1), rand()%(2*(DEPTH-1)+1-DEPTH)};
        if (!is3D) {
            velRandomizer.z = 0;
            posRandomizer.z = 0;
        }
        velRandomizer = {0,0,0};
        sphereStack = Sphere(0.75, particleColor, posRandomizer, velRandomizer);
        spheresGL.push_back(sphereStack);
        //delete sphereStack;
    } */
    if (is3D) {
     for (i=0; i<numSpheres; i++) {
        velRandomizer = {get_random(-1,1), get_random(-1,1), get_random(-1,1)};
        velRandomizer = velRandomizer.normalized();
        std::cout << velRandomizer.x << velRandomizer.y << velRandomizer.z <<std::endl;
        posRandomizer = {get_random(-LENGTH,LENGTH), get_random(-HEIGHT,HEIGHT), get_random(-DEPTH,DEPTH)};

        //velRandomizer = {0,0,0};
        sphereStack = new Sphere(rad, particleColor, posRandomizer, velRandomizer);
        spheresGL.push_back(sphereStack);
     }

    } else {
        for (x=-LENGTH+rad; x < LENGTH-rad; x+=spacing) {
            for (y=-LENGTH+rad; y < LENGTH-rad; y += spacing) {
                if (spheresGL.size() >= numSpheres) break;
                
                posDistr = {x,y,0};
                velRandomizer = {get_random(-1,1), get_random(-1,1), 0};
                velRandomizer = velRandomizer.normalized();
                sphereStack = new Sphere(rad, particleColor, posDistr, velRandomizer);
                spheresGL.push_back(sphereStack);
            }
        }
    }

}

void Sphere::border_collision()
{
    if (fabs(m_position.x) + m_radius >= LENGTH)
        m_velocity.x *= -1;
    if (fabs(m_position.y) + m_radius >= HEIGHT)
        m_velocity.y *= -1;
    if (fabs(m_position.z) + m_radius >= DEPTH)
        m_velocity.z *= -1;
}

////////////////////////////////
/*      Constructors          */
///////////////////////////////
Sphere::Sphere()
{
    m_radius = 1;
    m_position = {0, 0, 0};
    m_velocity = {0, 0, 0};
    m_color = {0, 0, 0};
}

Sphere::Sphere(GLfloat newRadius, color newColor)
{
    m_radius = newRadius;
    m_position = {0, 0, 0};
    m_velocity = {0, 0, 0};
    m_color = newColor; 
}

Sphere::Sphere(GLfloat newRadius, color newColor, vec3 initPos, vec3 initVel)
{
    m_radius = newRadius;
    m_position = initPos;
    m_velocity = initVel;
    m_color = newColor; 
}
/////////////////////////////////
Sphere::~Sphere() {}

/* Collision Getters */
float Sphere::minx(){return this->m_position.x - this->m_radius;}
float Sphere::maxx(){return this->m_position.x + this->m_radius;}
float Sphere::miny(){return this->m_position.y - this->m_radius;}
float Sphere::maxy(){return this->m_position.y + this->m_radius;}
float Sphere::minz(){return this->m_position.z - this->m_radius;}
float Sphere::maxz(){return this->m_position.z + this->m_radius;}

