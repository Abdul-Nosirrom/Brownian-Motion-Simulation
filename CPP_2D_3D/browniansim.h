#include <math.h>
#include <random>
#include <chrono>
#include <iostream>
#include "vec.h"

extern "C" void gaussian_(float *);

void initialize_scale_factor();

void brownian_sim(vec3& position, double dt, bool is3D);

float boltz (float T);

float get_random(int max);