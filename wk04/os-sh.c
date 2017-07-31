#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/*
** This program implements a simple shell!
*/


/*
** Maximum number of command-line arguments for the executable
*/
#define MAX_ARGS  31

/*
** Paths to be searched for executables
*/
char *path[]={"/usr/bin", "/bin", "/usr/local/bin", ".", NULL};

/*
** maximum length of executable filename including path
*/
#define MAX_FILE_SIZE 128

/*
** full path to executable (note a global variable)
*/
char filename[MAX_FILE_SIZE];

/*
** Function to search for the executable using the predefined
** directories in path.
*/
int statcmd(char *cmd) {
  struct stat sb;
  char *dir;
  int i = 0;
  /*
  ** Go through each directory in the path array looking
  ** for the executable. 
  ** NULL element means we are at the end of the array.
  */
  while( (dir=path[i]) != NULL ) {
    i++;
    /*
    ** Have we reserved enough space for the path+fileanme?
    */
    if( strlen(dir)+strlen(cmd)+2 > MAX_FILE_SIZE ) continue;
    /*
    ** Create e full path to the executable
    */
    strcpy(filename,dir);
    strcat(filename,"/");
    strcat(filename,cmd);
    /*
    ** Use the 'stat' system call to find out the properties of the
    ** the file. See 'man 2 stat'
    */
    if( stat(filename, &sb) ) continue;
    /*
    ** Is it a regular file? And is it an executable?
    */
    if( S_ISREG(sb.st_mode) && ( 
            (sb.st_mode  & S_IXUSR) ||
            (sb.st_mode  & S_IXGRP) ||
            (sb.st_mode  & S_IXOTH) ) ) return 0;
  }
  printf("Cannot stat command: %s\n",cmd);
  return 1;
}


int main(int argc, char *argv[]) {
  int i;
  char *line = NULL;
  char *args[MAX_ARGS+1];
  char *cmd = NULL;
  char *token;
  pid_t pid;
  int status;
  int background;


  while(1) {
    /*
    ** Initialise variables for a new input line
    */
    background = 0;
    for(i=0; i<=MAX_ARGS; i++) {
          args[i]=NULL;
    }
    free(line);
    /*
    ** Read a line from stdin using the readline function
    */
    line = readline("os-sh> ");
    if( line == NULL ) exit(0);
    if( strlen(line) == 0 ) continue;
    /*
    ** Pull the line apart into words (separated by white space)
    ** Use the C-library strtok command.
    **
    ** grap the actual command and store it in our args array
    */
    i=0;
    args[0] = strtok(line," 	");
    if( args[0] == NULL || strlen(args[0]) == 0 ) continue;
    i++;
    /*
    ** loop grabbing each word and putting it into args
    */
    while( i<MAX_ARGS && (args[i]=strtok(NULL," 	")) != NULL ) {i++;}
    /*
    ** Check to see if the executable exists and find its full path
    */
    if( statcmd(args[0]) ) continue;
    args[0] = filename;
    /*
    ** if the last word is an ampersand this means the shell
    ** should not wait for the command to finish but return with the prompt
    ** ready to accept a new command.
    */
    if ( strncmp(args[i-1],"&",1) == 0 ) {
      args[i-1]=NULL;
      background = 1;
    }

    /*
    ** execute the command by first forking
    */
    pid = fork();
    if( pid < 0 ) {
      printf("Error forking!\n");
      exit(2);
    }

    /*
    ** We are the child process so execute the command
    */
    if( pid == 0 ) {
      execv(filename, args);
    } 

    /*
    ** We are the parent process so wait for child to terminate
    */
    waitpid(pid,&status,0);

  }


}
