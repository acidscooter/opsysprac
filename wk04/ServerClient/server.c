#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include <time.h>

/*
** Example of IPC via sockets over a network
**
** This is the server which listens for connections
*/

#define BUFF_SIZE 128
/*
** Port to listen on
*/
#define PORT 5000

int main(int argc, char *argv[])
{
    int listenfd = 0;
    int connfd = 0;
    int n;
    struct sockaddr_in saddr; 
    char buff[BUFF_SIZE];
    time_t ticks; 
    /*
    ** Initialise structure and buffer memory to zero
    */ 
    memset(&saddr, '\0', sizeof(saddr));
    memset(buff, '\0', BUFF_SIZE); 
    /*
    ** request a socket that will use Internet protocols
    ** and establich a two-way stream connection (TCP)
    */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if( listenfd < 0 )
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } ;
    /*
    ** Need to assign an address to the socket - that is
    ** (since this is the server) which port to listen on.
    ** bind assigns the address found in saddr to the socket.
    ** (Note: the port number must be in Internet byte order
    ** (big endian) which may not be the same as your machine's architecture)
    */
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(PORT); 

    bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr)); 
    /*
    ** This is a passive socket, the server plans to listen for incoming
    ** connections.
    */
    listen(listenfd, 10); 

    while(1)
    {
        /*
        ** Block and wait for an incoming request
        */
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        printf("Client connection received\n");
        /*
	** Read the expected salutation from the client
        */
        printf("Client salutation: ");
        n = read(connfd, buff, BUFF_SIZE-1);
        if( n < 0 ) {
	  printf("Error reading salutation from client\n");
        } else {
          buff[n] = '\0';
          printf("%s\n", buff);
        }
        /*
	** Send the current time back to the client
        */
        ticks = time(NULL);
        snprintf(buff, BUFF_SIZE-1, "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff)); 
        /*
	** Finished so close the connection
        */
        close(connfd);
        sleep(1);
     }
}
