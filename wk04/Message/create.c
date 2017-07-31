#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <mqueue.h>

/*
** Create a message queue
*/

int main(int argc, char *argv[])
{
  mqd_t mqd;
  int flags;
  unsigned int prio = 0;
  struct mq_attr attr;

  /*
  ** Must have the name of the queue to create
  */
  if ( argc != 2 ) {
    fprintf(stderr,"Usage %s name msg [prio]\n",argv[0]);
    fprintf(stderr,"   name - name of message queue must start with a slash\n");
    exit(1);
  }
  /*
  ** Set the attributes of the queue: 
  **     the maximum number of messages, and 
  **     the maximum size of a message
  */
  attr.mq_maxmsg = 5;
  attr.mq_msgsize = 1024;
  /*
  ** Create the queue by opening it with the create option.
  */
  mqd = mq_open(argv[1], O_CREAT | O_RDWR, 0660, &attr);
  if(mqd == (mqd_t)-1) {
    error(2,errno,"mq_open failed");
  }

  exit(EXIT_SUCCESS);
}

  
