#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
** A list of contacts implemented as a linked-list
*/

#include "linklists.h"

/*
** prototype local functions used
*/
int readline(FILE *, char *, int);
int load(char *);
/*
** Size of input buffer
*/
#define NBUFF 10

int main()
{
  char action[NBUFF];
  ContactDetails new;
  ContactDetails *ptr;
  char fname[SZ_FNAME];
  char gname[SZ_GNAME];

  /*
  ** generic input loop reads a line of input from the
  ** user at a time.
  */
  while(1) {
   
    /*
    ** Output a prompt and get the response from the user
    */
    printf("\nEnter action: ");
    readline(stdin, action, NBUFF);

    /*
    ** Keyword: quit
    */
    if( !strncmp(action,"quit",4) ) {
      exit(1);
    }

    /*
    ** Keyword: load
    ** Action: load the contacts from a file
    */
    if( !strncmp(action,"load",4) ) {
      printf("Filename: ");
      readline(stdin, fname, SZ_FNAME);
      load(fname);
    }
    
    /*
    ** Keyword: add
    ** Action: get the data for a contact and add it
    **         to the list
    */
    if( !strncmp(action,"add",3) ) {
      printf("\nFamily Name: ");
      readline(stdin, new.FamilyName, SZ_FNAME);
      printf("Given Name: ");
      readline(stdin, new.GivenName, SZ_GNAME);
      printf("Phone: ");
      readline(stdin, new.Phone, SZ_PHONE);
      printf("Email: ");
      readline(stdin, new.Email, SZ_EMAIL);
      add(&new);
    }

    /*
    ** Keyword: list
    ** Action: list all contacts in the list
    */
    if( !strncmp(action,"list",4) ) {
      list();
    }

    /*
    ** Keyword: delete
    ** Action: delete an entry out of the list
    */
    if( !strncmp(action,"delete",6) ) {
      printf("\nFamily Name: ");
      readline(stdin, fname, SZ_FNAME);
      printf("Given Name: ");
      readline(stdin, gname, SZ_GNAME);

      ptr = delete(fname,gname);
      if(ptr != NULL) {
         printf("\nName: %s %s\n",ptr->GivenName, ptr->FamilyName);
         printf("Phone: %s\n",ptr->Phone);
         printf("Email: %s\n",ptr->Email);
         free(ptr);
      }
    }

    /*
    ** Keyword: find
    ** Action: find an entry in the list
    */
    if( !strncmp(action,"find",4) ) {
      printf("\nFamily Name: ");
      readline(stdin, fname, SZ_FNAME);
      printf("Given Name: ");
      readline(stdin, gname, SZ_GNAME);

      ptr = search(fname,gname);
      if(ptr != NULL) {
         printf("\nName: %s %s\n",ptr->GivenName, ptr->FamilyName);
         printf("Phone: %s\n",ptr->Phone);
         printf("Email: %s\n",ptr->Email);
      }
    }

    /*
    ** Keyword: help
    ** Action: Print out list of actions
    */
     if( !strncmp(action,"help",4) ) {
      printf("Actions available: quit, add, list, delete, find, load\n");
    }

  }
}

/*
** Read a line from a file (this includes standard in)
** Parameters:
**    fptr: file to read the line of text from.
**    string: the string buffer to contain the characters.
**    maxchar: Maximum number of characters to read including
**             the end of string NULL character and the end-of-line
**             character.     
*/
int readline(FILE *fptr, char *string, int maxchar)
{
  char *eol;
  /*
  ** Parameter Error checking
  */
  if( string == NULL || fptr == NULL || maxchar < 1 ) {
    return 0;
  }
  /*
  ** Use the safe fgets to read the line of characters
  */
  fgets(string, maxchar, fptr);
  /*
  ** fgets also reads the end-of-line character which 
  ** we don't want so we will replace it with a NULL character
  ** the end of string character.
  ** EOL character:
  **               Unix: newline
  **               MacOS: carriage-return
  **               Dos: carriage-return & newline
  */
   eol = strchr(string, '\r');
  if( eol != NULL ) {
    *eol = '\0';
  } else {
    eol = strchr(string, '\n');
    if( eol != NULL ) {
      *eol = '\0';
    }
  }
  /*
  ** Return the number of useful characters read.
  */ 
  return strlen(string);
}

/*
** Load a heap of contacts from a file
** Parameters:
**      fname: file that contains the contacts
** Assumed Format of the file:
**      Family Name
**      Given Name
**      Phone
**      Email
*/
int load(char *fname)
{
  FILE *fptr;
  ContactDetails new;  

  /*
  ** Parameter error checking
  */
  if(fname == NULL || strlen(fname) == 0) {
    fprintf(stderr, "load: must supply a file name\n");
    return 1;
  }
     
  /*
  ** open the file for reading and always check if it was successful
  */   
  fptr = fopen(fname,"r");

  if(fptr == NULL) {
    fprintf(stderr, "load: failed to open the file '%s'\n", fname);
    return 1;
  }
  /*
  ** Loop through the file reading four lines at a time
  */
  while ( 1 ) {
      readline(fptr, new.FamilyName, SZ_FNAME);
      readline(fptr, new.GivenName, SZ_GNAME);
      readline(fptr, new.Phone, SZ_PHONE);
      readline(fptr, new.Email, SZ_EMAIL);
      if( !feof(fptr) && !ferror(fptr) ) {
         add(&new);
      } else {
	break;
      }
 }
 close(fptr);
 return 0;
}
