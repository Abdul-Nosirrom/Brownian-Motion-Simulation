//#include "browniansim.h"
#include "browniansim.h"

std::default_random_engine generator;
std::normal_distribution<float> distribution(0,1);

void brownian_sim(vec3& position, double dt, bool is3D)
{

    float rand_norm;
    static double totalTime = 0;
    double dx, dy, dz;
    rand_norm = distribution(generator);
    //gaussian_(&rand_norm);
    dx = sqrt(dt) * rand_norm;
    position.x += dx;
    totalTime += dt;
    //gaussian_(&rand_norm);
    rand_norm = distribution(generator);
    dy = sqrt(dt) * rand_norm;
    position.y += dy;

    if (is3D) {
        //gaussian_(&rand_norm);
        rand_norm = distribution(generator);
        dz = sqrt(dt) * rand_norm;
        position.z += dz;
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

float get_random(int max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(-1,1); // rage -1 -> 1
    return max*dis(e);
}
