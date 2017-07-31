#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <mqueue.h>

/*
** Read a message from a message queue
*/



int main(int argc, char *argv[])
{
  mqd_t mqd;
  unsigned int prio = 0;
  struct mq_attr attr;
  char *buffer;
  ssize_t nRead;

  /*
  ** Must have the name of the queue to read messages from
  */
  if ( argc != 2 ) {
    fprintf(stderr,"Usage %s name msg [prio]\n",argv[0]);
    fprintf(stderr,"   name - name of message queue\n");
    exit(1);
  }
  /*
  ** Open the ques for read only
  */
  mqd = mq_open(argv[1], O_RDONLY);
  if(mqd == (mqd_t)-1) {
    error(2,errno,"mq_open failed");
  }
  /*
  ** Get the attributes of the queue - we need to know
  ** the largest message size
  */
  if( mq_getattr(mqd,&attr) == -1 ) {
    error(3,errno,"mq_getattr failed");
  }
  /*
  ** request memory so we can store the largest possible message.
  */
  buffer = (char *)malloc(attr.mq_msgsize);
  if(buffer == NULL) {
    fprintf(stderr,"Malloc failed\n");
    exit(4);
  }
  /*
  ** read one message from the queue
  */
  nRead = mq_receive(mqd, buffer, attr.mq_msgsize, &prio);
  if(nRead == -1 ) {
    error(3,errno,"mq_receive failed");
  }
  /*
  ** print our the message
  */
  printf("Read %d bytes; priority=%u\n", (int)nRead, prio);
  write(STDOUT_FILENO, buffer, nRead);
  write(STDOUT_FILENO, "\n", 1);


  exit(EXIT_SUCCESS);
}

  
