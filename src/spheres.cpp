#include "spheres.h"
#include <algorithm>

// Operator overload
bool Sphere::operator==(const Sphere& s2) {
    return (m_radius == s2.m_radius && m_position.x == s2.m_position.x 
            && m_position.y == s2.m_position.y && m_position.z == s2.m_position.z);}


void initialize_spheres(std::vector<Sphere*>& spheresGL, long unsigned int numSpheres, bool is3D)
{
    Sphere *sphereStack;
    vec3 posRandomizer;
    vec3 velRandomizer;
    color particleColor;

    float velMag;
    float mainRadius = 3;
    float rad = 0.8;

    if (!is3D) particleColor = {1.0,1.0,1.0};
    else particleColor = {0, 0.2, 0.4};

    long unsigned int i;

    sphereStack = new Sphere(mainRadius, {1,0,0});
    spheresGL.push_back(sphereStack);
  
    for (i=0; i<numSpheres; i++) {
        velMag = boltz(DEFAULT_TEMP);
        velRandomizer = {get_random(1), get_random(1), get_random(1)};
        velRandomizer = velRandomizer.normalized()*velMag;
        posRandomizer = {get_random(LENGTH-rad), get_random(HEIGHT-rad), get_random(DEPTH-rad)};
        if (!is3D) {
            posRandomizer.z = 0; velRandomizer.z = 0;
        }
        sphereStack = new Sphere(rad, particleColor, posRandomizer, velRandomizer);
        spheresGL.push_back(sphereStack);
     
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

/* Collision Getters for Sweep & Prune */
float Sphere::minx(){return this->m_position.x - this->m_radius;}
float Sphere::maxx(){return this->m_position.x + this->m_radius;}
float Sphere::miny(){return this->m_position.y - this->m_radius;}
float Sphere::maxy(){return this->m_position.y + this->m_radius;}
float Sphere::minz(){return this->m_position.z - this->m_radius;}
float Sphere::maxz(){return this->m_position.z + this->m_radius;}

