/*
** Header file defining the Contacts Structure
*/

#define SZ_FNAME 64
#define SZ_GNAME 32
#define SZ_PHONE 24
#define SZ_EMAIL 64

/*
** The structure that will be used to store the details
** of one contact. Note the pointer to the next 
** structure in the list.
*/
struct _contact_details {
  char FamilyName[SZ_FNAME];
  char GivenName[SZ_GNAME];
  char Phone[SZ_PHONE];
  char Email[SZ_EMAIL];
  struct _contact_details *next;
};

/*
** Use typedef to define the new type - this is purely
** as a convenience. Now we can use "ContactDetails"
** to mean "struct _contact_details" supposedly making
** the code easier to read.
*/  
typedef struct _contact_details ContactDetails;

/*
** Prototype Link-List functions for the compiler. This will be needed
** by the contacts.c file when using these functions.
*/

/*
** Add a contact structure to the list
*/
int add(ContactDetails *new);
/*
** Delete a contact structure from the list
*/
ContactDetails *delete(char *fname, char *gname);
/*
** Search the list for a specific contact structure.
*/
ContactDetails *search(char *fname, char *gname);
/*
** List all contacts in the link-list.
*/
int list();
