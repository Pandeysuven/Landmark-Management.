#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Functions.h"

int modify_records()
{
    char options_main[][50] = { "Add a new landmark", "Edit existing landmark", "Add new type of landmark"};
    char *inputString = ( char* ) calloc( 100, sizeof( char ) );

    while (1)
    {
        system("cls");
        int selected_option = GetMenuSelection( "Add/Modify Landmark", options_main, 3 ), input;
        switch ( selected_option )
        {
        case 0:
            free(inputString);
            return 0;
        case '\b':
            free(inputString);
            return 0;
        case 27:
            free(inputString);
            return 0;
        case 1:
        {
            system( "cls" );
            char options[20][50];
            char *temp;
            char file[50];
            int num_options = 0, j, selected_landmark, selected_area;

            for ( j = 1; GetAreaName( j ) != NULL; j++ )
            {
                char area[50];
                strcpy( area, GetAreaName( j ) );
                strcpy( options[num_options++], area );
            }
            selected_area = GetMenuSelection( "Select Area", options, num_options );
            if ( selected_area == 0 || selected_area == '\b')
            {
                free( inputString );
                return 0;
            }
            num_options = 0;
            j = 1;
            {
                while ( ( temp = GetLandmarkType( j++ ) ) != NULL )
                {
                    strcpy( options[num_options], temp );
                    num_options++;
                    system( "cls" );
                }
                selected_landmark = GetMenuSelection( "Select Landmark Type", options, num_options );

                if ( selected_landmark == 0)
                    return 0;
                if (selected_landmark == '\b')
                    continue;
            }
            system( "cls" );
			sprintf( file, ".\\Data\\Area%d\\%s.txt", selected_area, GetLandmarkType(selected_landmark) );
            AddLandmark( file, selected_area, selected_landmark );
            free( temp );

            printf( "Press q to exit.\nPress any key to return to main menu." );
            input = getch();
            fflush(stdin);

            if ( input == KEY_Q_CAPITAL || input == KEY_Q_SMALL )
            {
                free(inputString);
                exit( 0 );
            }
            if (input == '\b')
			{
				break;
			}
            free(inputString);
            return 0;
        }

        case 2:
            system( "cls" );
            char   options[][50] = {"Edit existing landmark\n", "Delete landmark"};
            int selected_edit_option = GetMenuSelection( "Edit Landmark", options, 2 );
            if (selected_edit_option == 0 || selected_edit_option == '\b')
                return 0;
            system( "cls" );
            if ( StrInput( inputString, "Enter landmark name: ", 50 ) == EOF)
                return 1;
            fflush( stdin );
            LANDMARK lmark;

            for ( int i = 1; GetLandmarkType( i ) != NULL; i++ )
            {
                lmark = search_by_name( inputString, i );

                if ( strcmpi(lmark.name, "null"))
                {
                    char file[50];
                    sprintf( file, ".\\Area%d\\%s.txt", lmark.area, GetLandmarkType( i ) );
                    int area = lmark.area;

                    if ( selected_edit_option == 1 )
                    {
                        DeleteLandmark( file, lmark.name );
                        AddLandmark( file, area, i );
                        break;
                    }

                    else if ( selected_edit_option == 2 )
                    {
                        DeleteLandmark( file, lmark.name );
                        break;
                    }
                }
                else
                {
                    printf("Landmark not found.\n");

                }
            }

            printf( "Press q to exit.\nPress any key to return to main menu." );
            input = getch();
            fflush(stdin);

            if ( input == KEY_Q_CAPITAL || input == KEY_Q_SMALL )
            {
                free( inputString );
                exit( 0 );
            }
            if (input == '\b')
			{
				break;
			}
            free(inputString);
            return 0;

        case 3:
            system( "cls" );
            GoToXY( 0, 0 );
            if ( StrInput( inputString, "Input name of landmark type: ", 50 ) == EOF)
                return 1;
            fflush( stdin );

            if ( SearchLandmarkType( inputString ) )
            {
                printf( "Landmark %s already exists.\n", inputString );
            }
            else
            {
                CreateLandmarkType( inputString );
                printf( "Successfully created new Landmark type.\n" );

            }
            printf( "Press q to exit.\nPress any key to return to main menu." );
            input = getch();
            fflush(stdin);
            if ( input == KEY_Q_CAPITAL || input == KEY_Q_SMALL )
            {
                free( inputString );
                exit( 0 );
            }
            if (input == '\b')
			{
				break;
			}
            free(inputString);
            return 0;
        }
    }
    free( inputString );
    return 0;



}


