#include "spheres.h"
#include <iostream>
#include <algorithm>

// Objects
// Define a 3x3 grid 
    /*  1  2  3
     *  4  5  6
     *  7  8  9 */
std::vector<Sphere> partitions[3][3][3];


// Operator overload
bool Sphere::operator==(const Sphere& s2) {
    return (m_radius == s2.m_radius && m_position.x == s2.m_position.x 
            && m_position.y == s2.m_position.y && m_position.z == s2.m_position.z);}
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


void intersphere_collisionV2()
{
    int i,j,k,l,m;
    bool hasCollided;

    for (i=0; i < 3; i++) {
        for (j=0; j < 3; j++) {
            std::cout << partitions[i][j][0].size() << std::endl;
            for (k=0; k < 3; k++) {
                for (l=0; l < partitions[i][j][k].size(); l++) {
                    for (m=l+1; m < partitions[i][j][k].size(); m++) {
                        hasCollided = is_collision(
                            partitions[i][j][k][l].m_radius, 
                            partitions[i][j][k][m].m_radius,
                            partitions[i][j][k][l].m_position, 
                            partitions[i][j][k][m].m_position);
                        if (hasCollided)
                            update_collision_velocity(partitions[i][j][k][l], partitions[i][j][k][m]);
                    }
                }
            }
        }
    }
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

    float mainRadius = 3;
    float rad = 0.8;

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
    grid_define(spheresGL, is3D);
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
void grid_define(std::vector<Sphere>& spheresGL, bool is3D)
{
    // Defining grid/box size
    float x_int = (float)2*LENGTH/3;
    float y_int = (float)2*HEIGHT/3;
    float z_int = (float)2*DEPTH/3;

    int i,j,k, s;
    float upper_x = -LENGTH + x_int, lower_x = -LENGTH, 
          upper_y = -HEIGHT + y_int, lower_y = -HEIGHT, 
          upper_z = -DEPTH + z_int, lower_z = -DEPTH;

    bool ins;

    reset_partitions();
    for (s = 0; s < spheresGL.size(); s++) {

        lower_x = -LENGTH; upper_x = lower_x + x_int; 
        lower_y = -HEIGHT; upper_y = lower_y + y_int;  
        lower_z = -DEPTH;  upper_z = lower_z + z_int; 

    for (i=0; i < 3; i++) {
        ins = false;
        if (lower_x <= spheresGL[s].m_position.x && spheresGL[s].m_position.x <= upper_x) ins = true;
        for (j=0; j < 3; j++) {
            if (lower_x <= spheresGL[s].m_position.x && spheresGL[s].m_position.x <= upper_x && ins) ins = true;
            else ins = false;
            if (is3D) {
                for (k=0; k < 3; k++) {
                    if (lower_z <= spheresGL[s].m_position.z && spheresGL[s].m_position.z <= upper_z && ins) {
                        partitions[i][j][k].push_back(spheresGL[s]);
                    }
                    upper_z += z_int;
                    lower_z += z_int;
                }
            } if (ins){
                partitions[i][j][0].push_back(spheresGL[s]);
            }
            lower_y += y_int;
            upper_y = lower_y + y_int;
        }
        lower_x += x_int;
        upper_x = lower_x + x_int;
    }

    }
}

void reset_partitions()
{
    int i,j,k;

    for (i=0; i < 3; i++) {
        for (j=0; j < 3; j++) {
            for (k=0; k < 3; k++) {
                partitions[i][j][k].clear();
            }
        }
    }
}
