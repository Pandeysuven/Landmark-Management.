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
    int len = strlen(name);
    char *temp = (char*) calloc(len+2, sizeof(char));
    strcpy(temp,name);
    strcat(temp,"\n");
    FILE *fptr = fopen(".\\Data\\Landmark_list.txt", "a");
    if (fptr == NULL)
    {
        printf("Cannot find list of landmarks.");
        free(temp);
        exit(1);
    }
    if (!SearchLandmarkType(name))
    {
        fputs(temp,fptr);
    }
    else
    {
        printf("Landmark %s already exists.\n", name);
        free(temp);
        fclose(fptr);
        return 1;
    }
    free(temp);
    fclose(fptr);
    return 0;
}

char* GetLandmarkType(int sn)
{
    int sz = 25;
    char *temp = (char*) calloc(sz, sizeof(char));
    int line = 1;
    FILE *fptr = fopen(".\\Data\\Landmark_list.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot find list of landmarks.\n");
        exit(1);
    }
    while ( !feof(fptr) )
    {
        temp=fgets(temp,sz,fptr);
        if (line < sn)
        {
            if (temp[strlen(temp)-1] != '\n' && !feof(fptr))
            {
                printf("Line is too long.\n");
                return 1;
            }
            else
                line++;
        }
        else
        {
            fclose(fptr);
            return temp;
        }
    }
    free(temp);
    fclose(fptr);
    return NULL;
}

int SearchLandmarkType(char* input)
{
    char *input_name = calloc(strlen(input)+2, sizeof(char));
    strcpy(input_name, input);
    strcat(input_name, "\n");
    int sz = 25;
    char *temp = (char*) calloc(sz, sizeof(char));
    FILE *fptr = fopen(".\\Data\\Landmark_list.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot find list of landmarks.\n");
        free(input_name);
        free(temp);
        exit(1);
    }
    while ( fgets(temp,sz,fptr) )
    {
        if (temp[strlen(temp)-1] != '\n')
        {
            free(input_name);
            free(temp);
            fclose(fptr);
            printf("Line is too long.");
            return 1;
        }
        if (strcmpi(input_name, temp) == 0)
        {
            free(input_name);
            free(temp);
            fclose(fptr);
            return 1;
        }

    }
    free(input_name);
    free(temp);
    fclose(fptr);
    return 0;
}




char* GetAreaName(int sn)
{
    int sz = 25;
    char *temp = (char*) calloc(sz, sizeof(char));
    int line = 1;
    FILE *fptr = fopen(".\\Data\\Area_list.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot find list of landmarks.\n");
        exit(1);
    }
    while ( !feof(fptr) )
    {
        temp=fgets(temp,sz,fptr);
        if (line < sn)
        {
            if (temp[strlen(temp)-1] != '\n' && !feof(fptr))
            {

                fseek(fptr, -strlen(temp), SEEK_CUR);
                sz += 10;
                realloc(temp, sz);
                continue;
            }
            else
                line++;
        }
        else
        {
            fclose(fptr);
            if (feof(fptr) && temp[strlen(temp)-1] != '\n')
                strcat(temp, "\n");
            return temp;
        }
    }
    free(temp);
    fclose(fptr);
    return NULL;
}






