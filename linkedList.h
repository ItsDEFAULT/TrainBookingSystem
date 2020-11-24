#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "trains.h"
#ifndef LINKED_LIST
#define LINKED_LIST
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
    newNode->data = data;
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
    lp->rear->next = (NODE *)data;
}

void display(LIST lp)
{
    NODE *temp;
    temp = lp.head;
    while (temp != NULL)
    {
        TRAIN *t = (TRAIN *)temp->data;
        printf("Train:%s", t->name);
        temp = temp->next;
    }
}

#endif