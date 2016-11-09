/*
** stream_client.c - a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "6000"          //the port client will be connecting to 
#define MAXDATASIZE 100      //max number of bytes we can get at once 

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
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int status;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;          //AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;      //create TCP socket, SOCK_DGRAM for UDP, SOCK_RAW to bypass transport layer
    hints.ai_flags = AI_PASSIVE;          //fill in my IP for me if no IP address or domain name is specified in getaddrinfo()

    //create structs for a socket
    if ((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)            
    {
        printf("Server: getaddrinfo() error: %s\n", gai_strerror(status));
        exit(1);
    }

    //loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
	//create a socket descriptor
	if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
            printf("Client: Error creating Socket Descriptor\n");
	    continue;
	}

	//connect to server
	if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            printf("Client: Error connecting to server\n");
	    close(sockfd);
	    continue;
	}

	break;
    }

    if (p == NULL) 
    {
	printf("Client: Failed to connect to a server\n");
	return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("Client: Connecting to %s\n", s);

    freeaddrinfo(servinfo);                   //all done with this struct

    //receive messages from server
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) 
    {
        printf("Client: Error receiving messages from server");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("Client: Received '%s' from server\n",buf);

    close(sockfd);                            //close socket

    return 0;
}

