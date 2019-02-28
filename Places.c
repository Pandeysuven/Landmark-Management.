//  /*
#include "Functions.h"
#include "Places.h"
#include <inttypes.h>
#include <limits.h>

int AddLandmark(char *file_location, int area, int lmark_type)
{
    FILE *fptr = fopen(file_location, "a");
    if (fptr == NULL)
    {
        printf("Error writing to file.\n");
        return 1;
    }
    LANDMARK lmark;
    P_LANDMARK plmark = &lmark;
    StrInput(&lmark.name, "Enter name of landmark: ", 50);
    fflush(stdin);

    LANDMARK temp = search_by_name(lmark.name, lmark_type);
    if (!strcasecmp ( temp.name, lmark.name) )
    {
        fclose(fptr);
        printf("Landmark already exists.\n");
        return 1;
    }
    StrInput(&lmark.address, "Enter address of landmark: ", 100);
    fflush(stdin);
    lmark.area = area;
    lmark.type = lmark_type;
    while (lmark.phone != 0)
    {
        printf("Enter phone number: ");
        lmark.phone = ULLInput();
    }

    fflush(stdin);

    {
        fwrite(plmark, sizeof(LANDMARK), 1, fptr);
        printf("Successfully added landmark.\n");
        fclose(fptr);
        return 0;
    }
}
//*/

void DisplayLandmark(LANDMARK lmark)
{
    printf("Name: %s\n", lmark.name);
    printf("Address: %s\n", lmark.address);
    printf("Phone number: %"PRId64"\n", lmark.phone);
}

int DeleteLandmark(char *file_path, char *lmark_name)
{
    FILE *finput, *ftemp;
    LANDMARK lmark;
    P_LANDMARK plmark = &lmark;

    finput = fopen(file_path, "r");
    ftemp = fopen("temp.txt", "w");

    if (finput == NULL || ftemp == NULL)
        return 1;


    while (!feof(finput))
    {
        fread(plmark, sizeof(lmark), 1, finput);
        if (strcmp(lmark.name, lmark_name))
        {
            fwrite(plmark, sizeof(lmark), 1, ftemp);
        }

    }

    fclose(ftemp);
    fclose(finput);

    finput = fopen(file_path, "w");
    ftemp = fopen("temp.txt", "r");
    while (!feof(ftemp))
    {
        fread(plmark, sizeof(lmark), 1, ftemp);
        fwrite(plmark, sizeof(lmark), 1, finput);

    }

    fclose(ftemp);
    fclose(finput);
    remove("temp.txt");


    return 0;
}


