#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "Functions.h"
#include "Places.h"
#include <limits.h>

int AddLandmark( char *file_location, int area, int lmark_type )
{
    FILE *fptr = fopen( file_location, "a" );

    if ( fptr == NULL )
    {
        MessageBox(0, "Error writing to file.\n", 0, 0);
        return 1;
    }

    LANDMARK lmark, lmark_b;
    if( StrInput( lmark.name, "Enter name of landmark: ", 50 ) == EOF)
    {
        fclose(fptr);
        return 1;
    }

    fflush( stdin );
    lmark_b = search_by_name( lmark.name, lmark_type );
    if ( strcmpi( lmark_b.name, lmark.name) != NULL )
    {
        fclose( fptr );
        char err_msg[130];
        int msgbox_return;
        sprintf(err_msg, "Landmark %s already exists. Do you want to add another landmark with same name?", lmark.name);
        msgbox_return = ErrorDialogue(NULL, err_msg, MB_YESNO);
        switch(msgbox_return)
        {
        case IDYES:
            break;
        case IDNO:
            fclose(fptr);
            return 0;
        }

    }
    lmark.area = area;
    lmark.type = lmark_type;
    if ( StrInput( lmark.address, "Enter address of landmark: ", 50 ) == EOF)
    {
        fclose(fptr);
        return 1;
    }
    if (strcmpi(lmark_b.address, lmark.address) == MATCH_FOUND)
    {
        ErrorDialogue(0, "Cannot have two landmarks with same name and address.", 0);
        fclose(fptr);
        return 0;
    }
    fflush( stdin );
    strcpy(lmark.phone,PhoneInput("Enter phone number: ") );
    fflush(stdin);
    {
        fwrite( &lmark, sizeof( lmark ), 1, fptr );
        printf( "Successfully added landmark.\n" );
        fclose( fptr );
        return 0;
    }
}
//*/

void DisplayLandmark( LANDMARK lmark )
{
    printf( "Name: %s\n", lmark.name );
    printf( "Address: %s\n", lmark.address );
    printf( "Phone number: %s\n", lmark.phone );
}

int DeleteLandmark( char *file_path, char *lmark_name )
{
    FILE *finput, *ftemp;
    LANDMARK lmark;
    P_LANDMARK plmark = &lmark;

    finput = fopen( file_path, "r" );
    ftemp = fopen( "temp.txt", "w" );

    if ( finput == NULL || ftemp == NULL )
        return 1;


    while ( !feof( finput ) )
    {
        fread( plmark, sizeof( lmark ), 1, finput );

        if ( strcmpi( lmark.name, lmark_name ) )
        {
            fwrite( plmark, sizeof( lmark ), 1, ftemp );
        }

    }

    fclose( ftemp );
    fclose( finput );

    finput = fopen( file_path, "w" );
    ftemp = fopen( "temp.txt", "r" );

    while ( !feof( ftemp ) )
    {
        fread( plmark, sizeof( lmark ), 1, ftemp );
        fwrite( plmark, sizeof( lmark ), 1, finput );

    }

    fclose( ftemp );
    fclose( finput );
    remove( "temp.txt" );


    return 0;
}


