#include "users.h"
#include "colors.h"
#include "trains.h"
#include "booking.h"
USER *currentUser = NULL;
int main()
{
    int ch, res;
    while (1)
    {
        while (!currentUser) // if no user is logged in
        {
            boldYellow();
            printf("\n1.LOGIN\n2.SIGNUP\n3.EXIT\n");
            boldMagenta();
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
                    printf("\nLogin Successful! Welcome!\n");
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
                {
                    boldGreen();
                    printf("Account Successfully Created!!");
                    reset();
                }
                else
                {
                    boldRed();
                    printf("\nThere was an error....please try again!");
                    reset();
                }
                break;
            case 3:
                system("cls");
                boldCyan();
                printf("\nThank you for using the \"Benkyo Train Reservation Software\"!!\n");
                reset();
                return 0;

            default:
                system("cls");
                boldRed();
                printf("Invalid Input!!!");
                reset();
                break;
            }
        }
        while (currentUser) //  when user logs in
        {
            boldYellow();
            printf("\n1.Book a Ticket\n2.Cancel a Ticket\n3.View your account details\n4.Create New Train\n5.Show all trains\n6.Logout\n");
            boldMagenta();
            printf("Enter your choice:");
            boldBlue();
            scanf("%d", &ch);
            reset();
            fflush(stdin);
            switch (ch)
            {
            case 1:
                book();
                break;
            case 3:
                system("cls");
                boldYellow();
                printf("\nName: ");
                boldCyan();
                printf("%s\n", currentUser->username);
                boldYellow();
                printf("Password: ");
                boldCyan();
                printf("%s\n", currentUser->password);
                boldYellow();
                printf("Email: ");
                boldCyan();
                printf("%s\n", currentUser->email);
                boldYellow();
                printf("Age: ");
                boldCyan();
                printf("%d\n", currentUser->age);
                boldYellow();
                printf("Gender: ");
                boldCyan();
                printf("%c\n", currentUser->gender);
                reset();

                break;

            case 4:
                newTrain();
                break;
            case 5:
                showAll();
                break;
            case 6:
                system("cls");
                currentUser = NULL;
                break;
            default:
                system("cls");
                boldRed();
                printf("Invalid Input!");
                reset();
                break;
            }
            break;
        }
    }
    return 0;
}
