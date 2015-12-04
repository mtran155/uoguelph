#include "StudentInterface.h"
typedef Student Item;

typedef struct ListNodeTag {
	Item items;
	struct ListNodeTag *next;
} ListNode;
typedef struct{
    int size;
    ListNode *first;
}List;