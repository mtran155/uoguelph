/*********************************************************************
 * FILE NAME: ListImplementation.c
 * PURPOSE: Sequential implementation of the Student List ADT.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 13/09/2013
 * NOTES: . Some functions are static (they are auxiliary functions
 *          with local scope; they are not visible outside the file).
 *        . Only these static functions will need to be modified
 *          if the type of the list items (here, Student) changes. 
 *        . Only the other functions will need to be modified if
 *          the implementation of the List ADT changes.
 *        . As we will see, there is a better way to check whether
 *          the preconditions and postconditions are met.
 *********************************************************************/


#include "ListInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#define DEBUG

void Initialize (List *L) {
	L->size=0;
#ifdef DEBUG
	if(!Empty(L) || Full(L) || Length(L)!=0) {
		printf("Violated postcondition for Initialize!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Insert (Item X, int position, List *L) {
#ifdef DEBUG
	int oldLength=Length(L);
	if(position<0 || position>oldLength || Full(L)) {
		printf("Violated precondition for Insert!\n");
		exit(EXIT_FAILURE);
	}
#endif

    L->items[position] = X;
    L->size++;
      
#ifdef DEBUG
	Item Y;
	Peek(position,L,&Y);
	if(Empty(L) || Length(L)!=oldLength+1) {
		printf("Violated postcondition for Insert!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Remove (int position, List *L) {
#ifdef DEBUG
	int oldLength=Length(L);
	if(position<0 || position>=oldLength || Empty(L)) {
		printf("Violated precondition for Remove!\n");
		exit(EXIT_FAILURE);
	}
#endif

#ifdef DEBUG
	if(Full(L) || Length(L)!=oldLength-1) {
		printf("Violated postcondition for Remove!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


int Full (List *L) {
	return L->size==MAXLISTSIZE;
}


int Empty (List *L) {
	return L->size==0;
}


int Length (List *L) {
	return L->size;
}


void Peek (int position, List *L, Item *X) {
#ifdef DEBUG
	if(position<0 || position>=Length(L) || Empty(L)) {
		printf("Violated precondition for Peek!\n");
		exit(EXIT_FAILURE);
	}
#endif
    Item temp;
    temp = L->items[position];
    *X = temp;
}


void Destroy (List *L) {
}


void BubbleSort1 (List *L)
{
    int i,j,swap;   
    for (i = 1; i <= Length(L)-1; i++){
        for(j = 1; j <= Length(L)-i; j++){
            if(L->items[j-1]>L->items[j]){
                swap = L->items[j-1];
                L->items[j-1] = L->items[j];
                L->items[j] = swap;
            }
        }
    }
}

 
void BubbleSort2 (List *L)
{ 
    int i, flag, swap, length = Length(L);
    do{
        flag = 0;
        for(i = 1; i <= length-1; i++)
        {
            if(L->items[i-1] > L->items[i])
            {
                swap = L->items[i-1];
                L->items[i-1] = L->items[i];
                L->items[i] = swap;
                flag = 1;
            }
        }
        length--;    
    }while(flag != 0); 
}


void MergeSort(List *L, int first, int last)
{
    int middle;
    if(first < last )
    {
        middle = (first+last)/2;
        MergeSort(L,first,middle);
        MergeSort(L,middle+1,last);
        Merge(L,first,middle,last);
    }
}

void Merge(List *L, int first, int middle, int last)
{
    int leftArray[Length(L)/2];
    int rightArray[Length(L)/2];
    int i, j, k;
    
    for (i = 0; i <= middle-first; i++)
        leftArray[i] = L->items[first+i];
    
    leftArray[middle-first+1] = 1000000;
    
    for (j = 0; j <= last-middle-1; j++)
        rightArray[j] = L->items[middle+j+1];
    
    rightArray[last-middle] = 1000000;  
    
    i=j=0;
    
    for(k = first; k <= last; k++){
        if (leftArray[i] <= rightArray[j])
        {
            L->items[k]=leftArray[i];
            i++;
        }
        else
        {
            L->items[k]=rightArray[j];
            j++;
        }
    }
}
