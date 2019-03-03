/*
	//functions.c
	//contains functions to modify landmark details
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

int CreateLandmarkType(char *name)
{
    char *lmark_type = (char*) calloc(strlen(name) + 2, sizeof(char));
    if(lmark_type == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
        ErrorDialogue("Memory allocation error", errmsg, 0);
        exit(-1);
    }

    FILE *fptr = fopen(".\\Data\\Landmark_list.txt", "r");
    if(fptr == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in Landmark_list.txt.\n%s", ENOFILE, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        free(lmark_type);
        return -1;
    }
    freopen(".\\Data\\Landmark_list.txt", "a", fptr);

    sprintf(lmark_type, "%s\n", name);
    if(SearchLandmarkType(name) == NOT_FOUND)
    {
        fputs(lmark_type, fptr);
        fclose(fptr);
        free(lmark_type);
        CreateFolder();
        return 0;
    }
    else
    {
        printf("Landmark %s already exists.\n", name);
        free(lmark_type);
        fclose(fptr);
        return 1;
    }
}

char* GetLandmarkType(int sn)
{
    if(sn < 0)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s to GetLandmarkType( ).", EINVAL, strerror(EINVAL));
        ErrorDialogue("Error", errmsg, 0);
        return "";
    }
    int sz = 25;
    int line = 1;
    FILE *fptr = fopen(".\\Data\\Landmark_list.txt", "r");
    if(fptr == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in Landmark_list.txt.\n%s", ENOFILE, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        return "";
    }

    while(!feof(fptr))
    {
        char *temp = (char*) calloc(sz, sizeof(char));
        if(temp == NULL)
        {
            char errmsg[50];
            sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
            ErrorDialogue("Memory allocation error", errmsg, 0);
            exit(-1);
        }
        fgets(temp, sz, fptr);
        if(line < sn)
        {
            if(temp[strlen(temp) - 1] != '\n' && !feof(fptr))
            {
                if(sz > 200)
                {
                    char errmsg[50];
                    sprintf(errmsg, "Line %d of landmark list is too long..", line);
                    ErrorDialogue("Error", errmsg, 0);
                    return "";
                }

                fseek(fptr, -strlen(temp), SEEK_CUR);
                sz += 10;
                realloc(temp, sz);
                continue;
            }
            else
                line++;
        }
        else if(line == sn)
        {
            fclose(fptr);
            if(temp[strlen(temp)-1] == '\n')
                temp[strlen(temp)-1] = '\0';
            if(strcmp(temp, "") == STR_MATCH)
            {
                free(temp);
                return "";
            }
            else
                return temp;
        }

    }
    fclose(fptr);
    return "";
}

int SearchLandmarkType(char* input)
{
    char *input_name = calloc(strlen(input) + 2, sizeof(char));
    if(input_name == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
        ErrorDialogue("Memory allocation error", errmsg, 0);
        exit(-1);
    }
    sprintf(input_name, "%s\n", input);
    int sz = 50;
    char *temp = (char*) calloc(sz, sizeof(char));
    if(temp == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
        ErrorDialogue("Memory allocation error", errmsg, 0);
        exit(-1);
    }

    FILE *fptr = fopen(".\\Data\\Landmark_list.txt", "r");
    if(fptr == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in Landmark_list.txt.\n%s", ENOFILE, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        free(input_name);
        free(temp);
        return EOF;
    }

    while(fgets(temp, sz, fptr))
    {
        if(temp[strlen(temp) - 1] != '\n' && !feof(fptr))
        {
            free(input_name);
            free(temp);
            fclose(fptr);
            printf("Line is too long.");
            return EOF;
        }

        if(strcmpi(input_name, temp) == 0)
        {
            free(input_name);
            free(temp);
            fclose(fptr);
            return FOUND;
        }

    }

    free(input_name);
    free(temp);
    fclose(fptr);
    return NOT_FOUND;
}




char* GetAreaName(int sn)
{
    if(sn < 0)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s to GetAreaname( ).", EINVAL, strerror(EINVAL));
        ErrorDialogue("Error", errmsg, 0);
        return "";
    }
    int sz = 50;
    int line = 1;
    FILE *fptr = fopen(".\\Data\\Area_list.txt", "r");

    if(fptr == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in Area_list.txt.\n%s", ENOFILE, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        return "";
    }

    while(!feof(fptr))
    {
        char *temp = (char*) calloc(sz, sizeof(char));
        if(temp == NULL)
        {
            char errmsg[50];
            sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
            ErrorDialogue("Memory allocation error", errmsg, 0);
            exit(-1);
        }
        fgets(temp, sz, fptr);
        if(line < sn)
        {
            if(temp[strlen(temp) - 1] != '\n' && !feof(fptr))
            {
                if(sz > 200)
                {
                    char errmsg[50];
                    sprintf(errmsg, "Line %d of landmark list is too long..", line);
                    ErrorDialogue("Error", errmsg, 0);
                    return "";
                }

                fseek(fptr, -strlen(temp), SEEK_CUR);
                sz += 10;
                realloc(temp, sz);
                continue;
            }
            else
                line++;
        }
        else if(line == sn)
        {
            fclose(fptr);
            if(temp[strlen(temp)-1] == '\n')
                temp[strlen(temp)-1] = '\0';
            if(strcmp(temp, "") == STR_MATCH)
            {
                free(temp);
                return "";
            }
            else
                return temp;
        }
        else
        {
            free(temp);
            fclose(fptr);
            return "";
        }
    }
    return "";


}






