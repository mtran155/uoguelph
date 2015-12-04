#include "QueueInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void showQueueSize (Queue *Q) {
	if(Empty(Q)) printf("Queue is empty; ");
	else printf("Queue is not empty; ");
	if(Full(Q)) printf("queue is full; ");
	else printf("queue is not full; ");
	printf("queue is of length %d:\n",Size(Q));
}
	
	
static void showQueueContent (Queue *Q) {
	int i;
	Student S;
	for(i = Size(Q);i>0;i--) {
            Head(Q,&S);
		printf("\t%s %d%%\n",NameOfStudent(S),GradeOfStudent(S));
                Dequeue(Q);
                Enqueue(S,Q);
		FreeStudent(&S);
	}
}
			    

int main(void) {
	FILE *test;
	char s[20];
	int grade;
	Student S;
	Queue Q; 
	
	Initialize(&Q);
	showQueueSize(&Q);
	showQueueContent(&Q);
	
	test=fopen("test.txt","r");
	while(fscanf(test,"%s ",s)==1) {
		if(strcmp(s,"Enqueue")==0) {
			fscanf(test,"%s %d",s,&grade);
			InitializeStudent(s,grade,&S);
			Enqueue(S,&Q);
			FreeStudent(&S);
		}
		if(strcmp(s,"Dequeue")==0)
			Dequeue(&Q);
		showQueueSize(&Q);
		showQueueContent(&Q);
	} 
	
	fclose(test);
	Destroy(&Q);
	return EXIT_SUCCESS;
}

