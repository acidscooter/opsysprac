#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

/*
** Size of the hash-table
*/
#define BUCKETS 10

/*
** Each slot in the hash table points to its own
** link-list of contact structures.
*/
ContactDetails *bucket[BUCKETS];

/*
** The hash function: Given a family-name and a given-name
** the hash function will return an integer between 0 and
** BUCKETS-1. That is the index of the slot where the 
** contact should be placed/found.
*/ 
unsigned int hash(char *fname, char *gname) 
{
  char gfname[SZ_FNAME+SZ_GNAME];
  char *ptr;
  unsigned int val;

  /*
  ** Combine the family-name and given-name
  ** strings into the single key given-family
  */
  *gfname = '\0';
  strcat(gfname,gname);
  strcat(gfname,fname);
  ptr = gfname;
  /*
  ** Now use the ASCII value of each character and add
  ** them together - this is an extremely simple and
  ** not very good hash function - biut works OK for
  ** names.
  */
  for( val=0; *ptr != '\0'; ptr++ ) {
    val = val + *ptr;
  }
  /*
  ** modulo the result so the output can be used
  ** as an index into the hash-table.
  */ 
  return val % BUCKETS;
}

/*
** Initialise the hash-table buckets to NULL.
*/
int init()
{
  int i;

  for(i=0; i<BUCKETS; i++) {
    bucket[i] = NULL;
  }

}

/*
** Add a new item to the hash-table.
*/
int add(ContactDetails *new)
{
  ContactDetails *llnew;
  int index;
  /*
  ** If we are not actually pointing to an item 
  ** throw an error
  */
  if( new == NULL ) {
    fprintf(stderr, "add: no contact information to add\n");
    return 1;
  }

  /*
  ** Request memory from the system to hold this new item
  ** Always check the return value of a system call!
  */
  llnew = (ContactDetails *)malloc(sizeof(ContactDetails));
  /*
  ** If our request failed throw an error. 
  */
  if( llnew == NULL) {
    fprintf(stderr, "add: Failed to get memory for new contact\n");
    return 1;
  }
  /*
  ** Copy the data from the contact data strcture into the new
  ** hash table data strcture.
  */
  strcpy(llnew->FamilyName,  new->FamilyName); 
  strcpy(llnew->GivenName,   new->GivenName); 
  strcpy(llnew->Phone,       new->Phone); 
  strcpy(llnew->Email,       new->Email);
  /*
  ** Find the index into the hash-table using the hash function
  */
  index = hash(llnew->FamilyName, llnew->GivenName);
  /*
  ** Add the new item at the start of the link list associated
  ** with the slot calculated by the hash function
  */
  llnew->next = bucket[index];
  bucket[index] = llnew;

  return 0;
}

ContactDetails *search(char *fname, char *gname)
{
  ContactDetails *current;
  unsigned int index;


  if( fname == NULL || gname == NULL ) {
    fprintf(stderr, "search: must supply given name and family name\n");
    return NULL;
  }

  index = hash(fname, gname);

  current = bucket[index];

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
  ContactDetails *current;
  unsigned int index;

  if( fname == NULL || gname == NULL ) {
    fprintf(stderr, "delete: must supply given name and family name\n");
    return NULL;
  }

  index = hash(fname, gname);

  current = bucket[index];

  while(current != NULL) {
    if( !strcmp(current->FamilyName, fname) && 
        !strcmp(current->GivenName, gname) ) {

      if( parent == NULL ) {
	bucket[index] = current->next;
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
  ContactDetails *current;
  int i;

  for(i=0; i<BUCKETS; i++) {
    current = bucket[i];
    while(current != NULL) {
      fprintf(stdout,"\nName: %s %s\n",
	      current->GivenName, current->FamilyName);
      fprintf(stdout,"Phone: %s\n",current->Phone);
      fprintf(stdout,"Email: %s\n",current->Email);

      current = current->next;
    }
  }
  return 0;
}
int count()
{
  ContactDetails *current;
  int i;
  int count;
  int total=0;

  for(i=0; i<BUCKETS; i++) {
    current = bucket[i];
    count = 0;
    while(current != NULL) {
      count++;
      current = current->next;
    }
    printf("Bucket(%d): %d\n",i,count);
    total += count;
  }
  printf("Total: %d\n",total);
  return 0;
}


  
