typedef int Item;

typedef struct StackNodeTag {
	Item item;
	struct StackNodeTag *next;
} StackNode;

typedef struct {
	int size;
	StackNode *first;
} Stack;
