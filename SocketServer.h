/*
 * SocketServer.h
 *
 */

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPv4_PORT_NUMBER 	14014
#define IPv4_IP_ADDRESS		"127.0.0.1"
#define PENDING_CONNECTIONS_MAX	10

#include <iostream>

using namespace std;

class SocketServer {
public:
	SocketServer();

	void accept_connections();

	int handle_request();

	void error(const char *msg);

	virtual ~SocketServer();


//private:
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    struct in_addr inp;
    int cli_quit;
//    int n;

};

#endif /* SOCKETSERVER_H_ */
