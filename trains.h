#include <stdio.h>
#include "users.h"
#include "linkedList.h"

#ifndef TRAINS
#define TRAINS

typedef struct // this is the head node with all the metadata
{
    int passengerCapacity;
    float totalDistance;
    int id;
    int totalStations;
    float pricePerKm;
    char name[20];
} TRAIN;

typedef struct station // the rest of the nodes
{
    char cityName[20];
    float distance;
    // struct station *next;
} STATION;

void addStation(LIST *newList, TRAIN *newTrainNode); // adds a station to the train
void remStation(LIST *lp);                           // removes a station from the train
void saveTrain(LIST *lp);                            // saves the train to a flie
void displayTrain(LIST *lp);                         // displays a given train's details
LIST *loadTrain(char *path);                         // returns a train object, searching by its path

void displayTrain(LIST *lp)
{
    TRAIN *tPtr = (TRAIN *)lp->head->data; // the head node
    printf("Train ID: %d\n", tPtr->id);
    printf("Train: %s\n", tPtr->name);
    printf("Passenger Capacity: %d\n", tPtr->passengerCapacity);
    printf("Price Per Km: %f\n", tPtr->pricePerKm);
    printf("Total Distance: %f\n", tPtr->totalDistance);
    printf("Total Stations: %d\n", tPtr->totalStations);

    printf("The Train Visits the following stations: \n");

    STATION *tempStation;
    NODE *temp = lp->head->next; // the 1st station
    while (temp != NULL)
    {
        tempStation = (STATION *)temp->data;
        printf("->Station Name: %s,  ", tempStation->cityName);
        printf("Distance from previous Station: %f\n", tempStation->distance);
        temp = temp->next;
    }
}

void newTrain()
{
    int ch;
    LIST *newList = createList();
    TRAIN *newTrainNode = (TRAIN *)malloc(sizeof(TRAIN));
    newTrainNode->totalDistance = 0;
    newTrainNode->totalStations = 0;
    printf("\nEnter the Train's Name: ");
    fgets(newTrainNode->name, 20, stdin);
    clean(newTrainNode->name);
    printf("\nEnter the Train ID: ");
    scanf("%d", &newTrainNode->id);
    printf("\nEnter the Train's Passenger Capacity: ");
    scanf("%d", &newTrainNode->passengerCapacity);
    printf("\nEnter the Train's Price Per Kilometer: ");
    scanf("%f", &newTrainNode->pricePerKm);
    NODE *newNode = getNode(newTrainNode);
    newList->head = newList->rear = newNode; // added the head node with all the info above
    while (1)
    {
        printf("\n1.Add a Station\n2.Remove a Station\n3.Save\n4.Display Train\n5.Back\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            addStation(newList, newTrainNode);
            break;
        case 2:
            remStation(newList);
            break;
        case 3:
            saveTrain(newList);
            break;
        case 4:
            displayTrain(newList);
            break;
        case 5:
            return;
        default:
            printf("Invalid Input!!!");

            break;
        }
    }
}

void addStation(LIST *newList, TRAIN *newTrainNode)
{
    STATION *newStation = (STATION *)malloc(sizeof(STATION));
    printf("Enter the Station's name:");
    fflush(stdin);
    fgets(newStation->cityName, 20, stdin);
    clean(newStation->cityName);
    fflush(stdin);
    printf("Enter the distance from the previous station: ");
    scanf("%f", &newStation->distance);
    append(newList, newStation); // appended the new station to the list
    newTrainNode->totalStations++;
    newTrainNode->totalDistance += newStation->distance;
    printf("Successfully added the station!");
}

