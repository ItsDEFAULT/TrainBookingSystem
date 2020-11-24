#include <stdio.h>
#include "users.h"

#ifndef TRAINS
#define TRAINS

typedef struct // this is the head node with all the metadata
{
    int passengerCapacity;
    int totalDistance;
    int id;
    int totalStations;
    float pricePerKm;
    char name[20];
} TRAIN;

typedef struct station // the rest of the nodes
{
    char cityName[20];
    struct station *next;
    float distance;
} STATION;

#endif