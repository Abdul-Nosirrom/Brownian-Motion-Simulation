
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define LENGTH 50.0
#define HEIGHT 50.0

#define VERT_COLLIDE 1
#define HOR_COLLIDE 2
#define BOTH_COLLIDE 4

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
    vec2 velocity;
    GLfloat radius;
    GLfloat color[3];
} sphere;

void spherePos(sphere *, GLfloat vel);

void drawSphere(sphere *);

sphere* initializeSphere(int numSpheres);

int isCollide(vec2);