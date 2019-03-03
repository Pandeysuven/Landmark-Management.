#ifndef PLACES_H
#define PLACES_H

typedef struct _LANDMARK
{
    char phone[11];
    int area;
    char name[50];
    int type;
    char address[50];


} LANDMARK, *P_LANDMARK;


#endif // PLACES_H


/*
	if (temp == NULL)
	{
		char errmsg[50];
		sprintf(errmsg, "Error %d: %s", ENOMEM, strerror(ENOMEM));
		ErrorDialogue("Memory allocation error", errmsg, 0);
		exit(-1);
	}

	if ( fptr == NULL )
    {
    	char errmsg[50];
		sprintf(errmsg, "Error %d: Error in Landmark_list.txt.\n%s", errno, strerror(errno));
		ErrorDialogue("File error", errmsg, 0);
        free( temp );
        exit(-1);
    }









*/
