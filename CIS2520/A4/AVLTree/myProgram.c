#include "StudentInterface.h"
#include "TreeInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void * copyValue (void *X, void *Y){
    Student S = *((Student*) Y);
    if (X == NULL)
        X = malloc(sizeof(Student));
    InitializeStudent(NameOfStudent(S),GradeOfStudent(S), X);
    return X;
}

static void destroyValue (void *X){
    FreeStudent(X);
}

static int compareValues (void *X, void *Y){
    int student1, student2;
    Student S1 = *((Student*) X);
    Student S2 = *((Student*) Y);
    
    student1 = GradeOfStudent(S1);
    student2 = GradeOfStudent(S2);
    if (student1 < student2)
        return -1;
    else if (student1 == student2)
        return 0;
    else if (student1 > student2)
        return 1;
}

static void printTreeProperties(Tree * T, Student S){
    printf("Insert(%s, %d)\nSize = %d, Height = %d, ", NameOfStudent(S), GradeOfStudent(S), Size(T), Height(T));
        if(Balanced(T) == 1)
            printf("Balanced = Yes \n\n");
        else if (Balanced(T) == 0)
            printf("Balanced = No \n\n");
}

static void printTree(Tree * T, Student S){
    int i;
    Minimum(T,&S);
    for(i = Size(T) ; i > 0; i--){
        printf("%s\t%d%%\n",NameOfStudent(S),GradeOfStudent(S));
        Successor(T,&S);
    }
}

int main(void){
    FILE *test;
    char student[20];
    int grade, i;
    void *(*copy)(void*,void*);
    void (*destroy)(void*);
    int (*compare)(void*,void*);
    Student S;
    Tree T; 
    
    copy = copyValue;
    destroy = destroyValue;
    compare = compareValues;
    
    Initialize(&T,copy,destroy,compare); // initialize the tree
    
    printf("Initialize()\nSize = %d, Height = %d,  ",Size(&T), Height(&T));
    if(Balanced(&T) == 1)
        printf("Balanced = Yes \n\n");
    else if (Balanced(&T) == 0)
        printf("Balanced = No \n\n");
    
    test = fopen("test.txt", "r");
    while(fscanf(test,"%s %d",student,&grade)==2){
        InitializeStudent(student, grade, &S);
        Insert(&T,&S);
        printTreeProperties(&T,S);
    }
    fclose(test);
    printTree(&T,S);
    Destroy(&T);
    return 0;
}