#include "HeapInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int Initialize (Heap *H, int capacity, void * (*copyValue) (void *, void *),  void (*destroyValue) (void *), int (*compareValues) (void *, void *)){
    H->heap = (void*)malloc(sizeof(void*)*(capacity+1));
    if(H->heap != NULL){
        H->capacity = capacity;
        H->numberOfValues = 0;
        H->copyValue = copyValue;
        H->destroyValue = destroyValue;
        H->compareValues = compareValues;
        return 1;
    }
    else
        return 0;
}

int Insert (Heap *H, void *I)
{
    int child;
    void * p;
    
    p = H->copyValue(NULL, I);
    
    if(p != NULL){
        H->numberOfValues++;
        H->heap[H->numberOfValues] = p; // insert at the end of tree
        child = H->numberOfValues;
        while(child > 1){ // while the child is greater than parent swap ((up)heapify)
            if(H->compareValues(H->heap[child],H->heap[child/2]) < 0){
                p = H->heap[child/2];
                H->heap[child/2] = H->heap[child];
                H->heap[child] = p;
                child = child/2;
            }
            else
                break;
        }
        return 1;
    }
    else 
        return 0; 
}

void Remove(Heap *H)
{ 
    int parent, child;
    void *p;
    
    if(Empty(H) == 0){        
        H->destroyValue(H->heap[1]); // remove max node
        H->heap[1] = H->heap[H->numberOfValues]; // replace with last node in tree
        H->numberOfValues--;
        
        parent = 1;
        child = 2 * parent; 
        
        while (child <= H->numberOfValues){ // while child is less than or equal to number of items in heap (down)heapify
            if (child < H->numberOfValues && H->compareValues(H->heap[child],H->heap[child+1]) > 0)
                child++;
            if(H->compareValues(H->heap[parent],H->heap[child]) > 0){ // if last node is smaller than the child swap them
                p = H->heap[parent];
                H->heap[parent] = H->heap[child];
                H->heap[child] = p;
                parent = child;
                child = child * 2;
            }
            else
                break;    
        }
    }
}

void Top (Heap*H, void *I)
{
    H->copyValue(I,H->heap[1]);
}

int Full (Heap * H)
{
    if(H->numberOfValues == H->capacity)
        return 1;
    else
        return 0;    
}

int Empty (Heap * H)
{
    if(H->numberOfValues == 0)
        return 1;
    else 
        return 0;
}

void Destroy (Heap *H)
{
    int i;
    for(i = 1; i <= H->numberOfValues; i++)
        H->destroyValue(H->heap[i]);
}