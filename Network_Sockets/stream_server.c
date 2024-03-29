/*
** stream_server.c - a stream socket server demo
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
#include <sys/wait.h>
#include <signal.h>

#define PORT "6000"    //the port users will be connecting to

#define BACKLOG 10     //how many pending connections queue will hold

//reap zombie processes
void sigchld_handler(int s)
{
    //waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


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
    int sockfd, new_fd;                            //listen on sock_fd, service new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;            //client's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int status;

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

    //loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        //create a socket descriptor
        if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1)
        {
            printf("Server: Error creating Socket Descriptor\n");
            continue;
        }

        //remove any leftover sockets still present in the kernel for the given port
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) 
	{
            printf("Server: Address already in use");
            exit(1);
        }

	//bind socket to the IP address and port
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
	{
            close(sockfd);
            printf("Server: Error binding Socket Decriptor to IP Address and Port\n");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);                             //all done with this struct

    if (p == NULL)  
    {
        printf("Server: Socket Creation and Bind failed\n");
        exit(1);
    }

    //listen for incoming connections
    if (listen(sockfd, BACKLOG) == -1) 
    {
        printf("Server: listen() failed");
        exit(1);
    }

    //reap all zombie processes
    //sigaction() waits for a software interrupt (signal) which is triggered when a child process exits in this case
    //interrupt routine=sigchld_handler; it reaps the now zombie child process
    sa.sa_handler = sigchld_handler; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)        
    {
        printf("Server: sigaction() failed");
        exit(1);
    }

    printf("Server: waiting for connections...\n");

    //main accept() loop
    while(1) 
    {
        sin_size = sizeof(their_addr);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
	{
            printf("Server: accept() failed");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
        printf("Server: got connection from %s\n", s);

        if (!fork()) 
        {   //this is the child process
            close(sockfd);           //child doesn't need the listener
            if (send(new_fd, "Hello world!", 12, 0) == -1)
	    {
                printf("Server: send() failed");
	    }
            close(new_fd);
            exit(0);                 //terminate child process
        }
        close(new_fd);               //parent process doesn't need this
    }

    return 0;
}
