
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct vector2 {
    GLfloat x;
    GLfloat y;
} vec2;

typedef struct color {
    GLfloat r;
    GLfloat g;
} color;

typedef struct sphere {
    vec2 position;
    GLfloat radius;
    GLfloat color[3];
} sphere;

void spherePos(sphere *, GLfloat vel);

void drawSphere(sphere *);

sphere* initializeSphere(int numSpheres);