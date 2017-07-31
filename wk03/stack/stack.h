/*
** Header file defining the Contacts Structure
*/

#define SZ_FNAME 64
#define SZ_GNAME 32
#define SZ_PHONE 24
#define SZ_EMAIL 64

/*
** The structure that will be used to store the details
** of one contact.
*/
struct _contact_details {
  char FamilyName[SZ_FNAME];
  char GivenName[SZ_GNAME];
  char Phone[SZ_PHONE];
  char Email[SZ_EMAIL];
};

/*
** Use typedef to define the new type - this is purely
** as a convenience. Now we can use "ContactDetails"
** to mean "struct _contact_details" supposedly making
** the code easier to read.
*/  
typedef struct _contact_details ContactDetails;

/*
** Prototype Stack functions for the compiler. This will be needed
** by the contacts.c file when using these functions.
*/

/*
** Push a contact structure onto the stack
*/
int push(ContactDetails *);
/*
** Pop a contact structure off the stack
*/
ContactDetails *pop();
/*
** List all contacts on the stack
*/
int list();
/*
** Is the stack full?
*/
int full();
/*
** return the number of items on the stack
*/
int size();
