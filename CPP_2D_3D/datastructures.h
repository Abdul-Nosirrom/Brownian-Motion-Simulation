#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct  vector3
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3;

class LinkedList {

    typedef struct Node {
        vec3 pos;
        struct Node* next;
    } Node;

    Node* head;
    Node* tail;

    public:
        LinkedList();

        void draw_path();
        void add_position(vec3);
        
        ~LinkedList();

};
