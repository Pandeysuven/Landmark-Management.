#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Functions.h"
#include "Places.h"

LANDMARK search_by_name( char *input_name,  int lmark_type )
{
    int j = 1;
    LANDMARK null;
    LANDMARK lmark;
    strcpy( null.name, "null" );

    for ( j = 1; j <= NUM_AREAS; j++ )
    {
        FILE *fptr;
        char file[50] = ".\\Data\\Area", str_num[3];
        sprintf( str_num, "%d", j );
        strcat( file, str_num );
        strcat( file, "\\" );
        char temp[20];

        strcpy( temp, GetLandmarkType( lmark_type ) );
        temp[strlen( temp ) - 1] = '\0';
        strcat( file, temp );
        strcat( file, ".txt" );
        fptr = fopen( file, "r" );

        if ( fptr == NULL )
        {
            printf( "Error opening file %s", file );
        }
        while ( !feof( fptr ) )
        {
            fread( &lmark, sizeof( lmark ), 1, fptr );
            char lmark_name_lower[50], input_name_lower[50];
            strcpy(lmark_name_lower, lmark.name);
            strcpy(input_name_lower, input_name);
            strlwr(lmark_name_lower);
            strlwr(input_name_lower);
            if ( strstr( lmark_name_lower, input_name_lower ) != NULL)
            {
                return lmark;
            }
        }
    }

    return null;
}
