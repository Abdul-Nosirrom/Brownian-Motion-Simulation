#include "spheres.h"
#include <iostream>
// Operator overload
bool operator==(Sphere& s1, Sphere& s2) {
    return (s1.m_radius == s2.m_radius && s1.m_position.x == s2.m_position.x 
            && s1.m_position.y == s2.m_position.y && s1.m_position.z == s2.m_position.z);}
/* Sweep and Prune Methods */
void removeEntitites(std::vector<Sphere>& spheresGL, std::vector<Sphere>& toRemove)
{
    size_t i;
    size_t j;
    bool didRemove;

    if (toRemove.size()) return;

    for (i=0; i < spheresGL.size(); i++) {
        didRemove = false;
        do {
            didRemove = false;
            for (j=0; j < toRemove.size(); j++) {
                if (spheresGL[i] == toRemove[j]) {
                    // Swap remove spheresGL
                    std::swap(spheresGL[i], spheresGL[spheresGL.size() - 1]);
                    spheresGL.pop_back();
                    std::swap(toRemove[j], toRemove[toRemove.size() - 1]);
                    toRemove.pop_back();
                    didRemove = true; break;
                }
            }
            if (toRemove.size() && didRemove) return;
        } while(didRemove);
    }
    toRemove.clear();
}

void sweep_prune(std::vector<Sphere>& spheresGL)
{

}

