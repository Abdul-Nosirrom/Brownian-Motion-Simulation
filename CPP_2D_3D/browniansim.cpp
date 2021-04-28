//#include "browniansim.h"
#include "browniansim.h"

void brownian_sim(vec3& position, double dt, bool is3D)
{
    // Check for collision, if none do the below
    float rand_norm;
    static double totalTime = 0;
    double dx, dy, dz = 0;
    gaussian_(&rand_norm);
    dx = sqrt(dt) * rand_norm;
    position.x += dx;
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

// Function to draw initial velocities fron the Maxwell
// distribution for a given temperature T

float boltz (float T)
{
    T /= 50;
    uint32_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::gamma_distribution<GLfloat> maxwell(3./2., T);


    return maxwell(generator);
}

float get_random(int min, int max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(min,max); // rage -1 -> 1
    return dis(e);
}
