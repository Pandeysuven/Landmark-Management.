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
    StripfromFile( ".\\Data\\Area_list.txt" );
    system( "title Landmark Management System" );
    system( "cls" );
}

int CreateFolder()
{
    FILE *fptr;
    char *landmark_file = ( char* ) malloc( 50 * sizeof( char ) );
    system("IF NOT EXIST .\\Temp mkdir .\\Temp");

    for ( int i = 1; i <= NUM_AREAS; i++ )
    {
        int j;
        char mkdirs[50];
        sprintf(mkdirs, "IF NOT EXIST .\\Data\\Area%d mkdir .\\Data\\Area%d", i, i);
        system( mkdirs );

        j = 1;

        while ( GetLandmarkType(j) != NULL)
        {
            sprintf(landmark_file, ".\\Data\\Area%d\\%s.txt", i, GetLandmarkType(j++));
            fptr = fopen( landmark_file, "r" );
            if ( fptr == NULL )
            {
                fptr = fopen( landmark_file, "w" );
            }

            fclose( fptr );

        }
    }
    free( landmark_file );
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
            if ( c == EOF)
                return EOF;
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

int ErrorDialogue(char *heading, char *error, int type)
{
    int option;
    if (type == 0)
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
