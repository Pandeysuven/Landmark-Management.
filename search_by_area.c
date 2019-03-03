#include <stdio.h>
#include "Functions.h"
#define OPTION_NEXT 0
int search_by_area()
{
    int j, num_options = 0, selected_area;
    char options[NUM_AREAS+2][50];
    LANDMARK lmark;

    for(j = 1; strcmp(GetAreaName(j), "") != STR_MATCH; j++)      //Sets area name to array of options
    {
        char area[50];
        strcpy(area, GetAreaName(j));
        strcpy(options[num_options++], area);
    }
    selected_area = GetMenuSelection("Select area", options, num_options);

    //char *temp = calloc(25, sizeof(char));
    for(j = 1; strcmp(GetLandmarkType(j), "") != STR_MATCH; j++)      //List of landmark in options[]
    {
        FILE *fpfile;
        char file[50];
        int selected_lmark;
        sprintf(file, ".\\Data\\Area%d\\%s.bin", selected_area, GetLandmarkType(j));
        fpfile = fopen(file, "rb");
        if(fpfile == NULL)
        {
            printf("Error opening file %s", file);
            //free(temp);
            return 1;
        }

        strcpy(options[0], "Next");
        num_options = 1;
        while(!feof(fpfile))
        {
            int fread_rtn = fread(&lmark, sizeof(lmark), 1, fpfile);
            if(strcmp(lmark.name, "") != 0 && fread_rtn == 1)
                strcpy(options[num_options++], lmark.name);
        }
        if(j > 1)
            strcpy(options[num_options++], "Previous");
        selected_lmark = GetMenuSelection(GetLandmarkType(j), options, num_options) - 1;
        if(selected_lmark == 0)
            continue;
        else if(selected_lmark == '\b' || (selected_lmark == num_options && j > 1))
        {
            j -= 1;
            continue;
        }
        fseek(fpfile, sizeof(LANDMARK) * (selected_lmark-1), SEEK_SET);
        fread(&lmark, sizeof(lmark), 1, fpfile);
        DisplayLandmark(lmark);
        break;


    }
    return 0;



}
