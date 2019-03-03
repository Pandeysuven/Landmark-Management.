#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "Functions.h"
#include "Places.h"
#include <limits.h>

int AddLandmark(char *file_location, int area, int lmark_type)
{
    FILE *fptr = fopen(file_location, "rb");
    if(fptr == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in %s.\n%s", ENOFILE, file_location, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        return -1;
    }
    if(freopen(file_location, "ab", fptr) == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in %s.\n%s", ENOFILE, file_location, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        return -1;
    }
    LANDMARK lmark, lmark_b;
    if(StrInput(lmark.name, "Enter name of landmark: ", 50) == EOF)
    {
        fclose(fptr);
        return 1;
    }
    fflush(stdin);

    if(search_by_name(lmark.name, lmark_type) == FOUND)
    {
        char err_msg[130];
        int msgbox_return;
        sprintf(err_msg, "Landmark %s already exists. Do you want to add another landmark with same name?", lmark.name);
        msgbox_return = ErrorDialogue("Name Conflict", err_msg, MB_YESNO);
        switch(msgbox_return)
        {
        case IDYES:
            break;
        case IDNO:
            fclose(fptr);
            return 1;
        }
    }
    lmark.area = area;
    lmark.type = lmark_type;
    if(StrInput(lmark.address, "Enter address of landmark: ", 50) == EOF)
    {
        fclose(fptr);
        return 1;
    }
    FILE *fp_search = fopen(".\\Temp\\search_result.bin", "rb");
    if(fp_search == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in Search_result.bin.\n%s", errno, strerror(errno));
        ErrorDialogue("File error", errmsg, 0);
        fclose(fptr);
        return -1;
    }
    while(fread(&lmark_b, sizeof(lmark_b), 1, fp_search))
    {
        if(strstr(lmark_b.address, lmark.address) != 0 && search_by_name(lmark.name, lmark_type) == FOUND)
        {
            ErrorDialogue(0, "Cannot have two landmarks with same name and address.", 0);
            fclose(fptr);
            return 1;
        }
    }
    fflush(stdin);
    strcpy(lmark.phone, PhoneInput("Enter phone number: "));
    fflush(stdin);

    int write_rtn = fwrite(&lmark, sizeof(lmark), 1, fptr);
    if(write_rtn == 1)
    {
        printf("Successfully added landmark.\n");
        fclose(fptr);
        return 0;
    }
    return 1;
}

void DisplayLandmark(LANDMARK lmark)
{
    printf("Name: %s\n", lmark.name);
    printf("Address: %s\n", lmark.address);
    printf("Phone number: %s\n", lmark.phone);
}

int DeleteLandmark(char *file_path, char *lmark_name)
{
    FILE *finput, *ftemp;
    LANDMARK lmark;
    P_LANDMARK plmark = &lmark;

    finput = fopen(file_path, "rb");
    if(finput == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in %s.\n%s", ENOFILE, file_path, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        return EOF;
    }
    ftemp = fopen(".\\Temp\\temp_delete.bin", "wb");
    if(ftemp == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d in DeleteLandmark: Error in %s.\n%s", ENOFILE, "temp file", strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        fclose(finput);
        return EOF;
    }


    while(!feof(finput))
    {
        int fread_rtn = fread(plmark, sizeof(lmark), 1, finput);
        if(fread_rtn != 1 && !feof(finput))
        {
            ErrorDialogue("Read error", "Landmark not read by DeleteLandmark( )", 0);
        }
        else if(fread_rtn == 0 && feof(finput))
        {
            break;
        }
        else if(strcmpi(lmark.name, lmark_name))
        {
            int fwrite_rtn = fwrite(plmark, sizeof(lmark), 1, ftemp);
            if(fwrite_rtn != 1)
            {
                ErrorDialogue("Write error", "Landmark not written by DeleteLandmark( )", 0);
            }
        }

    }
    fclose(ftemp);
    fclose(finput);

    finput = fopen(file_path, "wb");
    if(finput == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d: Error in %s.\n%s", ENOFILE, file_path, strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        return EOF;
    }
    ftemp = fopen(".\\Temp\\temp_delete.bin", "rb");
    if(ftemp == NULL)
    {
        char errmsg[50];
        sprintf(errmsg, "Error %d in DeleteLandmark: Error in %s.\n%s", ENOFILE, "temp file", strerror(ENOFILE));
        ErrorDialogue("File error", errmsg, 0);
        fclose(finput);
        return EOF;
    }

    while(!feof(ftemp))
    {
        int fread_rtn = fread(plmark, sizeof(lmark), 1, ftemp);
        if(fread_rtn != 1 && !feof(ftemp))
        {
            ErrorDialogue("Read error", "Landmark not read by DeleteLandmark( )", 0);
        }
        else if(strcmpi(lmark.name, lmark_name))
        {
            int fwrite_rtn = fwrite(plmark, sizeof(lmark), 1, finput);
            if(fwrite_rtn != 1)
            {
                ErrorDialogue("Write error", "Landmark not written by DeleteLandmark( )", 0);
            }
        }

    }

    fclose(ftemp);
    fclose(finput);
    remove(".\\Temp\\temp_delete.bin");
    return 0;
}


