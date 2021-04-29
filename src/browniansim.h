#include <math.h>
#include <random>
#include <chrono>
#include <iostream>
#include "vec.h"

#define DEFAULT_TEMP 273

void brownian_sim(vec3& position, double dt, bool is3D);

float boltz (float T);

float get_random(int max);