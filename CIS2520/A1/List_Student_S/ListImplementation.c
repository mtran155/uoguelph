#include "ListInterface.h"
/* some code here (e.g., #include directives, static functions) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEBUG

void Initialize (List *L) {
#ifdef DEBUG
    if (Empty(L) != 1 && Full(L) != 0 && Length(L) != 0)
    {
        printf("ERROR INITIALIZING LIST\n");
        exit(0);
    }
#endif        
	/* some code here */
}

void Insert (Item X, int position, List *L) {
#ifdef DEBUG
    if (position < 0 && Full(L) != 1)
    {
        printf("ERROR INSERTING \n");
        exit(0);
    }
#endif
    
    int i, prevPos;
    prevPos = Length(L) - 1;
    if(prevPos >= position && Full(L) != 1)
    {
        for(i = Length(L) -1 ; i >= position; i--)
        {
            L->items[i+1] = L->items[i];
        }
    }
    L->items[position] = X;
    L->size = L->size+1;
    
#ifdef DEBUG
    if(Empty(L) == 1)
    {
        printf("ERROR INSERTING \n");
        exit(0);
    }    
#endif
	/* some code here */
}

void Remove (int position, List *L) {
#ifdef DEBUG
    if (position < 0 && Empty(L) != 1)
    {
        printf("ERROR REMOVING\n");
        exit(0);
    }
#endif

    int i, prevPos; 
    prevPos = Length(L) -1;
    if(prevPos >= position && Empty(L) != 1)
    {
        for (i = position+1; i<= Length(L); i++)
        {
            L->items[i-1] = L->items[i];
        }
    }
    L->size = L->size-1;
    
	/* some code here */
}

int Full (List *L) {
    if(L->size == MAXLISTSIZE)
        return 1;
    else
        return 0; /* change this */
}

int Empty (List *L) {
    if (L->size == 0)
        return 1; /* change this */
    else 
        return 0;
}

int Length (List *L) {
    int length;
    length = L->size;
    
    return length; /* change this */
}

void Peek (int position, List *L, Item *X) {
#ifdef DEBUG
    if (position < 0 && Empty(L) != 1)
    {
        printf("ERROR PEEKING\n");
        exit(0);
    }
#endif
    
    Item temp;
    temp = L->items[position];
    *X = temp;
    
	/* some code here */
}

void Destroy (List *L) {
	/* some code here */
}