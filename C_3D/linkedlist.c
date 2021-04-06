#include "linkedlist.h"

LinkedList initialize_list() 
{
    LinkedList motionData;
    motionData.head = (Node *)malloc(sizeof(Node));
    motionData.size = 0;
    motionData.head->next = NULL;
    motionData.head->pos.x = 0;
    motionData.head->pos.y = 0;
    motionData.head->pos.z = 0;
    
    return motionData;
}

void add_position(LinkedList *motionData, vec3 position) 
{
    Node* trav = motionData->head;
    motionData->size++;

    while(trav->next != NULL) {
        trav = trav->next;
    }

    trav->next = (Node *)malloc(sizeof(Node));
    trav->next->pos = position;
    trav->next->next = NULL;

}

void destroy_list(LinkedList *toDestroy)
{
    Node* trav = toDestroy->head;
    while(trav != NULL) {
        free(trav);
        trav = trav->next;
    }
    toDestroy->size = 0;
}

void draw_path(LinkedList *particleHistory)
{
    Node* trav = particleHistory->head;
    
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0,1.0,0.0);
        while(trav != NULL) {
            glVertex3f(trav->pos.x, trav->pos.y, trav->pos.z);
            trav = trav->next;
        }
    glEnd();


}