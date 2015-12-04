#include "StudentInterface.h"
#include "HeapInterface.h"
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

static void printHeap(Heap *H, int capacity){
    int i;
    Student S;
    for(i = capacity; i > 0; i--){
        Top(H,&S);
        printf("%s %d\n",NameOfStudent(S),GradeOfStudent(S));
        Remove(H); 
        FreeStudent(&S);
        
        if(Empty(H) == 1)
            break;
    }
}
    

int main (int argc, char* argv[]) {
    FILE *test;
    char student[20];
    int grade, i;
    int capacity;
    void *(*copy)(void*,void*);
    void (*destroy)(void*);
    int (*compare)(void*,void*);
    Student S;
    Heap H; 
    
    if(argc != 2){
        printf("Error: must enter a postive value N to view top N students\n");
        return 0;
    }
    
    capacity = atoi(argv[1]);    
    copy = copyValue;
    destroy = destroyValue;
    compare = compareValues;
    
    Initialize(&H,capacity,copy,destroy,compare); // initialize the heap
    
    test=fopen("test.txt","r");
    while(fscanf(test,"%s %d",student,&grade)==2){        
        if(Full(&H) == 0) { // if heap is not full insert student
            InitializeStudent(student,grade,&S);                    
            Insert(&H,&S);
        }
        /* if heap is full compare the grade of the student at top of heap to student from file if greater 
         * remove student from top of heap and insert new student*/
        else if (Full(&H) == 1) { 
            Top(&H,&S);
            if(grade > GradeOfStudent(S)) {
                Remove(&H);
                InitializeStudent(student,grade,&S);
                Insert(&H,&S);
            }
        }
    }
    fclose(test);
    printHeap(&H,capacity);
    Destroy(&H);
    return 0;
}