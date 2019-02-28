#include "Functions.h"
#include "Places.h"   //

int modify_records()
{
    char options_main[][50] = { "Add a new landmark", "Edit existing landmark", "Add new type of landmark"};
    char *inputString = (char*) calloc(100, sizeof(inputString));
    int j = 1, num_options = 0, selected_landmark, selected_area;
    int selected_option = GetMenuSelection("Add/Modify Landmark", options_main, 3);
    if (selected_option == 0)
        return 0;

    switch(selected_option)
    {
    case 1:
    {
        system("cls");
        char options[20][50];
        char file[50] = ".\\Data\\Area", str_num[3];
        char *temp = malloc(sizeof(char) * 50);
        for (j = 1; GetAreaName(j) != NULL; j++)
        {
            char area[50];
            strcpy(area, GetAreaName(j));
            strcpy(options[num_options++], area);
        }
        selected_area = GetMenuSelection("Select Area", options, num_options);
        if (selected_area == 0)
        {
            free(inputString);
            return 0;
        }
        sprintf(str_num, "%d", selected_area);
        strcat(file, str_num);
        num_options = 0;
        j = 1;
        {
            while( (temp = GetLandmarkType(j++)) != NULL )
            {
                int len = strlen(temp);
                char lmark[len];
                strcpy(lmark, temp);
                lmark[len-1] = '\0';
                strcpy(options[num_options], lmark);
                num_options++;
                system("cls");
            }
            selected_landmark = GetMenuSelection("Select Landmark Type", options, num_options);
            if (selected_landmark == 0)
                return 0;
        }
        system("cls");

        strcat(file, "\\");
        temp = GetLandmarkType(selected_landmark);
        temp[strlen(temp)-1] = '\0';
        strcat(file, temp);
        strcat(file, ".txt");
        AddLandmark(file, selected_area, selected_landmark);
        free(temp);
        break;
    }
    case 2:
        system("cls");
        char   options[][50] = {"Edit existing landmark\n", "Delete landmark"};
        int selected_edit_option = GetMenuSelection("Edit Landmark", options, 2);
        system("cls");
        StrInput(inputString, "Enter landmark name: ", 100);
        fflush(stdin);
        LANDMARK lmark;
        for (int i = 1; GetLandmarkType(i) != NULL; i++)
        {
            lmark = search_by_name(inputString, i);
            if (lmark.name != NULL )
            {
                char file[50] = ".\\Data\\Area";
                char str_area[3];
                sprintf(str_area, "%d", lmark.area);
                strcat(file, str_area);
                strcat(file, "\\");
                strcat(file, GetLandmarkType(i));
                file[strlen(file)-1] = '\0';
                strcat(file, ".txt");
                int area = lmark.area;
                if (selected_edit_option == 1)
                {
                    DeleteLandmark(file, lmark.name);
                    AddLandmark(file, area, i);
                }
                if (selected_edit_option == 2)
                {
                    DeleteLandmark(file, lmark.name);
                }

            }
        }

        break;
    case 3:
        system("cls");
        GoToXY(0,0);
        StrInput(inputString, "Input name of landmark type: ", 100);
        fflush(stdin);
        if (SearchLandmarkType(inputString))
        {
            printf("Landmark %s already exists.\n", inputString);
        }
        else
        {
            CreateLandmarkType(inputString);
            printf("Successfully created new Landmark type.\n");

        }
        break;
    }
    free(inputString);
    return 0;



}


