#include "spheres.h"
#include <iostream>

void intersphere_collision(std::vector<Sphere>& spheresGL)
{
    int i,j;
    double dist;
    bool hasCollided;
    std::vector<std::vector<int>> pairs;

    for (i=0; i < spheresGL.size(); i++) {
        for (j=0; j < spheresGL.size(); j++) {
            hasCollided = is_collision(spheresGL[i].m_radius, spheresGL[j].m_radius,
                            spheresGL[i].m_position, spheresGL[j].m_position);
            if (i!=j && hasCollided && check_pairs(pairs, i, j)) {
                update_collision_velocity(spheresGL[i], spheresGL[j]);
                pairs.push_back({i,j});
            }
        }
    }
}

bool check_pairs(std::vector<std::vector<int>> pairs, int j1, int j2)
{
    int i,j;
    for (i=0; i < pairs.size(); i++) {
        if ((j1 == pairs[i][0] && j2 == pairs[i][1]) || j1 == pairs[i][1] && j2 == pairs[i][0])
            return false;
    }
    return true;

}

bool is_collision(double r1, double r2, vec3 pos1, vec3 pos2)
{
    double dist = sqrt(pow(pos1.x - pos2.x,2) + pow(pos1.y - pos2.y,2) + pow(pos1.z - pos2.z,2));
    if (dist <= (r1+r2))
        return true;
    else
        return false;
}

void update_collision_velocity(Sphere& C1, Sphere& C2)
{
    double m1,m2, sc1, sc2;
    m1 = C1.m_radius*1.5; m2 = C2.m_radius;
    sc1 = (2*m2)/(m1+m2); sc2 = (2*m1)/(m1+m2);

    vec3 norm = {C1.m_position.x - C2.m_position.x,
                 C1.m_position.y - C2.m_position.y,
                 C1.m_position.z - C2.m_position.z};
    double mag = sqrt(pow(norm.x,2) + pow(norm.y,2) + pow(norm.z,2));
    norm.x /= mag; norm.y /= mag; norm.z /= mag;

    vec3 vrel = {C1.m_velocity.x - C2.m_velocity.x,
                 C1.m_velocity.y - C2.m_velocity.y,
                 C1.m_velocity.z - C2.m_velocity.z};

    double v_alongNorm = vrel.x*norm.x + vrel.y*norm.y + vrel.z*norm.z;
    norm.x *= v_alongNorm; norm.y *=v_alongNorm; norm.z *=v_alongNorm;

    C1.m_velocity.x -= sc1*norm.x; C1.m_velocity.y -= sc1*norm.y; C1.m_velocity.z -= sc1*norm.z;
    C2.m_velocity.x += sc2*norm.x; C2.m_velocity.y += sc2*norm.y; C2.m_velocity.z += sc2*norm.z;

}

void initialize_spheres(std::vector<Sphere>& spheresGL, int numSpheres, bool is3D)
{
    Sphere sphereStack;
    vec3 posRandomizer;
    vec3 velRandomizer;
    color particleColor;

    if (!is3D) particleColor = {1.0,1.0,1.0};
    else particleColor = {0.0, 0.0, 0.0};

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
        velRandomizer = {rand()%(VEL)-VEL, rand()%(VEL)-VEL, rand()%(VEL)-VEL};
        posRandomizer = {rand()%(2*LENGTH)-LENGTH, rand()%(2*HEIGHT)-HEIGHT, rand()%(2*DEPTH)-DEPTH};
        if (!is3D) {
            velRandomizer.z = 0;
            posRandomizer.z = 0;
        }
        sphereStack = Sphere(0.75, particleColor, posRandomizer, velRandomizer);
        spheresGL.push_back(sphereStack);
        //delete sphereStack;
    }
    
    //return spheresGL;    
}

void Sphere::border_collision()
{
    if (fabs(m_position.x) >= LENGTH)
        m_velocity.x *= -1;
    if (fabs(m_position.y) >= HEIGHT)
        m_velocity.y *= -1;
    if (fabs(m_position.z) >= DEPTH)
        m_velocity.z *= -1;
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

Sphere::Sphere(GLfloat newRadius, color newColor, vec3 initPos, vec3 initVel)
{
    m_radius = newRadius;
    m_position = initPos;
    m_velocity = initVel;
    m_color = newColor; 
}
/////////////////////////////////
Sphere::~Sphere() {}
