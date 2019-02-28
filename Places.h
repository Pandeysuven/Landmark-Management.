#ifndef PLACES_H
#define PLACES_H

typedef struct _LANDMARK
{
    char name[50];
    char address[100];
    int area;
    int type;
    unsigned long long int phone;

} LANDMARK, *P_LANDMARK;


#endif // PLACES_H
