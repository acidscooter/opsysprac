#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

/*
** Example of IPC via sockets over a network
**
** This is the client which connects to the listening server
*/

#define PORT 5000
/*
** Port to connect to
*/
#define BUFF_SIZE 128

int main(int argc, char *argv[])
{
    int sockfd = 0;
    int n = 0;
    char buff[BUFF_SIZE];
    struct sockaddr_in saddr; 
    /*
    ** Need the IP address of the server and an opening salution
    ** to send to the server.
    */
    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> salutation\n",argv[0]);
        return 1;
    } 
    /*
    ** Initialise structure and buffer memory to zero
    */ 
    memset(&saddr, '\0', sizeof(saddr));
    memset(buff, '\0', BUFF_SIZE); 
    /*
    ** request a socket that will use Internet protocols
    ** and establich a two-way stream connection (TCP)
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0 )
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    /*
    ** Need to connect the socket to an address - that is
    ** the IP address of the machine and the port.
    ** Connect does this.
    ** (Note: IP address and port number must be in Internet byte order
    ** (big endian) which may not be the same as your machine's architecture)
    */
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT); 

    /*
    ** Convert string to proper network address
    */
    if(inet_pton(AF_INET, argv[1], &saddr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
    /*
    ** Attempt to connect to server
    */
    if( connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }
    /*
    ** Write salutation to server
    */
    if( write(sockfd, argv[2], strlen(argv[2])) < 1 ) {
       printf("\n Error : Sending Salutation\n");
       return 1;
    }
    /*
    ** Read server's response
    */
    printf("Server Response: ");
    n = read(sockfd, buff, BUFF_SIZE-1);
    if(n < 0)
    {
        printf("\n Read error \n");
    } 
        
    buff[n] = '\0';
    printf("%s\n", buff);

    return 0;
}
