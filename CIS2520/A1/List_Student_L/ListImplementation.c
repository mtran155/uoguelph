#include "ListInterface.h"
/* some code here (e.g., #include directives, static functions) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEBUG

void Initialize (List *L) {
    L->size = 0;
    L->first = NULL;
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
        printf("ERROR INSERTING\n");
        exit(0);
    }
    #endif
    
    int i;
    ListNode *temp1 = (ListNode *) malloc(sizeof(ListNode)); 
    InitializeStudent(NameOfStudent(X),GradeOfStudent(X),&temp1->items); // copy content of Item X into temp node
    temp1->next = NULL;
    ListNode *temp2 = L->first;

    if(position == 0)
    {
        temp1->next=L->first;
        L->first =temp1;
    }
    else
    {
        for(i = 0; i < position -1; i++)
        {
            temp2 = temp2->next;
        }
        temp1->next = temp2->next;
        temp2->next = temp1;
    }
    L->size = L->size+1; 
    
#ifdef DEBUG
    if(Empty(L) == 1)
    {
        printf("ERROR INSERTING\n");
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

    int i;
    ListNode *temp1;
    ListNode *temp2;
    temp1 = L->first;
    
    if (position == 0)
    {
        L->first = temp1->next;
        free(temp1);
    }
    else 
    {
        for (i = 0 ; i < position - 2; i++)
        {
            temp1 = temp1->next;
        }
        temp2 = temp1->next;
        temp1->next = temp2->next;
        free(temp2);
    }
    L->size = L->size-1;
    
	/* some code here */
}

int Full (List *L) {
    return 0;
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

    int i;
    ListNode *temp1;
    temp1 = L->first;
    
    for(i = 0; i < position; i++)
    {
        temp1 = temp1->next;
    }
    InitializeStudent(NameOfStudent(temp1->items),GradeOfStudent(temp1->items),X);

	/* some code here */
}

void Destroy (List *L) {
    free(L);
	/* some code here */
}