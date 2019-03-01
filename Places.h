#ifndef PLACES_H
#define PLACES_H

typedef struct _LANDMARK
{
    unsigned long long int phone;
    int area;
    int type;
    char address[50];
    char name[50];

} LANDMARK, *P_LANDMARK;


#endif // PLACES_H
