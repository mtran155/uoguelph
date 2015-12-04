#include "ListInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void copyList(List *L1, List *L2){
    int i;
    int value;
    for(i=0;i<Length(L1);i++){
        Peek(i,L1,&value);
        Insert(value,i,L2);
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

static void printBubbleSort1Stat(float average, float best, float worst){
    printf("BubbleSort1:\n");
    printf("BEST TIME  = %f seconds\n", best);
    printf("AVG TIME   = %f seconds\n", average);
    printf("WORST TIME = %f seconds\n\n", worst);
}

static void printBubbleSort2Stat(float average, float best, float worst){
    printf("BubbleSort2:\n");
    printf("BEST TIME  = %f seconds\n", best);
    printf("AVG TIME   = %f seconds\n", average);
    printf("WORST TIME = %f seconds\n\n", worst);
}

static void printMergeSortStat(float average, float best, float worst){
    printf("MergeSort:\n");
    printf("BEST TIME  = %f seconds\n", best);
    printf("AVG TIME   = %f seconds\n", average);  
    printf("WORST TIME = %f seconds\n\n", worst);
}

int main (int argc, char*argv[]){  
    
    if(argc != 3)
    {
        printf("Not enough arguments\n");
        return 0;
    }  
    
    int number,i, position, counter = 0;
    float time1=0.0, time2=0, time3=0.0;
    float bubbleSortAvg =0.0, bubbleSortBest =10000.0 , bubbleSortWorst=0.0;
    float bubbleSort2Avg=0.0, bubbleSort2Best = 10000.0, bubbleSort2Worst=0.0;
    float mergeSortAvg=0.0, mergeSortBest = 1.0, mergeSortWorst=0.0;
    int numberOfList = atoi(argv[1]);
    int numberOfElements = atoi(argv[2]);
    List L1, L2; 
    
    while(counter < numberOfList)
    {
        Initialize(&L1);
        Initialize(&L2);
        position = 0;
        time1 = 0;
        time2 = 0;
        time3 = 0;
        
        if (counter == 0)
        {
            for(i=1; i <= numberOfElements; i++)// create list from (1,2,3....N)
            {
                Insert(i,position,&L1);
                position++;
            }
            copyList(&L1,&L2);
            time1 = TestBubbleSort1(&L2);
            
            Initialize(&L2);
            copyList(&L1,&L2);
            time2 = TestBubbleSort2(&L2);
                      
            Initialize(&L2);
            copyList(&L1,&L2);
            time3 = TestMergeSort(&L2);
        }
        
        if(counter == 1)
        {
            for (i=numberOfElements; i>=1;i--) // creates list from (N,N-1.....3,2,1)
            {
                Insert(i,position,&L1);
                position++;
            } 
            copyList(&L1,&L2);
            time1 = TestBubbleSort1(&L2);
     
            Initialize(&L2);
            copyList(&L1,&L2);
            time2 = TestBubbleSort2(&L2);

            Initialize(&L2);
            copyList(&L1,&L2);
            time3 = TestMergeSort(&L2);
        }
        else if (counter > 1)
        {
            for(i=1;i<=numberOfElements;i++) // creates a list with random numbers
            {
                number = rand() % numberOfElements;
                Insert(number,position,&L1);
                position++;
            }
            copyList(&L1,&L2);
            time1 = TestBubbleSort1(&L2);
            
            Initialize(&L2);
            copyList(&L1,&L2);
            
            time2 = TestBubbleSort2(&L2);
            
            Initialize(&L2);
            copyList(&L1,&L2);
            
            time3 = TestMergeSort(&L2);           
        }
        
        bubbleSortAvg = bubbleSortAvg + time1;
        if(time1<bubbleSortBest)
            bubbleSortBest=time1;
        if(time1>bubbleSortWorst)
            bubbleSortWorst=time1;
              
        bubbleSort2Avg = bubbleSort2Avg + time2;
        if(time2<bubbleSort2Best)
            bubbleSort2Best=time2;
        if(time2>bubbleSort2Worst)
            bubbleSort2Worst=time2;
        
        mergeSortAvg = mergeSortAvg + time3;
        if(time3<mergeSortBest)
            mergeSortBest=time3;
        if(time3>mergeSortWorst)
            mergeSortWorst=time3;
      
        counter++;
    }
    
    bubbleSortAvg = bubbleSortAvg/numberOfList;
    bubbleSort2Avg = bubbleSort2Avg/numberOfList;
    mergeSortAvg = mergeSortWorst/numberOfList;
    
    printBubbleSort1Stat(bubbleSortAvg,bubbleSortBest,bubbleSortWorst);
    printBubbleSort2Stat(bubbleSort2Avg,bubbleSort2Best,bubbleSort2Worst);
    printMergeSortStat(mergeSortAvg,mergeSortBest,mergeSortWorst);
    
    return 0;
}