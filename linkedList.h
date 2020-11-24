#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#ifndef LINKED_LIST
#define LINKED_LIST
/*
    LINKED LIST ADT
    this header follows the following convention:
    The list head node is called LIST.
    all other nodes are NODE.
    this is a generic singly linked list.
    createList() will create and return a head node.
    append(param1, param2) will add a node at the end, the node is passed in param2 and the list is passed in param1.
*/

typedef struct node
{
    struct node *next;
    void *data;
} NODE;

typedef struct
{
    int count;
    NODE *head;
    NODE *rear;
} LIST;

LIST *createList()
{
    LIST *newList = (LIST *)malloc(sizeof(LIST));
    if (!newList)
    {
        boldRed();
        printf("There was an error creating a list!");
        reset();
    }
    newList->count = 0;
    newList->head = NULL;
    newList->rear = NULL;
    return newList;
}
NODE *getNode(void *data)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = (NODE *)data;
    newNode->next = NULL;
    return newNode;
}

void append(LIST *lp, void *data)
{
    NODE *newNode = getNode(data);
    if (lp->head == NULL)
    {
        lp->head = lp->rear = newNode;
        return;
    }
    lp->rear->next = newNode;
    lp->rear = newNode; // updating the metadata
}

#endif