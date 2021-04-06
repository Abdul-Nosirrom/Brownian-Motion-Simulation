#include "spheres.h"

int sphereTotal;

int isCollide(vec3 curPos)
{
    if ((fabs(curPos.x) >= LENGTH) && (fabs(curPos.y) >= HEIGHT))
        return BOTH_COLLIDE;
    else if ((fabs(curPos.x) >= LENGTH) && !( fabs(curPos.y) >= HEIGHT))
        return HOR_COLLIDE;
    else if ((fabs(curPos.x) >= LENGTH) && ! (fabs(curPos.y) >= HEIGHT))
        return VERT_COLLIDE;

    return 0;
}

void spherePos(sphere *allSpheres, GLfloat vel, LinkedList particleHistory) 
{

    double dt = 0.5;
    add_position(&particleHistory, allSpheres[0].position);

    for (int i = 0; i < sphereTotal; i++) {
        if ((isCollide(allSpheres[i].position) & BOTH_COLLIDE)) {
            printf("COLLISION");
            allSpheres[i].position.x += -1*allSpheres[i].velocity.x*dt;
            allSpheres[i].position.y += -1*allSpheres[i].velocity.y*dt;
            allSpheres[i].position.z += allSpheres[i].velocity.z*dt;
        }
        else if ((isCollide(allSpheres[i].position) & HOR_COLLIDE)) {
            allSpheres[i].position.x += -1*allSpheres[i].velocity.x*dt;
            allSpheres[i].position.y += allSpheres[i].velocity.y*dt;
            allSpheres[i].position.z += allSpheres[i].velocity.z*dt;
        }
        else if ((isCollide(allSpheres[i].position) & VERT_COLLIDE)) {
            allSpheres[i].position.x += allSpheres[i].velocity.x*dt;
            allSpheres[i].position.y += -1*allSpheres[i].velocity.y*dt;
            allSpheres[i].position.z += allSpheres[i].velocity.z*dt;
        }
        else {
            allSpheres[i].velocity.x = (-1 + 2*drand48())*vel;
            allSpheres[i].velocity.y = (-1 + 2*drand48())*vel;
            allSpheres[i].velocity.z = (-1 + 2*drand48())*vel;
            allSpheres[i].position.x += allSpheres[i].velocity.x*dt;
            allSpheres[i].position.y += allSpheres[i].velocity.y*dt;
            allSpheres[i].position.z += allSpheres[i].velocity.z*dt;
        }
    }
    add_position(&particleHistory, allSpheres[0].position);
    
    
}

void drawSphere(sphere *allSpheres)
{
    int i = 0;
    
    for (i = 0; i < sphereTotal; i++) {
        glColor3f(allSpheres[i].color[0], allSpheres[i].color[1], allSpheres[i].color[2]);
        glTranslatef(allSpheres[i].position.x, allSpheres[i].position.y, allSpheres[i].position.z);
        gluDisk(gluNewQuadric(), 0.0, allSpheres[i].radius, 20, 10);
        glutSolidSphere(allSpheres->radius, 10, 20);
        glTranslatef(-allSpheres[i].position.x, -allSpheres[i].position.y, allSpheres[i].position.z);
    }
}

sphere *initializeSphere(int numSpheres)
{
    int i;
    sphere *spheresGL = (sphere *)malloc(sizeof(sphere)*numSpheres);

    spheresGL[0].color[0] = 1.0;
    spheresGL[0].radius = 5;
    

    for (i=1; i < numSpheres; i++) {
        spheresGL[i].color[0] = 0.0;
        spheresGL[i].color[1] = 0.0;
        spheresGL[i].color[2] = 0.0;

        spheresGL[i].radius = 2;
        spheresGL[i].position.x = (float) drand48() * 30;
        spheresGL[i].position.y = (float) drand48() * 30;
        spheresGL[i].position.z = (float) drand48() * 30;
    }
    sphereTotal = numSpheres;
    return spheresGL;

}