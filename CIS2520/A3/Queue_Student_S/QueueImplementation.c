#include "QueueInterface.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


static void copyItem (Item *Y, Item X) {
	InitializeStudent(NameOfStudent(X),GradeOfStudent(X),Y);
}


static void destroyItem (Item *X) {
	FreeStudent(X);
}


static int equalItems (Item X, Item Y) {
	int i;
	char *s;
	s=(char *)malloc(strlen(NameOfStudent(X))+1);
	strcpy(s,NameOfStudent(X));
	i=strcmp(s,NameOfStudent(Y));
	free(s);
	if(i!=0 || GradeOfStudent(X)!=GradeOfStudent(Y)) return 0;
	else return 1;
}


void Initialize (Queue *Q) {
    Q->size=0;
    Q->head=0;
    
    //postcondition
    assert(Empty(Q) && !Full(Q) && Size(Q)==0);
}


void Enqueue (Item I, Queue *Q) {
#ifndef NDEBUG
        int oldSize=Size(Q);
#endif
        //precondition
        assert(!Full(Q));  
        
        copyItem(&Q->items[(Q->size+Q->head)%MAXQUEUESIZE],I); //add to tail of queue
        Q->size++;
         
         //postcondition
         assert(!Empty(Q) && Size(Q)==oldSize+1);
}


void Dequeue (Queue *Q) {
#ifndef NDEBUG
        int oldSize=Size(Q);
#endif
        //precondition
        assert(!Empty(Q));

	Q->size--;
        destroyItem(&Q->items[Q->head]);
        Q->head = (Q->head+1) %MAXQUEUESIZE;  // move head over one spot
        
	//postcondition
        assert(!Full(Q) && Size(Q)==oldSize-1);
}


int Full (Queue *Q) {
	return Q->size==MAXQUEUESIZE;
}


int Empty (Queue *Q) {
	return Q->size==0;
}


int Size (Queue *Q) {
	return Q->size;
}


void Head (Queue *Q, Item *I) {
        //precondition
        assert(!Empty(Q));
        
	copyItem(I,Q->items[Q->head%MAXQUEUESIZE]); // gets head of the queue
}

void Tail (Queue *Q, Item *I) {
    //precondition
    assert(!Empty(Q));
    
    copyItem(I,Q->items[(Q->size+Q->head)%MAXQUEUESIZE]); // gets tail of the queue
}


void Destroy (Queue *Q) {
	int i;
	for(i=0;i<Q->size;i++)
		destroyItem(&Q->items[i]);
}

