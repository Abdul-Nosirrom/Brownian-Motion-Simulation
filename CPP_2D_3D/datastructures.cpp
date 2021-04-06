#include "datastructures.h"

LinkedList::LinkedList()
{
    LinkedList motionData;
    head = new Node;
    tail = new Node;

    head->next = tail;
    tail->next = NULL;

    head->pos.x = 0;
    head->pos.y = 0;
    head->pos.z = 0;

    tail->pos.x = 0;
    tail->pos.y = 0;
    tail->pos.z = 0;
    
}

void LinkedList::add_position(vec3 newPos)
{
    Node* newVec = new Node;

    newVec->pos.x = newPos.x;
    newVec->pos.y = newPos.y;
    newVec->pos.z = newPos.z;

    Node* trav = head;

    while(trav->next != NULL) {
        trav = trav->next;
    }

    // Draw the new position here (faster probably?)

    trav->next = newVec;
}

LinkedList::~LinkedList()
{
    Node* trav = head;
    while(trav != NULL) {
        delete trav;
        trav = trav->next;
    }
}