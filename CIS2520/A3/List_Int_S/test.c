#include "ListInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void copyList(List *L1, List *L2){
    int i;
    int value;
    for(i=0;i<Length(L1);i++){
        Peek(i,L1,&value);
        Insert(value,i,L2);
    }
}

static void showListContent (List *L) {
        int i;
        int value;
        for(i=0;i<Length(L);i++) {               
                Peek(i,L,&value);
                printf("%d ",value);
        }
} 

static float TestBubbleSort1 (List*L){
    float sec;
    clock_t t1,t2;
    t1 = clock();
    BubbleSort1(L);
    t2 = clock();
    sec = (t2-t1)/(float)CLOCKS_PER_SEC;
    return sec;
}

static float TestBubbleSort2(List*L){
    float sec;
    clock_t t1,t2;
    t1 = clock();
    BubbleSort2(L);
    t2 = clock();
    sec = (t2-t1)/(float)CLOCKS_PER_SEC;
    return sec;
}   

static float TestMergeSort(List*L){
    float sec;
    clock_t t1,t2;
    t1 = clock();
    MergeSort(L,0,Length(L)-1);
    t2 = clock();
    sec = (t2-t1)/(float)CLOCKS_PER_SEC;
    return sec;
}

int main (void){
    FILE *test;   
    int number,position;
    float time;
    List L1, L2;
    
    Initialize(&L1);
    Initialize(&L2);
    
    test=fopen("test.txt","r");
    
    while(fscanf(test,"%d",&number)==1)
    {
        Insert(number,position,&L1);
        position++;
    }
    fclose(test);
      
    copyList(&L1,&L2);
    
    showListContent(&L1);
    printf(" to sort\n");    
    time = TestBubbleSort1(&L2);
    showListContent(&L2);
    printf(" BUBBLESORT1 in %lf seconds\n", time);
    
    Initialize(&L2);
    copyList(&L1,&L2);
       
    time = TestBubbleSort2(&L2);
    showListContent(&L2);
    printf(" BUBBLESORT2 in %lf seconds\n", time);
    
    Initialize(&L2);
    copyList(&L1,&L2);
    
    time = TestMergeSort(&L2);
    showListContent(&L2);
    printf(" MERGESORT in %lf seconds\n", time);
    
return 0;
}