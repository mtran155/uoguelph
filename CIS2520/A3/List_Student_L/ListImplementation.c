/*********************************************************************
 * FILE NAME: ListImplementation.c
 * PURPOSE: One-way linked implementation of the Student List ADT.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 13/09/2013
 * NOTES: . Some functions are static (they are auxiliary functions
 *          with local scope; they are not visible outside the file).
 *        . Only the first two functions will need to be modified
 *          if the type of the list items (here, Student) changes. 
 *        . Only the other functions will need to be modified if
 *          the implementation of the List ADT changes.
 *        . For preconditions and postconditions,
 *          see the sequential implementation (no changes).
 *********************************************************************/


#include "ListInterface.h"
#include <stdio.h>
#include <stdlib.h>


static void copyItem (Item *Y, Item X) {
	InitializeStudent(NameOfStudent(X),GradeOfStudent(X),Y);
}


static void destroyItem (Item *X) {
	FreeStudent(X);
}


static ListNode *moveTo (int position, List *L) {
	int i;
	ListNode *p=L->first;
	for(i=0;i<position;i++) p=p->next;
	return p;
}

static ListNode *ReverseNode (ListNode * p)
{
    ListNode * q, *r;
    if(p->next != NULL)
    {      
        r = ReverseNode(p->next);
        q = p->next;
        q->next = p;
        p->next = NULL;
        return r;
    }
    else
        return p;
}

void Initialize (List *L) {
	L->size=0;
	L->first=NULL;
}


void Insert (Item X, int position, List *L) {
	ListNode *p, *q;
	
	L->size++;
	q=(ListNode *)malloc(sizeof(ListNode));
	copyItem(&q->item,X);
			 
	if(position==0) {
		q->next=L->first;
		L->first=q;
	}
	else {
		p=moveTo(position-1,L);
		q->next=p->next;
		p->next=q;
	}
}


void Remove (int position, List *L) {
	ListNode *p, *q;
	
	if(position==0) {
		q=L->first;
		L->first=q->next;
	}
	else {
		p=moveTo(position-1,L);
		q=p->next;
		p->next=q->next;
	}
	
	destroyItem(&q->item);
	free(q);
	L->size--;
}


int Full (List *L) {
	return 0;
}


int Empty (List *L) {
	return L->size==0;
}


int Length (List *L) {
	return L->size;
}


void Peek (int position, List *L, Item *X) {
	ListNode *p;
	p=moveTo(position,L);
	copyItem(X,p->item);
}


void Destroy (List *L) {
	int i;
	ListNode *p, *q;
	
	p=L->first;
	for(i=0;i<L->size;i++) {
		q=p;
		p=p->next;
		destroyItem(&q->item);
		free(q);
	}
}

void Reverse (List * L){
    ListNode *p, *q;
    p = L->first;
    if(p != NULL)
        q = ReverseNode(p);
    L->first = q;
}

