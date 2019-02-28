//Function setup
//Sets title of output window
//Clears output window
#include "setup.h"
#include "Functions.h"
#include <ctype.h>
#include <limits.h>

void setup()
{
    CreateFolder();
    StripfromFile(".\\Data\\Landmark_list.txt"); //
    system("title Landmark Management System");
    system("cls");
}

int CreateFolder()
{
    int j;
    char *temp = malloc(sizeof(char) * 50);
    FILE *fptr;
    char str_i[3];
    char *lmark = (char*) malloc(100 * sizeof(char));
    char *landmark_file = (char*) malloc(50 * sizeof(char));
    for (int i = 1; i <= NUM_AREAS; i++)
    {
        char folder[50] = ".\\Data\\Area", mkdirs[50] = "IF NOT EXIST ";

        sprintf(str_i, "%d", i);
        strcat(folder, str_i);

        strcat(mkdirs, folder);
        strcat(mkdirs, " mkdir ");
        strcat(mkdirs, folder);
        system(mkdirs);

        j = 1;
        while( (temp = GetLandmarkType(j++) ) )
        {
            strcpy(lmark, temp);
            lmark[strlen(temp)-1] = '\0';
            strcpy(landmark_file, folder);
            strcat(landmark_file, "\\");
            strcat(lmark, ".txt");
            strcat(landmark_file, lmark);

            fptr = fopen(landmark_file, "r");
            if (fptr==NULL)
            {
                fptr = fopen(landmark_file, "w");
            }
            fclose(fptr);

        }
    }
    free(lmark);
    free(landmark_file);
    free(temp);
    return 0;
}

int StripfromFile(char *file_path)
{
    FILE *finput, *ftemp;

    finput = fopen(file_path, "r");
    ftemp = fopen("temp.txt", "w");

    if (finput == NULL || ftemp == NULL)
        return 1;

    int line_sz = 20;
    char *line = calloc(line_sz, sizeof(char));
    if (line == NULL)
    {
        printf("Memory allocation error.");
        return 1;
    }
    while (fgets(line, line_sz, finput))
    {
        if (!feof(finput) && line[strlen(line)-1] != '\n')
        {
            line_sz *= 2;
            line = realloc(line, line_sz);
            fseek(finput, -strlen(line), SEEK_CUR);
            continue;
        }
        if (strcmp(line, "\n") )
        {
            fputs(line, ftemp);
        }
    }
    fclose(ftemp);
    fclose(finput);
    finput = fopen(file_path, "w");
    ftemp = fopen("temp.txt", "r");
    while (fgets(line, line_sz, ftemp))
    {
        fputs(line, finput);
    }

    free(line);
    fclose(ftemp);
    fclose(finput);
    remove("temp.txt");
    return 0;
}


int StrInput(char *input_string, char *msg, int sz)
{

    int c, len = 0, err = 0;
    fflush(stdin);
    while(1)
    {
        len = 0;
        printf("%s", msg);
        while ( (c=getchar()) != '\n')
        {
            if (isalpha(c) || isspace(c))
            {
                if (len < sz-1)
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
        if (err == 1)
        {
            continue;
        }
        if (len == 0)
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

unsigned long long int ULLInput(int input_lim)
{
    int c, len = 0;
    char *input_string = calloc(input_lim+1, sizeof(char));
    fflush(stdin);
    while(1)
    {
        len = 0;
        printf("Enter a number: ");
        while ( (c=getchar()) != '\n' && len <=input_lim)
        {
            if (isdigit(c))
            {
                input_string[len++] = c;
            }
            else
            {
                printf("Please enter number.\n");
                fflush(stdin);
                continue;
            }
        }
        if (len == 0)
        {
            printf("Input is empty.\n");
            fflush(stdin);
            continue;
        }
        else
            break;
    }
    input_string[len] = '\0';

    unsigned long long int a;
    a = strtoull(input_string, NULL, 10);
    if (a == 0 || a == ULONG_LONG_MAX)
    {
        printf("Invalid number.\n");
        return 0;
    }
    return a;
}
