#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

ContactDetails *head = NULL;
ContactDetails *tail = NULL;


int push(ContactDetails *new)
{
  ContactDetails *llnew;

  if( new == NULL ) {
    fprintf(stderr, "add: no contact information to add\n");
    return 1;
  }

  llnew = (ContactDetails *)malloc(sizeof(ContactDetails));
  
  if( llnew == NULL) {
    fprintf(stderr, "add: Failed to get memory for new contact\n");
    return 1;
  }

  memcpy(llnew,new,sizeof(ContactDetails));

  llnew->next = NULL;

  if( head == NULL ) {
    head = llnew;
  } else { 
    tail->next = llnew;
  }  

  tail = llnew;

  return 0;
}


ContactDetails *pop()
{
  ContactDetails *ptr = head;

  if( head == NULL ) {
    fprintf(stderr, "delete: must add contacts first\n");
    return NULL;
  }

  head = head->next;

  return ptr;
}

int list()
{
  ContactDetails *current = head;

  while(current != NULL) {
      fprintf(stdout,"\nName: %s %s\n",
	      current->GivenName, current->FamilyName);
      fprintf(stdout,"Phone: %s\n",current->Phone);
      fprintf(stdout,"Email: %s\n",current->Email);

      current = current->next;
    }

  return 0;
}

