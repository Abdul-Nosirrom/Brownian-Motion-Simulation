#include "spheres.h"


void spherePos(vec2 *currPos, GLfloat vel) 
{

    double dt = 0.1;
    currPos->x += vel*dt;
    currPos->y += vel*dt;
    
}

void drawSphere(vec2 currPos, GLboolean isLarge) 
{
    
    int radius;
    if (isLarge) {
        radius = 1.5;
        glColor3f(1.0,0.0,0.0);
    }
    else {
        radius = 0.5;
        glColor3f(1.0,1.0,1.0);
    }
    glTranslatef(currPos.x, currPos.y ,0);
    gluDisk(gluNewQuadric(), 0.0, 2.0, 20, 10);
    glTranslatef(-currPos.x, -currPos.y, 0);
}

vec2 initializeSphere()
{
    vec2 sphere;
    sphere.x = 0; sphere.y = 0;
    return sphere;
}