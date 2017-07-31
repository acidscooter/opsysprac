#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <error.h>
#include <errno.h>

/*
** Inter-process communication using a unidirectional pipe.
*/

/*
** Set the size of the Read buffer - string to hold the read characters.
*/
#define RBUF_SIZE 10

int main(int argc, char *argv[])
{
  int pfd[2];
  char rbuf[RBUF_SIZE];
  ssize_t nRead;
  pid_t pid;
  /*
  ** See that we have a string to send down the pipe.
  */
  if(argc != 2 || strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-h") == 0)
  {
    printf("Usage: %s string-to-send\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  /*
  ** Create the pipe. The array pfd[2] holds the files descripters for
  ** each end of the pipe.
  */ 
  if( pipe(pfd) < 0 ) {
    error(2,errno,"Failed to create pipe\n");
  }
  /*
  ** Fork this process so we have a child to talk to.
  ** Always check the return values from system calls as
  ** they are not always successful.
  */
  printf("Forking process\n");

  pid = fork();
  if( pid < 0 ) {
    error(3,errno,"Failed to fork\n");
  }
  

  /*
  ** Child Process Code
  */
  if( pid == 0 ) {
    /*
    ** The child will be reading data sent down the pipe by the parent
    ** so close the writing end - the child does not need it.
    */
    if( close(pfd[1]) == -1 ) {
      error(4,errno,"Child failed to close write end of pipe\n");
    }
    /*
    ** Sleep for 1 second to give the parent time to send message.
    */
    sleep(1);
    /*
    ** We will not use standard C-library output functions because 
    ** mixing system I/O with C-library I/O causes unexpected interleaving
    ** of output due to different buffering mechanisms and because 
    ** there is no newline. So to keep
    ** output in the correct order we will use system write() calls
    ** see man 2 write
    */ 
    write(STDOUT_FILENO,"Child: String received down pipe: ",34);
    /*
    ** Grab output on the pipe in RBUF_SIZE chunks and output it
    */
    while (1) {
      /*
      ** read an RBUF_SIZE chunk into rbuf
      */
      nRead = read(pfd[0], rbuf, RBUF_SIZE);
      if(nRead == -1) {
         error(5,errno,"Child failed to read from pipe\n");
      }
      /*
      ** No data to read must have it all
      */
      if(nRead == 0) {
        break;
      }
      /*
      ** Write this chunk to standard out
      */
      if( write(STDOUT_FILENO, rbuf, nRead) != nRead ) {
         error(6,errno,"Child write to stdout failed\n");
      }
    }
    /*
    ** Add a final new line to output
    */
    write(STDOUT_FILENO, "\n", 1);
    /*
    ** Finished so close read end of the pipe
    */
    if ( close(pfd[0]) == -1 ) {
      error(7,errno,"Child failed to close read end of pipe\n");
    }
    exit(EXIT_SUCCESS);
  }

  /*
  ** Parent Process Code
  **
  ** The parent will be writing data down the pipe
  ** so close the reading end - the parent does not need it.
  */
  if( close(pfd[0]) == -1 ) {
    error(4,errno,"Parent failed to close read end of pipe\n");
  }

  printf("Parent: String to send down pipe: %s\n", argv[1]);
  /*
  ** Write the string to the pipe
  */
  if( write(pfd[1], argv[1], strlen(argv[1]) ) != strlen(argv[1]) ) {
     error(5,errno,"Parent write to pipe failed\n");
  }
  /*
  ** Finished so close the write end of the pipe.
  */  
  if( close(pfd[1]) == -1 ) {
    error(6,errno,"Parent failed to close write end of pipe\n");
  }

  /*
  ** Wait for the child process to terminate
  */
  wait(NULL);

  exit(EXIT_SUCCESS);

}

  
