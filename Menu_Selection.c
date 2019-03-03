#include "Functions.h" // for create table
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int GetMenuSelection(char *heading, char (*options)[50], int num_options)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int selected_option = 1;          //input saves input selected option saves option 1,2 or 3
    int x = -12, y = ((-(num_options / 2)));                       //deviation from middle of screen
    if(num_options > 99 || num_options < 1)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s.", E2BIG, strerror(E2BIG));
        ErrorDialogue("Error", errmsg, 0);
        exit(-1);
    }

    //creates table and displays option
    CreateTable(40, num_options + 8);
    GoToMiddle(x, y - 2);
    SetConsoleTextAttribute(hConsole, RED);
    printf("%s", heading);
    SetConsoleTextAttribute(hConsole, WHITE);

    for(int i = 0; i < num_options; i++)
    {
        GoToMiddle(x, y + i);
        printf("%2d. %s", i + 1, *(options + i));
    }
    GoToMiddle(x - 2, y + num_options + 1);
    printf("Choose one of the above: ");

    //Sets console attribute to highlighted, moves cursor to option 1 and reprints option
    SetConsoleTextAttribute(hConsole, HIGHLIGHTED);
    GoToMiddle(x, y);
    printf(" 1. %s", *(options + 0));

    GoToMiddle(x + 23, y + num_options + 1);

    while(1)
    {
    	int input;
        SetConsoleTextAttribute(hConsole, 7);
        fflush(stdin);
        input = getch();
        if(input == ENTERKEY)
        {
            system("cls");
            return selected_option;
        }
        else if(input == KEY_Q_CAPITAL || 	input == KEY_Q_SMALL)
        {
            system("cls");
            exit(0);
        }
        else if(input == '\b')
        {
            system("cls");
            return '\b';
        }
        else if(input == 27)
        {
            system("cls");
            return 0;
        }
        else if(input >= 48 && input <= 57)
        {
            if(num_options < 10)
            {
                if((input-48) > num_options)
                {
                    ErrorDialogue("Invalid option.", "Selected option is out of range.", 0);
                    continue;
                }
                else
				{
					system("cls");
					return input - 48;
				}
            }
            else if(num_options >= 10 && input < 100)
            {
                selected_option = input - 48;
				GoToMiddle(x + 23, y + num_options + 1);
				printf("%d", selected_option);
                fflush(stdin);
                input = getch();
                if(input == 13)
                    return selected_option;
                selected_option = (selected_option * 10) + (input - 48);

                if(selected_option > num_options)
                {
                    ErrorDialogue("Invalid option.", "Selected option is out of range.", 0);
                    continue;
                }
                system("cls");
                return selected_option;
            }
        }
        fflush(stdin);
        input = getch();
        switch(input)
        {
        case ARROW_DOWN:
            SetConsoleTextAttribute(hConsole, 7);
            GoToMiddle(x, y + selected_option - 1);
            printf("%2d. %s", selected_option, *(options + selected_option - 1));

            if(selected_option == num_options)      //if last option is selected
            {
                selected_option = 1;
            }
            else
            {
                selected_option++;
            }

            SetConsoleTextAttribute(hConsole, 135);
            GoToMiddle(x, y + selected_option - 1);

            printf("%2d. %s", selected_option, *(options + selected_option - 1));
            GoToMiddle(x + 23, y + num_options + 1);

            break;

        case ARROW_UP:
            SetConsoleTextAttribute(hConsole, 7);
            GoToMiddle(x, y + selected_option - 1);
            printf("%2d. %s", selected_option, *(options + selected_option - 1));

            if(selected_option == 1)
            {
                selected_option = num_options;
            }
            else
            {
                selected_option--;
            }

            SetConsoleTextAttribute(hConsole, 135);
            GoToMiddle(x, y + selected_option - 1);
            printf("%2d. %s", selected_option, *(options + selected_option - 1));
            GoToMiddle(x + 23, y + num_options + 1);
            break;




        }
    }

    fflush(stdin);
    return selected_option;
}
