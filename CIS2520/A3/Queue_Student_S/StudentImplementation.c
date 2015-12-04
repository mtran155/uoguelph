/*********************************************************************
 * FILE NAME: StudentImplementation.c
 * PURPOSE: A first implementation of the Student ADT.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 13/09/2013
 * NOTES: As we will see, there is a better way to check whether
 *        the preconditions and postconditions are met.
 *********************************************************************/


#include "StudentInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void InitializeStudent (char *name, int grade, Student *S) {
	strncpy(S->name,name,MAXNAMESIZE-1);
	S->name[MAXNAMESIZE-1]='\0';
	S->grade=grade;
        //postcondition
        assert(strcmp(name,NameOfStudent(*S))==0 && GradeOfStudent(*S)==grade);
}


char *NameOfStudent (Student S) {
	static char name[MAXNAMESIZE];
	strcpy(name,S.name);
	return name;
}


int GradeOfStudent (Student S) {
	return S.grade;
}


void FreeStudent (Student *S) {
}
