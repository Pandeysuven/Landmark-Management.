#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "Functions.h"
#include "Places.h"

int search_by_name(char *input_name,  int lmark_type)
{
    int j = 1, bool_found = FALSE;
    LANDMARK lmark;
    FILE *fp_search_result;
    fp_search_result = fopen(".\\Temp\\search_result.bin", "wb");
    if(fp_search_result == NULL)
    {

        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", errno, strerror(errno));
        ErrorDialogue("Error", errmsg, 0);

    }
    for(j = 1; j <= NUM_AREAS; j++)
    {
        FILE *fptr;
        char file[50];
        sprintf(file, ".\\Data\\Area%d\\%s.bin", j, GetLandmarkType(lmark_type));
        fptr = fopen(file, "rb");

        if(fptr == NULL)
        {
            char errmsg[70];
            sprintf(errmsg, "Error %d: Error in %s.\n%s", ENOFILE, file, strerror(ENOFILE));
            ErrorDialogue("File error", errmsg, 0);
            exit(-1);
        }

        while(!feof(fptr))
        {
            strcpy(lmark.name, "\0");
            int fread_rtn = fread(&lmark, sizeof(lmark), 1, fptr);
            if(strcmp(lmark.name, "") == 0 || fread_rtn != 1)
                break;
            char lmark_name_lower[50], input_name_lower[50];
            strcpy(lmark_name_lower, lmark.name);
            strcpy(input_name_lower, input_name);
            _strlwr(lmark_name_lower);
            _strlwr(input_name_lower);
            if(strstr(lmark_name_lower, input_name_lower) != NULL)
            {
            	bool_found = TRUE;
                int fwrite_return = fwrite(&lmark, sizeof(LANDMARK), 1, fp_search_result);

                if (fwrite_return == 1)
                {
                    bool_found == FOUND;
                }
            }
        }
    }
    fclose(fp_search_result);
    return bool_found;
}
