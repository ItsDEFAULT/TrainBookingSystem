#include "users.h"
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
            printf("\n1.Login\n2.Sign Up\n3.Exit\n");
            printf("Enter your choice:");
            scanf("%d", &ch);
            fflush(stdin);
            switch (ch)
            {
            case 1:
                system("cls");
                currentUser = login();
                if (currentUser)
                    printf("\nLogin Successful! Welcome!");
                else
                    printf("\nUser not found!\n");
                break;
            case 2:
                system("cls");
                res = new_register();
                if (!res)
                    printf("Account Successfully Created!!");
                else
                    printf("There was an error....please try again!");
                break;
            case 3:
                system("cls");
                printf("Thank you for using the \"Benkyo Train Reservation Software\"!!");
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
