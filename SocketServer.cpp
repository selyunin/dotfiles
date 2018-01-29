/*
 * SocketServer.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: selyunin
 */

#include "SocketServer.h"
#include <iomanip>

void SocketServer::error(const char* msg)
{
    perror(msg);
    exit(1);
}

SocketServer::SocketServer() {
	cli_quit = 0;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
	   error("ERROR opening socket");
	}

	/* re-connect to socket when TIME OUT state */
	int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
		error("setsockopt(SO_REUSEADDR) failed");
	}
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = IPv4_PORT_NUMBER;
    serv_addr.sin_family = AF_INET;

	if (inet_aton(IPv4_IP_ADDRESS, &inp) == 0){
		printf("inet_aton failed!\n");
	}
	printf("inet_aton = %x\n", inp.s_addr);

    serv_addr.sin_addr = inp;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd,
    		(struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0){
             error("ERROR on binding");
    }
    listen(sockfd,PENDING_CONNECTIONS_MAX);
    clilen = sizeof(cli_addr);
    cout<<"socket configuration done"<<endl;
}

void SocketServer::accept_connections(){
	do {

	     newsockfd = accept(sockfd,
	                 	    (struct sockaddr *) &cli_addr,
							&clilen);
	     if (newsockfd < 0){
	          error("ERROR on accept");
	     }
		 cout<<"Processing request: "<<newsockfd<<endl;
	     cli_quit = handle_request();

	} while(!cli_quit);

}

int SocketServer::handle_request(){
	bzero(buffer,256);
	int read_status = read(newsockfd, buffer, 255);
	if (read_status < 0) error("ERROR reading from socket");{
	  printf("Here is the message: %s\n",buffer);
	}
	const char* server_response = "Server got your message";
	int write_status = write(newsockfd,server_response,strlen(server_response));
	if (write_status < 0) {
		error("ERROR writing to socket");
	}

	printf("buffer: %s\n", buffer);
	for (unsigned idx=0; idx < 64; idx++){
//		cout<<hex<<buffer[idx]<<"|";
		printf("%x|", buffer[idx]);
	}cout<<endl;

	const char * msg_quit = "quit";
	for (unsigned idx = 0; idx < strlen(msg_quit); idx++){
		printf("%x|", msg_quit[idx]);
	}cout<<endl;
	cout <<"strcmp "<<strcmp(buffer, "tiuq")<<endl;
	if (strcmp(buffer, "quit") == 0){
		cout<<"Quit"<<endl;
		return 1;
	} else {
		cout<<"Go on"<<endl;
		return 0;
	}
}

//	do {
//			struct sockaddr client_name;
//			socklen_t client_name_len;
//			int client_socket_fd;
//			/* Accept a connection. */
//			client_socket_fd = accept(socket_fd, &client_name, &client_name_len);
//			/* Handle the connection. */
//			client_sent_quit_message = server (client_socket_fd);
//			/* Close our end of the connection. */
//			close (client_socket_fd);
//		} while (!client_sent_quit_message);


SocketServer::~SocketServer() {
    close(newsockfd);
    close(sockfd);
}

