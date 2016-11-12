/*
** talker.c - a datagram sockets "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT "6000"	               //the port users will be connecting to

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;          //AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_DGRAM;       //create UDP socket, SOCK_STREAM for TCP, SOCK_RAW to bypass transport layer
    hints.ai_flags = AI_PASSIVE;          //fill in my IP for me if no IP address or domain name is specified in getaddrinfo()

    //create structs for a socket
    if ((rv = getaddrinfo(NULL, SERVERPORT, &hints, &servinfo)) != 0) 
    {
	printf("Talker: getaddrinfo() error: %s\n", gai_strerror(rv));
	return 1;
    }

    //loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        //create a socket descriptor
	if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
	    printf("Talker: Error creating Socket Descriptor\n");
	    continue;
	}

	break;
    }

    if (p == NULL) 
    {
	printf("Talker: Socket Creation failed\n");
	return 2;
    }

    if ((numbytes = sendto(sockfd, "Hello World!", 12, 0, p->ai_addr, p->ai_addrlen)) == -1) 
    {
	printf("Talker: sendto() failed");
	exit(1);
    }

    freeaddrinfo(servinfo);

    printf("Talker: Sent %d bytes to Listener\n", numbytes);
    close(sockfd);

    return 0;
}
