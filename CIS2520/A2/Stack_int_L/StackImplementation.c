#include "StackInterface.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void copyItem(Item *Y, Item X){
    *Y = X;
}

void Initialize (Stack *S) {
	S->size=0;
	S->first=NULL;
        
        //post conditions
        assert(Empty(S) == 1 && Size(S) == 0 && Full(S) == 0);
}


void Push (Item X, Stack *S) {
    // precondition
    assert(Full(S) == 0);
    int oldSize = Size(S);
    
    StackNode *temp1, *temp2;
    
    temp1 = (StackNode *)malloc(sizeof(StackNode));
    copyItem(&temp1->item,X);
    temp2 = S->first; 
    temp1->next = temp2;
    S->first = temp1;
    S->size++;
    
    //post conditions
    assert(Empty(S) == 0 && Size(S) == oldSize + 1);
}


void Pop (Stack *S) {
    // precondition
    assert(Empty(S) == 0);
    int oldSize = Size(S);
    
	StackNode *temp1;
        
        temp1 = S->first;
        S->first = temp1->next;
        free (temp1);
	S->size--;
        
        // post conditions
        assert(Full(S) == 0 && Size(S) == oldSize - 1);
}


int Full (Stack *S) {
	return 0;
}


int Empty (Stack *S) {
	return S->size==0;
}


int Size (Stack *S) {
	return S->size;
}


void Top (Stack *S, Item *X) {
    //precondition
    assert(Empty(S) == 0);
    
    StackNode *temp1;
    temp1 = (StackNode *)malloc(sizeof(StackNode));
    temp1 = S->first; 
    *X = temp1->item;
}


void Destroy (Stack *S) {
	int i;
	StackNode *p, *q;
	
	p = S->first;
        
	for(i=0;i<S->size;i++) {
		q=p;
		p=p->next;
		free(q);
	}
}

