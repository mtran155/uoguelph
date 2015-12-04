#include "StackType.h"

/*********************************************************************
 * FUNCTION NAME: Initialize
 * PURPOSE: Sets a Stack variable to the empty Stack.
 * ARGUMENTS: The address of the Stack variable to be initialized 
 *            (Stack *) 
 * ENSURES (postconditions):
 *          . Empty will return true (a nonzero integer).
 *          . Full will return false (0).
 *          . Size will return 0.
 * NOTES: Initialize is the only function that may be used right
 *        after the declaration of the Stack variable or a call
 *        to Destroy, and it should not be used otherwise.
 *********************************************************************/
extern void Initialize (Stack *S);

/*********************************************************************
 * FUNCTION NAME: Push
 * PURPOSE: Push an Item into a Stack.
 * ARGUMENTS: . The Item to be inserted (Item)
 *            . The address of the Stack (Stack *S)
 * REQUIRES (preconditions):
 *            . The Stack should not be full.
 * ENSURES: . Empty will return false (0).
 *          . Size will return the first integer greater
 *            than the length of the Stack before the call.
 *          . Top in the same position will find
 *            the Item that was inserted.
 *********************************************************************/
extern void Push (Item X, Stack *S);

/*********************************************************************
 * FUNCTION NAME: Pop
 * PURPOSE: Removes an Item from a Stack.
 * ARGUMENTS: . The address of the Stack (Stack *S)
 * REQUIRES:. The Stack should not be empty.
 * ENSURES: . Full will return false (0).
 *          . Size will return the first integer lower
 *            than the length of the Stack before the call.
 *********************************************************************/
extern void Pop (Stack *S);

/*********************************************************************
 * FUNCTION NAME: Full
 * PURPOSE: Determines whether a Stack is full.
 * ARGUMENTS: The address of the Stack (Stack *) 
 * RETURNS: True (a nonzero integer) if the Stack is full,
 *          false (0) otherwise
 *********************************************************************/
extern int Full (Stack *S);

/*********************************************************************
 * FUNCTION NAME: Empty
 * PURPOSE: Determines whether a Stack is empty.
 * ARGUMENTS: The address of the Stack (Stack *) 
 * RETURNS: True (a nonzero integer) if the Stack is empty,
 *          false (0) otherwise
 *********************************************************************/
extern int Empty (Stack *S);

/*********************************************************************
 * FUNCTION NAME: Size
 * PURPOSE: Finds the size of a Stack.
 * ARGUMENTS: The address of the Stack (Stack *) 
 * RETURNS: The size of the Stack (int)
 *********************************************************************/
extern int Size (Stack *S);

/*********************************************************************
 * FUNCTION NAME: Top
 * PURPOSE: Finds an Item in a Stack.
 * ARGUMENTS: . The address of the Stack (Stack *S)
 *            . The address of the Item
 *              the Item found should be copied to
 * REQUIRES:  . The Stack should not be empty.
 *********************************************************************/
extern void Top (Stack *S, Item *X);

/*********************************************************************
 * FUNCTION NAME: Destroy
 * PURPOSE: Frees memory that may have been allocated
 *          by Initialize, Insert or Remove.
 * ARGUMENTS: The address of the Stack to be destroyed (Stack * S) 
 * NOTES: The last function to be called should always be Destroy. 
 *********************************************************************/
extern void Destroy (Stack *S);


