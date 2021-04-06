#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct vector3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3;

typedef struct Node {
    vec3 pos;
    struct Node* next;
} Node;

typedef struct LinkedList {
    int size;
    Node* head;
} LinkedList;

LinkedList initialize_list();
void draw_path(LinkedList*);
void add_position(LinkedList*, vec3);
void destroy_list(LinkedList*);

