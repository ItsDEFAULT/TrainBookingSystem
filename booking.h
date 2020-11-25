#include <stdio.h>
#include "users.h"
#include "trains.h"
#include "linkedList.h"
#ifndef BOOKING
#define BOOKING

void findTrains(char *src, char *dest)
{
    FILE *allTrains = fopen("allTrains.txt", "r");
    FILE *tempTrain;
    char path[50];
    while (fgets(path, 50, allTrains))
    {
        tempTrain = fopen(path, "r");

        fclose(tempTrain);
    }
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
}

#endif