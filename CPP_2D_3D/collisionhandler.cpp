#include "collisionhandler.h"


void handleSphereSphereCollisions(std::vector<Sphere*> &particles)
{
    long unsigned int i,j;
    double dist;
    bool hasCollided;
    std::vector<std::vector<int>> pairs;

    for (i=0; i < particles.size(); i++) {
        for (j=i+1; j < particles.size(); j++) {
            hasCollided = is_collision(particles[i], particles[j]);
            if (hasCollided)
                update_collision_velocity(particles[i], particles[j]);
        }
    }
}


bool is_collision(Sphere* p1, Sphere* p2)
{
    double r1 = p1->m_radius, r2 = p2->m_radius;
    vec3 pos1 = p1->m_position, pos2 = p2->m_position;
    double dist = sqrt(pow(pos1.x - pos2.x,2) + pow(pos1.y - pos2.y,2) + pow(pos1.z - pos2.z,2));
    if (dist <= (r1+r2))
        return true;
    else
        return false;
}

void update_collision_velocity(Sphere* C1, Sphere* C2)
{
    vec3 cDiff = C2->m_position - C1->m_position;
    vec3 dir = cDiff.normalized();
    vec3 vDiff = C2->m_velocity - C1->m_velocity;

    float fellingSpeed = vDiff.dot(dir);
    if (fellingSpeed >=0)
        return;

    float s1 = (2*C2->m_radius*fellingSpeed)/ (C2->m_radius + C1->m_radius);
    float s2 = (fellingSpeed * (C2->m_radius - C1->m_radius))/ (C2->m_radius + C1->m_radius);
    s2 -= fellingSpeed;
    C1->m_velocity = (dir*s1) + C1->m_velocity;
    C2->m_velocity = (dir*s2) + C2->m_velocity;
}