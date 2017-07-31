#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linklists.h"

ContactDetails *head = NULL;


int add(ContactDetails *new)
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

  llnew->next = head;
  head = llnew;

  return 0;
}

ContactDetails *search(char *fname, char *gname)
{
  ContactDetails *current = head;

  if( head == NULL ) {
    fprintf(stderr, "search: must add contacts first\n");
    return NULL;
  }

  if( fname == NULL || gname == NULL ) {
    fprintf(stderr, "search: must supply given name and family name\n");
    return NULL;
  }

  while(current != NULL) {
    if( !strcmp(current->FamilyName, fname) && 
        !strcmp(current->GivenName, gname) ) {

      return current;
    }
    current = current->next;
  }
  return NULL;
}


ContactDetails *delete(char *fname, char *gname)
{
  ContactDetails *parent = NULL;
  ContactDetails *current = head;

  if( head == NULL ) {
    fprintf(stderr, "delete: must add contacts first\n");
    return NULL;
  }
  if( fname == NULL || gname == NULL ) {
    fprintf(stderr, "delete: must supply given name and family name\n");
    return NULL;
  }

  while(current != NULL) {
    if( !strcmp(current->FamilyName, fname) && 
        !strcmp(current->GivenName, gname) ) {

      if( parent == NULL ) {
	head = head->next;
      } else {
        parent->next = current->next;
      }
      return current;

    } else {
      parent  = current;
      current = current->next;
    }
  }
  return NULL;
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

