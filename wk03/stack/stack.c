#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

/*
** Maximum size of the stack
*/ 
#define STACKSIZE  100

/*
** Use an array as the underlying stack
** method. Size of the array is the maximum number
** of items allowed on the stack
*/
static ContactDetails Stack[STACKSIZE];

/*
** Index to point to the next free slot in the stack
** the Index 0 is at the bottom of the stack.
*/ 
static int StackTop = 0;

/*
** Push a new item onto the stack
*/
int push(ContactDetails *new)
{
  /*
  ** If we are not actually pointing to an item 
  ** throw an error
  */
  if( new == NULL ) {
    fprintf(stderr, "push: no data to add\n");
    return 1;
  }

  /*
  ** If the stack is full throw an error cannot
  ** add any new items
  */
  if( StackTop == STACKSIZE ) {
    fprintf(stderr, "push: Stack full\n");
    return 2;
  }
    
  /*
  ** Copy the data from the new contact structure into
  ** the stacks data structure.
  */
  strcpy(Stack[StackTop].FamilyName,  new->FamilyName); 
  strcpy(Stack[StackTop].GivenName,   new->GivenName); 
  strcpy(Stack[StackTop].Phone,       new->Phone); 
  strcpy(Stack[StackTop].Email,       new->Email);

  /*
  ** Increment the StackTop as we have successfully
  ** pushed data onto the stack
  */
  StackTop++;

  return 0;
}

/*
** Pop the last item of the stack and return a pointer to it.
*/
ContactDetails *pop()
{
  /*
  ** If there is nothin on the stack we can't pop
  ** of any item
  */
  if( StackTop ==  0 ) {
    fprintf(stderr, "pop: Stack empty\n");
    return NULL;
  }
  
  /*
  ** Decrement the top of the stack by one. The item
  ** has effectively been removed!
  */
  StackTop--;

  /*
  ** The pointer returned is the pointer into
  ** the top of the stack
  */
  return Stack+StackTop;
}

/*
** List the contents of the stack starting at
** the top and working down the stack
*/
int list()
{
  int i;

  /*
  ** Simple for-loop to increment down the stack
  ** to the end of the stack (but the start of the array)!
  */
  for(i=StackTop-1; i>=0; i--) {
      fprintf(stdout,"\nName: %s %s\n",
	      Stack[i].GivenName, Stack[i].FamilyName);
      fprintf(stdout,"Phone: %s\n",Stack[i].Phone);
      fprintf(stdout,"Email: %s\n",Stack[i].Email);
    }

  return 0;
}

/*
** Return the number of items on the stack.
*/
int size()
{
  return StackTop;
}

/*
** Return true if the stack is full
*/
int full()
{
  return StackTop==STACKSIZE;
}
 
