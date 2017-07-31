#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

/*
** Using shared memory to communicate between processes
*/

/*
** Size of the shared memory
*/
#define STRING_LENGTH  32

/*
** Message parent will send to child
*/
#define PARENT_MESSAGE "Message from Parent"
/*
** Message child will send to parent
*/
#define CHILD_MESSAGE  "Message from Child"

int main() {
  pid_t pid;
  int ret;
    
  /*
  ** Map a shared region of memory for reading and writing
  ** into the address space of the process.
  */
  char *shm  = mmap(NULL, 
                    sizeof(char)*STRING_LENGTH, 
                    PROT_READ | PROT_WRITE, 
                    MAP_ANONYMOUS | MAP_SHARED, 
                    -1, 0);
  /*
  ** Set stdout to be unbuffered otherwise there will be some odd
  ** interleaving between the output from the two processes
  */ 
  setbuf(stdout, NULL);

  /*
  ** fork to create the child process
  */
  pid = fork();  
  if (pid < 0) {
      perror("Fork failed!");
      exit(1);
  }
  /*
  ** Child process
  */
  if( pid == 0 ) {
    sleep(1);
    /*
    ** Print out what is in shared memory
    */
    printf("Child Process: %s\n",shm);
    /*
    ** Write the Child's message to shared memory
    */
    sprintf(shm,CHILD_MESSAGE);
    exit(0);
  }
  /*
  ** Parent Process
  **
  ** Write the Parent's message to shared memory
  */
  sprintf(shm,PARENT_MESSAGE);
  sleep(2);
  /*
  ** Print out what is in shared memory
  */ 
  printf("Parent Process: %s\n",shm);
  /*
  ** Wait for the child to terminate
  */
  wait();
  /*
  ** Unmap the shared memory
  */
  munmap(shm,sizeof(char)*STRING_LENGTH);
  exit(0);
}
