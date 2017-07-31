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
** Push a contact structure onto the end of the queue
*/
int push(ContactDetails *new);
/*
** Pop a contact structure off the beginning of the queue
*/
ContactDetails *pop();
/*
** List all contacts on the stack
*/
int list();
