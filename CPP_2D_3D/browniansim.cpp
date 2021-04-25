//#include "browniansim.h"
#include "browniansim.h"

void brownian_sim(vec3& position, double dt, bool is3D)
{
    // Check for collision, if none do the below
    //FILE *data = fopen("randomwalk.data", "a");
    float rand_norm;
    static double totalTime = 0;
    double dx, dy, dz;
    //fprintf(data, "%lf %lf\n", totalTime, position.x);
    gaussian_(&rand_norm);
    dx = sqrt(dt) * rand_norm;
    position.x += dx;
    //fclose(data);
    totalTime += dt;
    gaussian_(&rand_norm);
    dy = sqrt(dt) * rand_norm;
    position.y += dy;

    if (is3D) {
        gaussian_(&rand_norm);
        dz = sqrt(dt) * rand_norm;
        position.z += dx;
    }
}