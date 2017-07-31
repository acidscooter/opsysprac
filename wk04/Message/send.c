#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <mqueue.h>

/*
** Send a  message to a message queue
*/

int main(int argc, char *argv[])
{
  mqd_t mqd;
  int flags;
  unsigned int prio = 0;

  /*
  ** Check we have all the information required
  */
  if ( argc < 3 || argc > 4 ) {
    fprintf(stderr,"Usage %s name msg [prio]\n",argv[0]);
    fprintf(stderr,"   name - name of message queue\n");
    fprintf(stderr,"   msg - message to send\n");
    fprintf(stderr,"   prio - optional priority, must be positive, 0-low\n");
    exit(1);
  }
  /*
  ** Optional third argument is the priority of the message
  ** the priority re-orders the queue
  */
  if( argc == 4 ) {
    prio = atoi(argv[3]);
  }
  /*
  ** open the ques for writing only
  */
  mqd = mq_open(argv[1], O_WRONLY );
  if(mqd == (mqd_t)-1) {
    error(2,errno,"mq_open failed");
  }
  /*
  ** Send the message on the command line to the queue
  */
  if( mq_send(mqd, argv[2], strlen(argv[2]), prio) == -1 ) {
    error(3,errno,"mq_send failed");
  }

  exit(EXIT_SUCCESS);
}

  
