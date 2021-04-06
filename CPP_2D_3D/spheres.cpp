#include "spheres.h"

std::vector<Sphere> initialize_spheres(int numSpheres)
{
    Sphere* sphereStack;
    vec3 posRandomizer;

    int i;
    //Sphere *spheresGL = (sphere *)malloc(sizeof(sphere)*numSpheres);

    std::vector<Sphere> spheresGL;
    spheresGL.reserve(numSpheres);

    sphereStack = new Sphere(2, {1,0,0});
    spheresGL.push_back(*sphereStack);
    delete sphereStack;

    for (i=0; i<numSpheres; i++) {
        posRandomizer = {rand()%BORDERS, rand()%BORDERS, rand()%BORDERS};
        sphereStack = new Sphere(0.75, {0,0,0}, posRandomizer);
        spheresGL.push_back(*sphereStack);
        delete sphereStack;
    }
    
    return spheresGL;    
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

