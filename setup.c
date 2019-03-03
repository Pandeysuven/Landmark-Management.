//Function setup
//Sets title of output window
//Clears output window
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Functions.h"
#include <ctype.h>
#include <limits.h>

void setup()
{
    system("title Landmark Management System");
    StripfromFile(".\\Data\\Landmark_list.txt");   //
    StripfromFile(".\\Data\\Area_list.txt");
    CreateFolder();
    system("cls");
}

int CreateFolder()
{
    FILE *fptr;
    int num_area = 0;
    for(int i = 1; strcmp(GetAreaName(i), "") != STR_MATCH; i++)
    {
        num_area++;
    }

    for(int i = 1; i <= num_area; i++)
    {
        char mkdirs[50];
        sprintf(mkdirs, "IF NOT EXIST .\\Data\\Area%d mkdir .\\Data\\Area%d", i, i);
        system(mkdirs);

        char landmark_file[75];

        for(int j = 1; (strcmp(GetLandmarkType(j), "") != STR_MATCH); j++)
        {
            sprintf(landmark_file, ".\\Data\\Area%d\\%s.bin", i, GetLandmarkType(j));
            fptr = fopen(landmark_file, "rb");
            if(fptr == NULL)
            {
                fptr = fopen(landmark_file, "wb");
            }
            fclose(fptr);
        }
    }
    return 0;
}

int StripfromFile(char *file_path)
{
    FILE *finput, *ftemp;
    if(strstr(file_path, ".txt") != 0)
    {
        finput =fopen(file_path, "r");
        if(finput == NULL)
        {
            char errmsg[50];
            sprintf(errmsg, "Error %d: %s\n%s", ENOFILE, file_path, strerror(ENOFILE));
            ErrorDialogue("File error", errmsg, 0);
            exit(-1);
        }
        ftemp = fopen("Strip_temp.txt", "w");
    }
    else if(strstr(file_path, ".bin") != 0)
    {
        finput = fopen(file_path, "rb");
        if(finput == NULL)
        {
            char errmsg[50];
            sprintf(errmsg, "Error %d: %s\n%s", ENOFILE, file_path, strerror(ENOFILE));
            ErrorDialogue("File error", errmsg, 0);
            exit(-1);
        }
        ftemp = fopen("Strip_temp.bin", "wb");
    }
    else
    {
        char errmsg[50];
        sprintf(errmsg, "Unknown file extension: %s", file_path);
        ErrorDialogue("File error", errmsg, 0);
        return -1;
    }
    if(ftemp == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s\n%s", ENOFILE, "", strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        fclose(finput);
        exit(-1);
    }

    int line_sz = 50;
    char *line = calloc(line_sz, sizeof(char));
    if(line == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
        ErrorDialogue("Memory allocation error", errmsg, 0);
        fclose(finput);
        fclose(ftemp);
        exit(-1);
    }

    while(fgets(line, line_sz, finput))
    {
        if(!feof(finput) && line[strlen(line) - 1] != '\n')
        {
            if(line_sz>200)
            {
                char errmsg[50];
                sprintf(errmsg, "Error %d: Error in %s.\n%s", EFBIG, file_path, strerror(EFBIG));
                ErrorDialogue("File error", errmsg, 0);
                free(line);
                fclose(finput);
                fclose(ftemp);
                exit(-1);
            }
            line_sz *= 2;
            if((realloc(line, line_sz) == NULL))
            {
                char errmsg[50];
                sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
                ErrorDialogue("Memory allocation error", errmsg, 0);
                free(line);
                fclose(finput);
                fclose(ftemp);
                exit(-1);
            }
            fseek(finput, -strlen(line), SEEK_CUR);
            continue;
        }

        if(strcmp(line, "\n") != STR_MATCH)
        {
            fputs(line, ftemp);
        }
    }
    fclose(finput);
    fclose(ftemp);
    if(strstr(file_path, ".txt") != 0)
    {
        finput = fopen(file_path, "w");
        ftemp = fopen(".\\Strip_temp.txt", "r");
    }
    else
    {
        finput = fopen(file_path, "wb");
        ftemp = fopen(".\\Strip_temp.bin", "rb");
    }
    if(finput == NULL || ftemp == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in file.\n%s", errno, strerror(errno));
        ErrorDialogue("File error", errmsg, 0);
        free(line);
        exit(-1);
    }
    while(fgets(line, line_sz, ftemp))
    {
        fputs(line, finput);
	}

    free(line);
    fclose(ftemp);
    fclose(finput);
    return 0;
}


int StrInput(char *input_string, char *msg, int sz)
{

    int len = 0, err = 0;
    fflush(stdin);

    while(1)
    {
        int c;
        len = 0;
        printf("%s", msg);

        while((c = getchar()) != '\n')
        {
            if(c == EOF)
                return EOF;
            if(isalpha(c) || isspace(c))
            {
                if(len < sz - 1)
                {
                    err = 0;
                    input_string[len++] = c;
                }
                else
                {
                    printf("Input string too long.\n");
                    fflush(stdin);
                    err = 1;
                    break;
                }
            }
            else
            {
                printf("Invalid characters in input.\n");
                fflush(stdin);
                err = 1;
                break;

            }
        }

        if(err == 1)
        {
            continue;
        }

        if(len == 0)
        {
            printf("Input string is empty.\n");
            fflush(stdin);
            continue;
        }

        break;
    }

    input_string[len] = '\0';
    return len;
}

char* PhoneInput(char *msg)
{
    int len, limit = 10, pos;
    char *input_string = calloc(limit+1, sizeof(char));
    if(input_string == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
        ErrorDialogue("Memory allocation error", errmsg, 0);
        exit(-1);
    }

    while(1)
    {
        int c;
        len = 0;
        pos = 0;
        printf("%s", msg);
        fflush(stdin);
        while((c = getchar()) != '\n' && len <= limit)
        {
            if(c == '-' && input_string[0] == '0' && input_string[1] == '1')
            {
                input_string[pos++] = c;
            }
            else if(isdigit(c) || c == '-')
            {
                if(c != '-')
                {
                    input_string[pos++] = c;
                    len++;
                }
            }
            else
            {
                printf("Please enter valid number.\n");
                fflush(stdin);
                continue;
            }
        }
        if(len == 0)
        {
            printf("Input is empty.\n");
            fflush(stdin);
            continue;
        }
        else
            break;
    }
    input_string[len] = '\0';

    return input_string;
}

int ErrorDialogue(char *heading, char *error, int type)
{
    int option;
    if(type == 0)
    {
        option = MB_OK;
    }
    else
    {
        option = type;
    }
    int msgrtn = MessageBox(NULL, error, heading, option | MB_ICONEXCLAMATION);
    return msgrtn;
}
