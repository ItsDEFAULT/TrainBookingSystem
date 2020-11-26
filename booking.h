#include <stdio.h>
#include <string.h>
#include "users.h"
#include "trains.h"
#include "linkedList.h"
#ifndef BOOKING
#define BOOKING

void findTrains(char *src, char *dest)
{
    FILE *allTrains = fopen("allTrains.txt", "r");
    char path[50];
    int flag1, flag2;
    while (fgets(path, 50, allTrains))
    {
        flag1 = flag2 = 0;
        clean(path);
        LIST *tempTrain = loadTrain(path);
        NODE *temp = (NODE *)tempTrain->head->next;
        while (temp) // traversing the list
        {
            STATION *tempStation = (STATION *)temp->data;
            if (!strcasecmp(src, tempStation->cityName)) // when source city matches
                flag1 = 1;
            if (!strcasecmp(dest, tempStation->cityName)) // when destination city matches
                flag2 = 1;

            if (flag1 && flag2) // if a train has both source and destination
            {
                displayTrain(tempTrain);
                break;
            }
            temp = temp->next;
        }
    }
    fclose(allTrains);
}

void book()
{
    char source[20], dest[20];
    fflush(stdin);
    printf("From: ");
    fgets(source, 20, stdin);
    clean(source);
    fflush(stdin);
    printf("To: ");
    fgets(dest, 20, stdin);
    clean(dest);
    findTrains(source, dest);
}

#endif