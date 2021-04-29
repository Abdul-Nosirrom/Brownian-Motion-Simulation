#include "spheres.h"
#include <vector>

void handleSphereSphereCollisions(std::vector<Sphere*> &particles);
bool is_collision(Sphere* p1, Sphere* p2);
void update_collision_velocity(Sphere* C1, Sphere* C2);
