
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct vector2 {
    GLfloat x;
    GLfloat y;
} vec2;

void spherePos(vec2 *currPos, GLfloat vel);

void drawSphere(vec2 currPos, GLboolean isLarge);

vec2 initializeSphere();