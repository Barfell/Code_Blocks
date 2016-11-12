/*
** listener.c - a datagram sockets "server" demo
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

#define MYPORT "6000"            //the port users will be connecting to

#define MAXBUFLEN 100

//get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) 
    {
	return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;         //listen on sock_fd
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;           //client's address information
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;          //AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_DGRAM;       //create UDP socket, SOCK_STREAM for TCP, SOCK_RAW to bypass transport layer
    hints.ai_flags = AI_PASSIVE;          //fill in my IP for me if no IP address or domain name is specified in getaddrinfo()

    //create structs for a socket
    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) 
    {
	printf("Listener: getaddrinfo() error: %s\n", gai_strerror(rv));
	return 1;
    }

    //loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        //create a socket descriptor
	if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
	    printf("Listener: Error creating Socket Descriptor\n");
	    continue;
	}

        //bind socket to the IP address and port
	if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
	    close(sockfd);
	    printf("Listener: Error binding Socket Decriptor to IP Address and Port\n");
	    continue;
	}

	break;
    }

    if (p == NULL) 
    {
	printf("Listener: Socket Creation and Bind failed\n");
	return 2;
    }

    freeaddrinfo(servinfo);                            //all done with this struct

    printf("Listener: waiting to recvfrom()...\n");

    addr_len = sizeof(their_addr);
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) 
    {
	printf("Listener: recvfrom() failed");
	exit(1);
    }

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
    printf("Listener: Got packet from %s\n", s);
    printf("Listener: Packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("Listener: Packet contains \"%s\"\n", buf);

    close(sockfd);

    return 0;
}
