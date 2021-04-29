#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

struct  vec3
{
    GLfloat x;
    GLfloat y;
    GLfloat z;

    vec3 operator-(vec3 &obj);
    vec3 operator+(vec3 &obj);
    vec3 operator*(GLfloat &obj);
    vec3 normalized();
    float dot(vec3 obj);
    float length();

};

