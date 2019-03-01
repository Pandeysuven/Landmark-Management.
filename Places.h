#ifndef PLACES_H
#define PLACES_H

typedef struct _LANDMARK
{
    char phone[11];
    int area;
    int type;
    char address[50];
    char name[50];
    int starts_with_leading_zero;


} LANDMARK, *P_LANDMARK;


#endif // PLACES_H
