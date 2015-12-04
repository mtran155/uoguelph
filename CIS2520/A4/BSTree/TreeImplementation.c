#include "TreeInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int findHeight(TreeNode * p){ 
    int heightLeft, heightright;
    
    if(p != NULL){
        heightLeft = findHeight(p->left); // find height of left subtree
        heightright = findHeight(p->right); // find height of right subtree
        
        if(heightLeft > heightright) // return height of tree by seeing what subtree is larger in height
            return heightLeft + 1;
        else
            return heightright + 1;
    }
    else
        return -1; // tree is NULL
}

static int findBalance(TreeNode *p){
    int left, right;
    
    if(p != NULL){
        left = findHeight(p->left);
        right = findHeight(p->right);
        
        if(left - right > 1 || right - left > 1) // check if subtrees have heights that differ by at most 1
            return 0; // tree is not balanced
        else
            return 1; // tree is balanced
    }
    else
        return 1; // tree is NULL so balanced
}

static TreeNode * findMinimum (TreeNode *p) {
    while(p->left!=NULL)  // loop to find the leftmost leaf
        p = p->left;
    return p;
}

static void destroy(TreeNode * p,Tree * T){
    if(p != NULL)
    {
        destroy(p->left, T);
        destroy(p->right, T);
        T->destroyValue(p->value);
    }
}

void Initialize (Tree *T, void * (*copyValue) (void *, void *), void (*destroyValue) (void *), int (*compareValues) (void *, void *)){
    T->size = 0;
    T->root = NULL;
    T->copyValue = copyValue;
    T->destroyValue = destroyValue;
    T->compareValues = compareValues;
}

void Insert (Tree *T, void *I){    
    TreeNode *p, *q, *r;
    
    p = (TreeNode *)malloc(sizeof(TreeNode *));
    p->value = T->copyValue(NULL,I); // copy new student into new node
    p->right = p->left = NULL;
    q = T->root;
    r = NULL;
         
    T->size++;
    
    while (q != NULL){
        r = q;
        if(T->compareValues(I,q->value) < 0) 
            q = q->left;
        else
            q = q->right;
    }
    
    p->parent = r;
    
    if (r == NULL)
        T->root = p;
    else if (T->compareValues(I,r->value) < 0)
        r->left = p;
    else
        r->right = p;
}

int Minimum (Tree *T, void *I){   
    TreeNode *p;
    p = T->root;
    if(T->root == NULL)
        return 0;
    else{
        while(p->left != NULL)  // loop to find the leftmost leaf
            p = p->left;
        T->current = p;
        T->copyValue(I,p->value);
        return 1;
    } 
}

int Successor (Tree *T, void *I){
    TreeNode *p, *q;
    
    if(T->root == NULL)
        return 0;
    p = T->current;
    if(p->right != NULL){
        T->current = findMinimum(p->right);
        T->copyValue(I,T->current->value);
        return 1;
    } 
    
    q = p->parent;
    
    while(q != NULL && p == q->right){
        p = q;
        q = q->parent;
    }
    
    if(q != NULL){
        T->current = q;
        T->copyValue(I,q->value);
        return 1;
    }
    else 
        return 0;
}

int Size (Tree *T){
    int size = T->size;
    return size;
}

int Height (Tree *T){
    TreeNode *p;
    p = T->root;
    return findHeight(p);
}

int Balanced (Tree *T){
    int balance;
    TreeNode *p;
    p = T->root;
    return balance = findBalance(p);
    
}

void Destroy (Tree *T){
    TreeNode *p;
    p = T->root;
    destroy(p,T);
}