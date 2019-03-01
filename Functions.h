#ifndef FUNCTION_H
#define FUNCTION_H

#include <windows.h>
#include "Places.h"

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define KEY_Q_SMALL 113
#define KEY_Q_CAPITAL 81
#define ENTERKEY 13
#define WHITE 7
#define RED 4
#define HIGHLIGHTED 135
#define NUM_AREAS 5
#define NOT_FOUND 0
#define FOUND 1
#define MATCH_FOUND 0
#define MATCH_NOT_FOUND 1

//graphics.c
void GoToXY( int x, int y );
COORD GoToMiddle( int, int );
void CreateTable( int length, int breadth );

int CreateLandmarkType( char * );
char* GetAreaName( int sn );
char* GetLandmarkType( int sn );
int SearchLandmarkType( char* inputname );

int GetMenuSelection( char *heading, char ( *options )[50], int num_options );

int search_by_area();
LANDMARK search_by_name( char *name, int lmark_type );
int modify_records();

int AddLandmark( char *file_location, int area, int lmarktype );
void DisplayLandmark( LANDMARK lmark );
int DeleteLandmark( char *file_path, char *lmark_name );

void setup();
int CreateFolder();
int StrInput( char *_string, char *msg, int sz );
int StripfromFile( char *file_path );
char* PhoneInput(char *);
int ErrorDialogue(char *heading, char *error, int type);
#endif // FUNCTION_H
