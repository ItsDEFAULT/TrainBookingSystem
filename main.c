#include "users.h"
#include "colors.h"
USER *currentUser = NULL;
int main()
{
    // if (new_register())
    //     printf("There was an error registering....please rectify and try again!");

    // USER *usr = login("Shreehari");
    // if (usr)
    // printf("Login Successful!");
    // printf("%s\n%s\n%s\n%d\n%c", usr->username, usr->password, usr->email, usr->age, usr->gender);
    // else
    //     printf("User not found!");

    int ch, res;
    while (1)
    {
        while (!currentUser) // if no user is logged in
        {
            boldYellow();
            printf("\n1.LOGIN\n2.SIGNUP\n3.EXIT\n");
            printf("Enter your choice: ");
            reset();
            boldBlue();
            scanf("%d", &ch);
            reset();
            fflush(stdin);
            switch (ch)
            {
            case 1:
                system("cls");
                currentUser = login();
                if (currentUser)
                {
                    boldGreen();
                    printf("\nLogin Successful! Welcome!");
                    reset();
                }
                else
                {
                    boldRed();
                    printf("\nUser not found!\n");
                    reset();
                }
                break;
            case 2:
                system("cls");
                res = new_register();
                if (!res)
                    printf("Account Successfully Created!!");
                else
                    printf("\nThere was an error....please try again!");
                break;
            case 3:
                system("cls");
                boldCyan();
                printf("Thank you for using the \"Benkyo Train Reservation Software\"!!");
                reset();
                return 0;

            default:
                system("cls");
                printf("Invalid Input!!!");
                break;
            }
        }
        while (currentUser) //  when user logs in
        {
            printf("\n1.Book a Ticket\n2.Cancel a Ticket\n3.Logout\n");
            printf("Enter your choice:");
            scanf("%d", &ch);
            fflush(stdin);
            switch (ch)
            {
            case 3:
                system("cls");
                currentUser = NULL;
                break;
            default:
                system("cls");
                printf("Invalid Input!");
                break;
            }
            break;
        }
    }
    return 0;
}
