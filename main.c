#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Functions.h"

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char options_main[][50] = {"Search by name", "Search by area", "Add/Modify records" };
    char options[50][50];
    LANDMARK lmark;
    int j = 1, num_options = 0,  selected_landmark;
    char *input_name = calloc(50, sizeof(char));
    if(input_name == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", errno, strerror(errno));
        ErrorDialogue("Memory allocation error", errmsg, 0);
        exit(-1);
    }
    char *temp = calloc(50, sizeof(char));
    if(temp == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", errno, strerror(errno));
        ErrorDialogue("Memory allocation error", errmsg, 0);
        exit(-1);
    }
    setup();     //checks for folder, sets title and maximizes output window

    while(1)
    {
        system("cls");
        int MenuSelection = GetMenuSelection("Main Menu", options_main, 3);    //Displays menu and returns input
        SetConsoleTextAttribute(hConsole, 7);
        system("cls");

        switch(MenuSelection)
        {
        case 0:
            free(input_name);
            free(temp);
            return 0;

        case '\b':
            free(input_name);
            free(temp);
            return 0;

        case 1:

            for(j = 1, num_options = 0; strcmp((temp = GetLandmarkType(j)), "") != STR_MATCH; j++)       //List of landmark in options[]
            {
                if(num_options > 50)
                {
                    char errmsg[50];
                    sprintf(errmsg, "Error %d while retrieving types of landmark.\n%s", E2BIG, strerror(E2BIG));
                    ErrorDialogue("Error", errmsg, 0);
                    exit(-1);
                }
                strcpy(options[num_options], temp);
                num_options++;
            }
            selected_landmark = GetMenuSelection("Select type of landmark", options, num_options);
            if(selected_landmark == 0 || selected_landmark == '\b')
                break;

            if(StrInput(input_name, "Input name of landmark: ", 50) == EOF)
                break;
            fflush(stdin);
            system("cls");

            if(search_by_name(input_name, selected_landmark) == NOT_FOUND)
            {
                printf("Cannot find landmark.\n");
            }
            else
            {
                FILE *fpsearch = fopen(".\\Temp\\search_result.bin", "rb");
                if(fpsearch == NULL)
                {
                    char errmsg[50];
                    sprintf(errmsg, "Error %d: Error in Search_list.bin.\n%s", ENOFILE, strerror(ENOFILE));
                    ErrorDialogue("File error", errmsg, 0);
                    exit(-1);
                }
                while(fread(&lmark, sizeof(LANDMARK), 1, fpsearch))
                {
                    DisplayLandmark(lmark);
                    printf("\n");
                }
            }

            printf("Press q to exit.\nPress any key to return to main menu.");
            int input = getch();
            if(input == KEY_Q_CAPITAL || input == KEY_Q_SMALL)
            {
                free(input_name);
                free(temp);
                exit(0);
            }
            break;

        case 2:
            search_by_area();

            printf("Press q to exit.\nPress any key to return to main menu.");
            input = getch();

            if(input == KEY_Q_CAPITAL || input == KEY_Q_SMALL)
            {
                free(input_name);
                free(temp);
                exit(0);
            }
            break;

        case 3:
            modify_records();
            break;
        }
    }
    return 0;


}
