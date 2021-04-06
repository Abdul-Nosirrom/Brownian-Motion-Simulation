#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct vector2 {
    GLfloat x;
    GLfloat y;
} vec2;

typedef struct Node {
    vec2 pos;
    struct Node* next;
} Node;

typedef struct LinkedList {
    int size;
    Node* head;
} LinkedList;

LinkedList initialize_list();
void draw_path(LinkedList*);
void add_position(LinkedList*, vec2);
void destroy_list(LinkedList*);

