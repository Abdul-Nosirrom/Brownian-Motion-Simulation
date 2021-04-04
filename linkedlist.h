#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "spheres.h"

typedef struct Node {
    vec2 pos;
    struct Node* next;
} Node;

typedef struct LinkedList {
    int size;
    Node* head;
} LinkedList;

LinkedList particleHistory;

LinkedList initialize_list();
void draw_path();
void add_position(LinkedList, vec2);
void destroy_list(LinkedList);