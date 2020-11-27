#include <stdio.h>
#include <string.h>
#include "users.h"
#include "trains.h"
#include "linkedList.h"
#ifndef BOOKING
#define BOOKING
int writeTicket(float, int, char *, char *); // writes the ticket to file
void displayTicket(int);                     // displays ticket by its id

int findTrains(char *src, char *dest)
{
    FILE *allTrains = fopen("allTrains.txt", "r");
    int found = 0;
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
                found++;
                break;
            }
            temp = temp->next;
        }
        deleteList(tempTrain);
    }
    fclose(allTrains);
    return found;
}

void book()
{
    char *source = (char *)malloc(sizeof(char) * 20);
    char *dest = (char *)malloc(sizeof(char) * 20);
    char choice[20];
    fflush(stdin);
    boldYellow();
    printf("From: ");
    boldBlue();
    fgets(source, 20, stdin);
    clean(source);
    fflush(stdin);
    boldYellow();
    printf("To: ");
    boldBlue();
    fgets(dest, 20, stdin);
    reset();
    clean(dest);
    if (findTrains(source, dest))
    {
        printf("Enter the train you want to take: ");
        fflush(stdin);
        fgets(choice, 20, stdin);
        clean(choice);
        trainPath(choice); // stores path of the train in "choice" variable
        LIST *train = loadTrain(choice);
        if (!train)
        {
            boldRed();
            printf("Train not found!!!");
            reset();
            return;
        }
        int numberOfTickets = 0, flag = 0; // flag to see if we are in between the stations the user has input
        float ticketPrice, distance = 0, totalPrice;
        NODE *temp = train->head->next; // loads the 1st station
        while (temp)                    // traversing the stations
        {
            STATION *tempStation = temp->data;
            if (!strcasecmp(source, tempStation->cityName)) // if source matches
                flag = 1;
            if (flag == 1)
                distance += tempStation->distance;
            if (!strcasecmp(dest, tempStation->cityName)) // dest reached
            {
                if (flag == 0)
                {
                    boldRed();
                    printf("Sorry...This train does not have reverse journey yet!");
                    reset();
                    return;
                }
                flag = 0;
            }
            temp = temp->next;
        }
        TRAIN *meta = train->head->data;
        ticketPrice = meta->pricePerKm * distance;
        fflush(stdin);
        boldYellow();
        printf("Enter the number of tickets you want to book: ");
        boldBlue();
        scanf("%d", &numberOfTickets);
        if (numberOfTickets <= meta->passengerCapacity) // only provide tickets if train has that passenger capacity
        {
            totalPrice = ticketPrice * numberOfTickets;
            boldGreen();
            printf("Yay! Found %d free seats!\nYour total price: %f\nWould you like to book the ticket(s)? (Y/N):", numberOfTickets, totalPrice);
            reset();
            char c;
            fflush(stdin);
            boldBlue();
            scanf("%c", &c);
            if (c == 'Y' || c == 'y')
            {
                int id = writeTicket(totalPrice, numberOfTickets, source, dest);
                deleteList(train);
                boldGreen();
                printf("Ticket(s) booked successfully!\nYour ticket ID is: %d\nHAPPY JOURNEY!", id);
                reset();
            }
            else
            {
                deleteList(train);
                boldCyan();
                printf("Thankyou for using the Benkyo TRS! Have a good day!");
                reset();
                return;
            }
        }
        else
        {
            deleteList(train);
            boldRed();
            printf("Sorry....the train does not have %d seats.", numberOfTickets);
            reset();
            return;
        }
    }
    else
    {
        boldRed();
        printf("Sorry.. no trains available for this route");
        reset();
    }
}

int writeTicket(float price, int numberOfTickets, char *source, char *dest)
{
    int id;
    char num[20];
    FILE *idFile = fopen("./tickets/id.txt", "r");
    fgets(num, 20, idFile);
    id = atoi(num) + 1;
    fclose(idFile);
    idFile = fopen("./tickets/id.txt", "w");
    fprintf(idFile, "%d", id);
    fclose(idFile);
    // writing the ticket
    // the ticket will be written in this format:
    // id,name,source,destination,number of seats booked
    char path[50] = "./tickets/";
    idFile = fopen("./tickets/id.txt", "r");
    fgets(num, 20, idFile);
    fclose(idFile);
    strcat(num, ".txt");
    strcat(path, num);
    FILE *ticket = fopen(path, "w");
    fprintf(ticket, "%d,%s,%s,%s,%d", id, currentUser->username, source, dest, numberOfTickets);
    fclose(ticket);
    return id;
}

void displayTicket(int id)
{
    char path[50] = "./tickets/";
    char num[20];
    itoa(id, num, 10);
    strcat(num, ".txt");
    strcat(path, num);
    FILE *ticket = fopen(path, "r");
    if (!ticket)
    {
        boldRed();
        printf("Ticket not found!");
        reset();
        return;
    }
    char name[20];
    char source[20];
    char dest[20];
    int commaCount = 0;
    int i = 0, j = 0;
    char line[100];
    fgets(line, 100, ticket);
    while (commaCount == 0)
    {
        if (line[i++] == ',')
            commaCount++;
    }
    while (commaCount == 1)
    {
        name[j++] = line[i++];
        if (line[i] == ',')
            commaCount++;
    }
    name[j] = '\0';
    j = 0;
    i++;
    while (commaCount == 2)
    {
        source[j++] = line[i++];
        if (line[i] == ',')
            commaCount++;
    }
    source[j] = '\0';
    j = 0;
    i++;
    while (commaCount == 3)
    {
        dest[j++] = line[i++];
        if (line[i] == ',')
            commaCount++;
    }
    dest[j] = '\0';
    j = 0;
    i++;
    while (commaCount == 4)
    {
        num[j++] = line[i++];
        if (line[i] == '\0')
            break;
    }
    num[j] = '\0';
    int numberOfTickets = atoi(num);

    fclose(ticket);
    boldMagenta();
    printf("\n\n------------------------------------------------------------------------\n");
    boldCyan();
    printf("------------------------------TICKET DETAILS----------------------------\n");
    boldMagenta();
    printf("------------------------------------------------------------------------\n\n");
    reset();
    boldYellow();
    printf("\tName: ");
    boldBlue();
    printf("%s\n", name);
    boldYellow();
    printf("\n\tTicket ID: ");
    boldBlue();
    printf("%d\n", id);
    boldYellow();
    printf("\n\tFrom: ");
    boldBlue();
    printf("%s\n", source);
    boldYellow();
    printf("\n\tTo: ");
    boldBlue();
    printf("%s\n", dest);
    boldYellow();
    printf("\n\tNumber of seats booked: ");
    boldBlue();
    printf("%d\n", numberOfTickets);
    boldMagenta();
    printf("\n------------------------------------------------------------------------\n");
    boldCyan();
    printf("------------------------------TICKET DETAILS----------------------------\n");
    boldMagenta();
    printf("------------------------------------------------------------------------\n\n");
    reset();
}

#endif