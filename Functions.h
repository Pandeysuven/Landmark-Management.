#ifndef FUNCTION_H
#define FUNCTION_H
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <wincon.h>
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
#define NUM_AREAS 15

#define HIGHLIGHTED 135



//graphics.c
void GoToXY(int x, int y);
COORD GoToMiddle(int,int);
void CreateTable(int length, int breadth);
int StripfromFile(char *file_path);

int GetMenuSelection(char *heading, char (*options)[50], int num_options);

void search_by_area();
LANDMARK search_by_name(char *name, int lmark_type);
int modify_records();

int CreateLandmarkType(char *);
char* GetLandmarkType(int sn);
int SearchLandmarkType(char* inputname);
void DisplayLandmark(LANDMARK lmark);
int AddLandmark(char *file_location, int area,int lmarktype);
int DeleteLandmark(char *file_path, char *lmark_name);
char* GetAreaName(int sn);

unsigned long long int ULLInput();
int StrInput(char *_string, char *msg, int sz);


#endif // FUNCTION_H
