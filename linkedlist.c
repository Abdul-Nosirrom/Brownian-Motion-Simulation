#include "linkedlist.h"

LinkedList initialize_list() 
{
    LinkedList motionData;
    motionData.head = (Node *)malloc(sizeof(Node));
    motionData.size = 0;
    
    return motionData;
}

void add_position(LinkedList motionData, vec2 position) 
{
    int i;
    Node* trav = motionData.head;
    Node* newData = (Node *)malloc(sizeof(Node));
    newData->pos = position;

    while(trav->next != NULL) {
        trav = trav->next;
    }

    trav->next = newData;

}

void destroy_list(LinkedList toDestroy)
{
    Node* trav = toDestroy.head;
    while(trav != NULL) {
        free(trav);
        trav = trav->next;
    }
    toDestroy.size = 0;
}

void draw_path()
{
    Node* trav = particleHistory.head;
    int i;
    
    glBegin(GL_LINE_SMOOTH);
        glColor3f(0.0,1.0,0.0);
        while(trav != NULL) {
            glVertex2f(trav->pos.x, trav->pos.y, 0.0);
        }


}