#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef USERS
#define USERS

typedef struct
{
    char username[20];
    char password[10];
    char email[30];
    char gender;
    int age;
} USER;

void clean(char *s) // removes the trailing \n thats inserted in fgets
{
    int n = strlen(s);
    s[n - 1] = '\0';
}

USER *search(char *username)
{
    FILE *userFile = fopen("users.txt", "r");
    int i;
    char userString[100];
    USER *usr = (USER *)malloc(sizeof(USER)); // dynamic allocation because we need the object after the function execution
    char password[10];
    char email[30];
    char gender, ageStr[3];
    int age, commaCount = 0, k = 0;
    while (fgets(userString, 100, userFile)) // gets a line per loop and stores it in userString
    {
        int n = strlen(username);
        for (i = 0; i < n; ++i)
        {
            if (username[i] != userString[i])
                break;
        }
        if (i == n && userString[i] == ',') // user found!!!
        {
            strcpy(usr->username, username);
            int j = 0;
            while (userString[j] != ',')
                j++;
            commaCount++;
            j++;                 // moves from ','  to next char
            if (commaCount == 1) // read the password
            {
                k = 0;
                while (userString[j] != ',')
                    password[k++] = userString[j++];
                password[k] = '\0';
                commaCount++;
                strcpy(usr->password, password);
            }
            if (commaCount == 2) // read the email
            {
                k = 0;
                j++; // moves from ','  to next char
                while (userString[j] != ',')
                    email[k++] = userString[j++];
                email[k] = '\0';
                commaCount++;
                strcpy(usr->email, email);
            }
            if (commaCount == 3) // read the age
            {
                k = 0;
                j++; // moves from ','  to next char
                while (userString[j] != ',')
                    ageStr[k++] = userString[j++];
                ageStr[k] = '\0';
                age = atoi(ageStr);
                commaCount++;
                usr->age = age;
            }
            if (commaCount == 4)
            {
                j++; // moves from ','  to next char
                gender = userString[j];
                usr->gender = gender;
                fclose(userFile);
                return usr; // all data is written in this object
            }
        }
        // printf("%s", userString);
    }
    return NULL;
    fclose(userFile);
}

USER *login() // login to an existing account
{
    char user[20], pwd[10];
    USER *usr = (USER *)malloc(sizeof(USER));
    printf("\nEnter your Username:");
    fgets(user, 20, stdin);
    clean(user);
    usr = search(user);
    printf("\nEnter your Password:");
    fgets(pwd, 10, stdin);
    clean(pwd);
    if (!usr)
        return NULL;
    if (!strcmp(pwd, usr->password))
        return usr; // successful login
    printf("Wrong Password!");
    return NULL;
}

int new_register() // new account
{
    FILE *userFile;
    char user[20], pwd[10], cnfPwd[10], email[30], gender;
    int age;
    userFile = fopen("users.txt", "a");
    if (userFile == NULL)
    {
        printf("Error Opening Users File.");
        return 1;
    }
    // Username input and validation
    printf("Enter your username:");
    fgets(user, 21, stdin);
    if (strlen(user) <= 3 || strlen(user) == 20)
    {
        printf("Your username must be more than 3 characters and less than 18 characters!!!\n");
        return 1;
    }
    clean(user);
    if (search(user))
    {
        printf("Username Taken!!");
        return 1;
    }

    // Username vaidation ends

    // Password input and validation
    printf("Enter your password:");
    fgets(pwd, 11, stdin);
    while (strlen(pwd) <= 3 || strlen(pwd) == 10)
    {
        printf("Your Password Must be more than 3 characters and less than 10 characters!!!\n");
        return 1;
    }
    printf("Confirm your password:");
    fgets(cnfPwd, 10, stdin);
    while (strcmp(pwd, cnfPwd))
    {
        printf("Passwords Do not Match!!!\n");
        return 1;
    }
    clean(pwd);

    // Password validation ends

    // Email input
    printf("Enter your email:");
    fgets(email, 31, stdin);
    if (strlen(email) == 30 || strlen(email) <= 5)
    {
        printf("Your email must be longer than 5 characters and less than 30 characters!!!\n");
        return 1;
    }
    clean(email);

    // Email input end
    fflush(stdin); // cleans the buffer for scanf
    // Age input
    printf("Enter your age:");
    scanf("%d", &age);
    if (age < 18)
    {
        printf("You must be atleast 18 years old to make an account!!!\n");
        return 1;
    }

    // Age input end
    fflush(stdin); // cleans the buffer for scanf
    // Gender input
    printf("Enter your gender (M/F):");
    scanf("%c", &gender);
    while (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f')
    {
        printf("\nInput can either be 'M' or 'F'!!!");
        printf("\nEnter your gender (M/F):");
        scanf("%c", &gender);
    }

    // Gender input end

    // write to file
    fprintf(userFile, "%s,", user);
    fprintf(userFile, "%s,", pwd);
    fprintf(userFile, "%s,", email);
    fprintf(userFile, "%d,", age);
    fprintf(userFile, "%c\n", gender);

    // Account Successfull created
    fclose(userFile);
    return 0;
}

#endif