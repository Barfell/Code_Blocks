/*
** showip.c - show IP address(s) for a host
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;          //AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;      //create TCP socket, SOCK_DGRAM for UDP, SOCK_RAW to bypass transport layer
    hints.ai_flags = AI_PASSIVE;          //fill in my IP for me if no IP address or domain name is specified

    //create structs for a socket
    if ((status = getaddrinfo("www.google.se", "telnet", &hints, &res)) != 0)            
    {
        printf("getaddrinfo() error: %s\n", gai_strerror(status));
        return 1;
    }

    printf("IP address:\n\n");

    //iterate through linked list of structs returned by getaddrinfo()
    for(p = res; p != NULL; p = p->ai_next)           
    {
        void *addr;
        char *ipver;

        //get the pointer to the IP address itself,
        if (p->ai_family == AF_INET)     //IPv4
	{
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } 
	else     //IPv6
	{ 
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        //convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("  %s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res); // free dynamically allocated memory of the linked list

    return 0;
}

