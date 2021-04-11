extern "C" void gaussian_(float *);
#include "spheres.h"
#include <iostream>

void initialize_spheres(std::vector<Sphere>& spheresGL, int numSpheres, bool is3D)
{
    Sphere sphereStack;
    vec3 posRandomizer;
    color particleColor;

    if (!is3D) particleColor = {1.0,1.0,1.0};

    long unsigned int i;
    //Sphere *spheresGL = (sphere *)malloc(sizeof(sphere)*numSpheres);

    //std::vector<Sphere> spheresGL;
    //spheresGL.resize(numSpheres);

    sphereStack = Sphere(2, {1,0,0});
    spheresGL.push_back(sphereStack);
    //delete sphereStack;

    //std::cout << spheresGL.capacity() <<std::endl;
    float val;
    for (i=0; i<numSpheres; i++) {
        gaussian_(&val);
        posRandomizer = {rand()%(2*LENGTH)-LENGTH, rand()%(2*HEIGHT)-HEIGHT, rand()%(2*DEPTH)-DEPTH};
        sphereStack = Sphere(0.75, particleColor, posRandomizer);
        spheresGL.push_back(sphereStack);
        //delete sphereStack;
        std::cout << val << "\n";
    }
    
    //return spheresGL;    
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

Sphere::Sphere(GLfloat newRadius, color newColor, vec3 initPos)
{
    m_radius = newRadius;
    m_position = initPos;
    m_velocity = {0, 0, 0};
    m_color = newColor; 
}
/////////////////////////////////
Sphere::~Sphere() {}
