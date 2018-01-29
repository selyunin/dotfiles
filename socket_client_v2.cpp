/*
 * socket_client_v2.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: selyunin
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        error("setsockopt(SO_REUSEADDR) failed");

//    server = gethostbyname(argv[1]);

//    if (server == NULL) {
//        fprintf(stderr,"ERROR, no such host\n");
//        exit(0);
//    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    //***
//    bcopy((char *)server->h_addr,
//         (char *)&serv_addr.sin_addr.s_addr,
//         server->h_length);
//    server->h_name;

    struct in_addr inp;
	int inet_res = inet_aton(argv[1], &inp);
	if (inet_res == 0){
		printf("inet_aton failed!\n");
	}
	printf("inet_aton = %x\n", inp.s_addr);

//    printf("server->h_name: %s\n", (char *)server->h_name);
//    printf("server->h_addr: %s\n", (char *)server->h_addr);
    printf("serv_addr.sin_addr.s_addr: %s\n", (char *)&serv_addr.sin_addr.s_addr);

    serv_addr.sin_addr = inp;
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    }

    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0){
         error("ERROR writing to socket");
    }
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0){
         error("ERROR reading from socket");
    }
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}