void remStation(LIST *lp)
{
    char rem[20];
    printf("Enter the Station to be removed: ");
    fflush(stdin);
    fgets(rem, 20, stdin);
    fflush(stdin);
    clean(rem);
    TRAIN *t = (TRAIN *)lp->head->data;
    NODE *temp = lp->head->next; // points to 1st station
    NODE *prev = temp;
    while (temp)
    {
        STATION *tempStation = (STATION *)temp->data;
        if (!strcmp(rem, tempStation->cityName)) // if name matches
        {
            if (prev == temp) // the 1st station
            {
                lp->head->next = temp->next;
                t->totalDistance -= tempStation->distance;
                tempStation->distance = 0;
                t->totalStations--;
                return;
            }
            prev->next = temp->next;

            t->totalStations--;
            t->totalDistance -= tempStation->distance;
            free(tempStation);
            free(temp);
            printf("Successfully removed %s station", rem);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Did not find %s station", rem);
}

void saveTrain(LIST *lp)
{
    TRAIN *t = (TRAIN *)lp->head->data;
    NODE *temp = (NODE *)lp->head->next;
    STATION *s;

    char trainName[20];
    strcpy(trainName, t->name);
    strcat(trainName, ".txt");
    char fileName[30] = "./trains/";
    strcat(fileName, trainName);
    FILE *allTrains = fopen("allTrains.txt", "a");
    fprintf(allTrains, "%s\n", fileName);
    fclose(allTrains);
    FILE *newTrain = fopen(fileName, "w");
    /*
        the train data is written here, if a train with same name 
        was previously existing, it will be overwritten.

        the file structure after writing the data will be:
        1st line: all of the train meta data (comma separated)
        every line after this represents 1 station with the distance 
        wrt prev station
     */
    fprintf(newTrain, "%s,%d,%d,%d,%f,%f\n", t->name, t->id, t->passengerCapacity, t->totalStations, t->totalDistance, t->pricePerKm);
    while (temp)
    {
        s = (STATION *)temp->data;
        fprintf(newTrain, "%s,%f\n", s->cityName, s->distance);
        temp = temp->next;
    }
    fclose(newTrain);
}

LIST *loadTrain(char *path)
{
    LIST *train = createList();
    TRAIN *meta = (TRAIN *)malloc(sizeof(TRAIN));
    FILE *trainFile = fopen(path, "r");
    if (!trainFile) // train not found
        return NULL;
    char line[100], word[30];
    fgets(line, 100, trainFile);
    int k = 0, i = 0, commaCount = 0; // i index of a line, k index of a word
    while (line[i] != '\0')
    {
        if (commaCount == 0) // train name
        {
            while (line[i] != ',')
                word[k++] = line[i++];
            word[k] = '\0';
            commaCount++;
            strcpy(meta->name, word);
        }
        if (commaCount == 1) // train id
        {
            k = 0;
            i++;
            while (line[i] != ',')
                word[k++] = line[i++];
            word[k] = '\0';
            commaCount++;
            int id = atoi(word);
            meta->id = id;
        }
        if (commaCount == 2) // passenger capacity
        {
            k = 0;
            i++;
            while (line[i] != ',')
                word[k++] = line[i++];
            word[k] = '\0';
            int capacity = atoi(word);
            meta->passengerCapacity = capacity;
            commaCount++;
        }
        if (commaCount == 3) // total stations
        {
            k = 0;
            i++;
            while (line[i] != ',')
                word[k++] = line[i++];
            word[k] = '\0';
            int stations = atoi(word);
            meta->totalStations = stations;
            commaCount++;
        }
        if (commaCount == 4) // total distance
        {
            k = 0;
            i++;
            while (line[i] != ',')
                word[k++] = line[i++];
            word[k] = '\0';
            float dist = atof(word);
            meta->totalDistance = dist;
            commaCount++;
        }
        if (commaCount == 5) // price per kilometer
        {
            k = 0;
            i++;
            while (line[i] != '\n')
                word[k++] = line[i++];
            word[k] = '\0';
            float price = atof(word);
            meta->pricePerKm = price; // all the meta data is now copied into the meta head object
            commaCount++;
            break;
        }
    }
    append(train, meta);
    // to copy the stations
    while (fgets(line, 100, trainFile))
    {
        STATION *newStation = (STATION *)malloc(sizeof(STATION));
        i = 0;
        k = 0;
        while (line[i] != ',')
            word[k++] = line[i++];
        word[k] = '\0';
        strcpy(newStation->cityName, word);
        i++;
        k = 0;
        while (line[i] != '\n')
            word[k++] = line[i++];
        word[k] = '\0';
        float dist = atof(word);
        newStation->distance = dist;
        append(train, newStation); // adds this node to the linked list
    }
    displayTrain(train);
    fclose(trainFile);
    return train;
}

#endif