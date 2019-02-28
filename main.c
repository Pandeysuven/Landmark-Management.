#include "setup.h"
#include "Functions.h"

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char options_main[][50] = {"Search by name", "Search by area", "Add/Modify records" };
    char options[20][50];
    LANDMARK lmark;
    int j = 1, num_options = 0,  selected_landmark;
    char *input_name = calloc(50, sizeof(char));
    char *temp = calloc(50, sizeof(char));

    setup();     //checks for folder, sets title and maximizes output window

    while (1)
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
        case 1:
            system("cls");
            for (j = 1, num_options = 0; (temp = GetLandmarkType(j)) != NULL; j++)      //List of landmark in options[]
            {
                if (temp[strlen(temp)-1] == '\n')
                    temp[strlen(temp)-1] = '\0';
                strcpy(options[num_options], temp);
                num_options++;
            }
            selected_landmark = GetMenuSelection("Search options", options, num_options);
            if (selected_landmark == 0)
                break;
            StrInput(input_name, "Input name of landmark: ", 50);
            fflush(stdin);
            system("cls");
            lmark = search_by_name(input_name, selected_landmark);
            if (!strcmp(lmark.name, "null") )
            {
                printf("Cannot find landmark.\n");
            }
            else
            {
                DisplayLandmark(lmark);
            }
            printf("Press q to exit.\nPress any key to return to main menu.");
            int input = getch();
            if (input == KEY_Q_CAPITAL || input == KEY_Q_SMALL)
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
            if (input == KEY_Q_CAPITAL || input == KEY_Q_SMALL)
            {
                free(input_name);
                free(temp);
                exit(0);
            }
            break;
        case 3:
            modify_records();
            printf("Press q to exit.\nPress any key to return to main menu.");
            input = getch();
            if (input == KEY_Q_CAPITAL || input == KEY_Q_SMALL)
            {
                free(input_name);
                free(temp);
                exit(0);
            }
            break;
        }
    }
    return 0;


}
