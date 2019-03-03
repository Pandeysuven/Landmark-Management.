#include <stdio.h>
#include "Functions.h"
#define OPTION_NEXT 0
int search_by_area()
{
    int j = 1, num_options = 0, selected_area, num_areas = 0, num_lmark_type = 0;
    while(strcmp(GetAreaName(j++), "") != STR_MATCH)
        num_areas++;
    j = 1;
    while(strcmp(GetLandmarkType(j++), "") != STR_MATCH)
        num_lmark_type++;
    char options[num_areas+2][50];
    LANDMARK lmark;

    for(j = 1; strcmp(GetAreaName(j), "") != STR_MATCH; j++)      //Sets area name to array of options
    {
        char area[50];
        strcpy(area, GetAreaName(j));
        strcpy(options[num_options++], area);
    }
    selected_area = GetMenuSelection("Select area", options, num_options);

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
            return -1;
        }
        num_options = 0;
        if(j!= num_lmark_type)
        {
            strcpy(options[num_options++], "Next");
        }
        while(!feof(fpfile))
        {
            int fread_rtn = fread(&lmark, sizeof(lmark), 1, fpfile);
            if(strcmp(lmark.name, "") != 0 && fread_rtn == 1)
                strcpy(options[num_options++], lmark.name);
        }
        if(j > 1)
        {
            strcpy(options[num_options++], "Previous");
        }
        selected_lmark = GetMenuSelection(GetLandmarkType(j), options, num_options);
        if(selected_lmark == 1 && j != num_lmark_type)
            continue;
        else if(selected_lmark == '\b' || (selected_lmark == num_options && j > 1))
        {
            j -= 2;
            continue;
        }
        if(j != num_lmark_type)
        {
            selected_lmark--; //Since all except last have "Next" as first option
        }
        fseek(fpfile, sizeof(LANDMARK) * (selected_lmark-1), SEEK_SET);
        if(fread(&lmark, sizeof(lmark), 1, fpfile) == 1)
        {
            DisplayLandmark(lmark);
        }
        break;


    }
    return 0;



}