void intersphere_collision(std::vector<Sphere>& spheresGL)
{
    int i,j;
    double dist;
    bool hasCollided;
    std::vector<std::vector<int>> pairs;

    for (i=0; i < spheresGL.size(); i++) {
        for (j=i+1; j < spheresGL.size(); j++) {
            hasCollided = is_collision(spheresGL[i].m_radius, spheresGL[j].m_radius,
                            spheresGL[i].m_position, spheresGL[j].m_position);
            if (i!=j && hasCollided){ //&& check_pairs(pairs, i, j)) {
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
    /*
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
*/
    vec3 cDiff = C2.m_position - C1.m_position;
    vec3 dir = cDiff.normalized();
    vec3 vDiff = C2.m_velocity - C1.m_velocity;

    float fellingSpeed = vDiff.dot(dir);
    if (fellingSpeed >=0)
        return;

    float s1 = (2*C2.m_radius*fellingSpeed)/ (C2.m_radius + C1.m_radius);
    float s2 = (fellingSpeed * (C2.m_radius - C1.m_radius))/ (C2.m_radius + C1.m_radius);
    s2 -= fellingSpeed;
    C1.m_velocity = (dir*s1) + C1.m_velocity;
    C2.m_velocity = (dir*s2) + C2.m_velocity;
}

void initialize_spheres(std::vector<Sphere>& spheresGL, int numSpheres, bool is3D)
{
    Sphere sphereStack;
    vec3 posRandomizer;
    vec3 posDistr;
    vec3 velRandomizer;
    color particleColor;

    float mainRadius = 4;
    float rad = 1;

    float spacing = LENGTH/sqrt(numSpheres);
    if (is3D) spacing = LENGTH/(pow(numSpheres, 1/3));

    if (!is3D) particleColor = {1.0,1.0,1.0};
    else particleColor = {0.0, 0.0, 0.0};

    long unsigned int i;
    float x=-LENGTH + rad,y=-HEIGHT + rad,z=-DEPTH + rad;
    //Sphere *spheresGL = (sphere *)malloc(sizeof(sphere)*numSpheres);

    //std::vector<Sphere> spheresGL;
    //spheresGL.resize(numSpheres);

    sphereStack = Sphere(mainRadius, {1,0,0});
    spheresGL.push_back(sphereStack);
    //delete sphereStack;

    //std::cout << spheresGL.capacity() <<std::endl;
    /*for (i=0; i<numSpheres; i++) {
        velRandomizer = {rand()%(VEL)-VEL, rand()%(VEL)-VEL, rand()%(VEL)-VEL};
        posRandomizer = {rand()%(2*(LENGTH-1))-LENGTH+1, rand()%(2*(HEIGHT-1))-(HEIGHT-1), rand()%(2*(DEPTH-1)+1-DEPTH)};
        if (!is3D) {
            velRandomizer.z = 0;
            posRandomizer.z = 0;
        }
        velRandomizer = {0,0,0};
        sphereStack = Sphere(0.75, particleColor, posRandomizer, velRandomizer);
        spheresGL.push_back(sphereStack);
        //delete sphereStack;
    } */
    if (is3D) {
     for (i=0; i<numSpheres; i++) {
        velRandomizer = {rand()%(VEL)-VEL, rand()%(VEL)-VEL, rand()%(VEL)-VEL};
        posRandomizer = {rand()%(2*(LENGTH-1))-LENGTH+1, rand()%(2*(HEIGHT-1))-(HEIGHT-1), rand()%(2*(DEPTH-1)+1-DEPTH)};

        //velRandomizer = {0,0,0};
        sphereStack = Sphere(rad, particleColor, posRandomizer, velRandomizer);
        spheresGL.push_back(sphereStack);
     }

    } else {
        for (x=-LENGTH+rad; x < LENGTH-rad; x+=spacing) {
            for (y=-LENGTH+rad; y < LENGTH-rad; y += spacing) {
                if (spheresGL.size() >= numSpheres) break;
                
                posDistr = {x,y,0};

                //velRandomizer = {0, 0, 0};
                velRandomizer = {rand()%(VEL)-VEL, rand()%(VEL)-VEL, 0};
                sphereStack = Sphere(rad, particleColor, posDistr, velRandomizer);
                spheresGL.push_back(sphereStack);
            }
        }
    }
    //return spheresGL;    
}

void Sphere::border_collision()
{
    if (fabs(m_position.x) + m_radius >= LENGTH)
        m_velocity.x *= -1;
    if (fabs(m_position.y) + m_radius >= HEIGHT)
        m_velocity.y *= -1;
    if (fabs(m_position.z) + m_radius >= DEPTH)
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

/* Collision Getters */
float Sphere::minx(){return this->m_position.x - this->m_radius;}
float Sphere::maxx(){return this->m_position.x + this->m_radius;}
float Sphere::miny(){return this->m_position.y - this->m_radius;}
float Sphere::maxy(){return this->m_position.y + this->m_radius;}
float Sphere::minz(){return this->m_position.z - this->m_radius;}
float Sphere::maxz(){return this->m_position.z + this->m_radius;}

/* Grid Define */
void Sphere::grid_define(Sphere& s)
{
    // Defining grid/box size
    float x_int = (float)LENGTH/3;
    float y_int = (float)HEIGHT/3;
    float z_int = (float)DEPTH/3;

    // Placing sphere in a box - can be in two places at once so not if else
    // Goal is to minimize time searching for pairs of collision so this 
    // partition function should be constant time

    // Box 1,2,3
    if (-LENGTH <= m_position.x <= -LENGTH + x_int) {
        // y-box 1
        if (-HEIGHT <= m_position.y <= -HEIGHT + y_int) {
            // z-box 1
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[0][0][0].push_back(s);
            }
            //z-box 2
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[0][0][1].push_back(s);
            }
            // z-box 3
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[0][0][2].push_back(s);
            }
        }
        // y-box 2
        if (-HEIGHT + y_int <= m_position.y <= HEIGHT - y_int) {
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[0][1][0].push_back(s);
            }
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[0][1][1].push_back(s);
            }
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[0][1][2].push_back(s);
            }
        }
        // y-box 3
        if (HEIGHT - y_int <= m_position.y <= HEIGHT) {
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[0][2][0].push_back(s);
            }
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[0][2][1].push_back(s);
            }
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[0][2][2].push_back(s);
            }
        }

    // x-box 2
    if (-LENGTH <= m_position.x <= -LENGTH + x_int) {
        // y-box 1
        if (-HEIGHT <= m_position.y <= -HEIGHT + y_int) {
            // z-box 1
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[1][0][0].push_back(s);
            }
            //z-box 2
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[1][0][1].push_back(s);
            }
            // z-box 3
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[1][0][2].push_back(s);
            }
        }
        // y-box 2
        if (-HEIGHT + y_int <= m_position.y <= HEIGHT - y_int) {
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[1][1][0].push_back(s);
            }
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[1][1][1].push_back(s);
            }
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[1][1][2].push_back(s);
            }
        }
        // y-box 3
        if (HEIGHT - y_int <= m_position.y <= HEIGHT) {
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[1][2][0].push_back(s);
            }
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[1][2][1].push_back(s);
            }
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[1][2][2].push_back(s);
            }
        }
    }

    // x-box 3
    if (-LENGTH <= m_position.x <= -LENGTH + x_int) {
        // y-box 1
        if (-HEIGHT <= m_position.y <= -HEIGHT + y_int) {
            // z-box 1
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[2][0][0].push_back(s);
            }
            //z-box 2
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[2][0][1].push_back(s);
            }
            // z-box 3
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[2][0][2].push_back(s);
            }
        }
        // y-box 2
        if (-HEIGHT + y_int <= m_position.y <= HEIGHT - y_int) {
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[2][1][0].push_back(s);
            }
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[2][1][1].push_back(s);
            }
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[2][1][2].push_back(s);
            }
        }
        // y-box 3
        if (HEIGHT - y_int <= m_position.y <= HEIGHT) {
            if (-DEPTH <= m_position.z <= -DEPTH + z_int) {
                partitions[2][2][0].push_back(s);
            }
            if (-DEPTH + z_int <= m_position.z <= DEPTH - z_int) {
                partitions[2][2][1].push_back(s);
            }
            if (DEPTH - z_int <= m_position.z <= DEPTH) {
                partitions[2][2][2].push_back(s);
            }
        }
    }

}
