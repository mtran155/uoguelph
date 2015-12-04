#include "StudentInterface.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


void InitializeStudent (char *name, int grade, Student *S) {
	S->name=(char *)malloc(strlen(name)+1);
	strcpy(S->name,name);
	S->grade=grade;
        
        //post conditions
        assert(S->grade == grade && strcmp(name,S->name) == 0);
}


char *NameOfStudent (Student S) {
	static char *name=NULL;
	name=realloc(name,strlen(S.name)+1);
	strcpy(name,S.name);
	return name;
}


int GradeOfStudent (Student S) {
	return S.grade;
}


void FreeStudent (Student *S) {
	free(S->name);
}
