/*********************************************************************
 * FILE NAME: myProgram.c
 * PURPOSE: Test program for Student List implementations.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 13/09/2013
 * NOTES: This program uses test data recorded in a text file
 *        (see test.txt). 
 *********************************************************************/


#include "ListInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void showListSize (List *L) {
	if(Empty(L)) printf("List is empty; ");
	else printf("List is not empty; ");
	if(Full(L)) printf("list is full; ");
	else printf("list is not full; ");
	printf("list is of length %d:\n",Length(L));
}
	
	
static void showListContent (List *L) {
	int i;
	Student S;
	for(i=0;i<Length(L);i++) {               
		Peek(i,L,&S);
		printf("\t%s %d%%\n",NameOfStudent(S),GradeOfStudent(S));
		FreeStudent(&S);
	}
}
			   

int main(void) {
	FILE *test;
	char s[20];
	int position, grade;
	
	Student S;
	List L; 
	
	Initialize(&L);
	showListSize(&L);
	showListContent(&L);
	
	test=fopen("test.txt","r");
	while(fscanf(test,"%s %d",s,&position)==2) {
		if(strcmp(s,"Insert")==0) {
			fscanf(test,"%s %d",s,&grade);
			InitializeStudent(s,grade,&S); 
			Insert(S,position,&L);
			FreeStudent(&S);
		}
		if(strcmp(s,"Delete")==0)
			Remove(position,&L);
                Reverse(&L);
		showListSize(&L);
		showListContent(&L);
                Reverse(&L);
	}
	
	fclose(test);
	Destroy(&L);
	return EXIT_SUCCESS;
}

