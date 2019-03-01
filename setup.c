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
    CreateFolder();
    StripfromFile( ".\\Data\\Landmark_list.txt" ); //
    system( "title Landmark Management System" );
    system( "cls" );
}

int CreateFolder()
{
    FILE *fptr;
    char *temp = malloc( sizeof( char ) * 50 );
    char str_i[3];
    char *lmark = ( char* ) malloc( 100 * sizeof( char ) );
    char *landmark_file = ( char* ) malloc( 50 * sizeof( char ) );

    for ( int i = 1; i <= NUM_AREAS; i++ )
    {
        int j;
        char folder[50] = ".\\Data\\Area", mkdirs[50] = "IF NOT EXIST ";

        sprintf( str_i, "%d", i );
        strcat( folder, str_i );

        strcat( mkdirs, folder );
        strcat( mkdirs, " mkdir " );
        strcat( mkdirs, folder );
        system( mkdirs );

        j = 1;

        while ( ( temp = GetLandmarkType( j++ ) ) )
        {
            strcpy( lmark, temp );
            lmark[strlen( temp ) - 1] = '\0';
            strcpy( landmark_file, folder );
            strcat( landmark_file, "\\" );
            strcat( lmark, ".txt" );
            strcat( landmark_file, lmark );

            fptr = fopen( landmark_file, "r" );

            if ( fptr == NULL )
            {
                fptr = fopen( landmark_file, "w" );
            }

            fclose( fptr );

        }
    }

    free( lmark );
    free( landmark_file );
    free( temp );
    return 0;
}

int StripfromFile( char *file_path )
{
    FILE *finput, *ftemp;

    finput = fopen( file_path, "r" );
    ftemp = fopen( "temp.txt", "w" );

    if ( finput == NULL || ftemp == NULL )
    {
        return EXIT_FAILURE;
    }


    int line_sz = 20;
    char *line = calloc( line_sz, sizeof( char ) );

    if ( line == NULL )
    {
        printf( "Memory allocation error." );
        free(line);
        fclose(finput);
        fclose(ftemp);
        return 1;
    }

    while ( fgets( line, line_sz, finput ) )
    {
        if ( !feof( finput ) && line[strlen( line ) - 1] != '\n' )
        {
            line_sz *= 2;
            if ( (realloc( line, line_sz ) == NULL) )
            {
                printf( "Memory allocation error." );
                free(line);
                fclose(finput);
                fclose(ftemp);
                return 1;
            }
            fseek( finput, -strlen( line ), SEEK_CUR );
            continue;
        }

        if ( strcmp( line, "\n" ) )
        {
            fputs( line, ftemp );
        }
    }
    fclose( ftemp );
    fclose( finput );

    finput = fopen( file_path, "w" );
    ftemp = fopen( "temp.txt", "r" );
    while ( fgets( line, line_sz, ftemp ) )
    {
        fputs( line, finput );
    }

    free( line );
    fclose( ftemp );
    fclose( finput );
    remove( "temp.txt" );
    return 0;
}


int StrInput( char *input_string, char *msg, int sz )
{

    int len = 0, err = 0;
    fflush( stdin );

    while ( 1 )
    {
        int c;
        len = 0;
        printf( "%s", msg );

        while ( ( c = getchar() ) != '\n' )
        {
            if ( isalpha( c ) || isspace( c ) )
            {
                if ( len < sz - 1 )
                {
                    err = 0;
                    input_string[len++] = c;
                }
                else
                {
                    printf( "Input string too long.\n" );
                    fflush( stdin );
                    err = 1;
                    break;
                }
            }
            else
            {
                printf( "Invalid characters in input.\n" );
                fflush( stdin );
                err = 1;
                break;

            }
        }

        if ( err == 1 )
        {
            continue;
        }

        if ( len == 0 )
        {
            printf( "Input string is empty.\n" );
            fflush( stdin );
            continue;
        }

        break;
    }

    input_string[len] = '\0';
    return len;
}

char* PhoneInput(char *msg )
{
    int len;
    char *input_string = calloc( 11, sizeof( char ) );

    while ( 1 )
    {
        int c;
        len = 0;
        printf( "%s", msg );
        fflush(stdin);
        while ( ( c = getchar() ) != '\n' && len <= 10 )
        {
            if ( isdigit( c ) || c == '-')
            {
            	if (c != '-')
                input_string[len++] = c;
            }
            else
            {
                printf( "Please enter valid number.\n" );
                fflush( stdin );
                continue;
            }
        }
        if ( len == 0 )
        {
            printf( "Input is empty.\n" );
            fflush( stdin );
            continue;
        }
        else
            break;
    }
    input_string[len] = '\0';

    return input_string;
}
