#include "ListInterface.h"
#include <stdlib.h>
#include <assert.h>

static void copyItem (Item *Y, Item X) {
	InitializeStudent(NameOfStudent(X),GradeOfStudent(X),Y);
}


static void destroyItem (Item *X) {
	FreeStudent(X);
}


static ListNode *moveTo (int position, List *L) {
	int i;
	ListNode *p=L->first;
	for(i=0;i<position;i++) p=p->next;
	return p;
}


void Initialize (List *L) {
	L->size=0;
	L->first=NULL;
        
        //post conditions
        assert(Empty(L) == 1 && Length(L) == 0 && Full(L) == 0);
}


void Insert (Item X, int position, List *L) {
    //preconditions
    int oldLength=Length(L);
    assert(position >= 0 && position <= oldLength && Full(L) == 0);
    
	ListNode *p, *q;
	
	L->size++;
	q=(ListNode *)malloc(sizeof(ListNode));
	copyItem(&q->item,X);
			 
	if(position==0) {
		q->next=L->first;
		L->first=q;
	}
	else {
		p=moveTo(position-1,L);
		q->next=p->next;
		p->next=q;
	}
	
	//post conditions
	assert(Empty(L) == 0 && Length(L) == oldLength + 1);
}


void Remove (int position, List *L) {
    //preconditions
    int oldLength=Length(L);
    assert(position >= 0 && position <= oldLength && Empty(L) == 0);
    
	ListNode *p, *q;
	
	if(position==0) {
		q=L->first;
		L->first=q->next;
	}
	else {
		p=moveTo(position-1,L);
		q=p->next;
		p->next=q->next;
	}
	
	destroyItem(&q->item);
	free(q);
	L->size--;
        
        //post conditions
        assert(Full(L) == 0 && Length(L) == oldLength-1);
}


int Full (List *L) {
	return 0;
}


int Empty (List *L) {
	return L->size==0;
}


int Length (List *L) {
	return L->size;
}


void Peek (int position, List *L, Item *X) {
    //preconditions
    assert(position >= 0 && position <= Length(L) && Empty(L) != 1);
    
    
	ListNode *p;
	p=moveTo(position,L);
	copyItem(X,p->item);
}


void Destroy (List *L) {
	int i;
	ListNode *p, *q;
	
	p=L->first;
	for(i=0;i<L->size;i++) {
		q=p;
		p=p->next;
		destroyItem(&q->item);
		free(q);
	}
}

