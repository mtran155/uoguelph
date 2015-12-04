#include "StudentInterface.h"
/* some code here (e.g., #include directives, static functions) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEBUG

void InitializeStudent (char * name, int grade, Student * S) 
{
    S->name = (char *)malloc(strlen(name)+1);
    strcpy(S->name, name);
    S->grade = grade;
    
#ifdef DEBUG
    if (S->grade != grade || strcmp(name,S->name) != 0)
    {
        printf("ERROR INITIALIZING STUDENT \n");
        exit (0);
    }
#endif
	/* some code here */
}
char * NameOfStudent (Student S) 
{
    char * name;
    name =(char *) malloc(strlen(S.name)+1);
    strcpy(name,S.name);
    return name;/* change this */
}
int GradeOfStudent (Student S) 
{
    int grade = S.grade;
    return grade;/* change this */
}
void FreeStudent (Student * S) 
{
    free(S->name);
    free(S);
	/* some code here */
}