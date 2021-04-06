#include "spheres.h"

std::vector<Sphere> initialize_spheres(int numSpheres)
{
    int i;
    //Sphere *spheresGL = (sphere *)malloc(sizeof(sphere)*numSpheres);

    std::vector<Sphere> spheresGL;
    spheresGL.reserve(numSpheres);

    spheresGL[0].color[0] = 1.0;
    spheresGL[0].radius = 5;
    

    for (i=1; i < numSpheres; i++) {
        spheresGL[i].color[0] = 0.0;
        spheresGL[i].color[1] = 0.0;
        spheresGL[i].color[2] = 0.0;

        spheresGL[i].radius = 2;
        spheresGL[i].position.x = (float) drand48() * 30;
        spheresGL[i].position.y = (float) drand48() * 30;
        spheresGL[i].position.z = (float) drand48() * 30;
    }

    return spheresGL;    
}

