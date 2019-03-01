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

            if ( strcmpi( lmark.name, input_name ) == 0 )
            {
                return lmark;
            }
        }
    }

    return null;
}
