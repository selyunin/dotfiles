/*
 * socket_server_v3.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: selyunin
 */

#include <iostream>
#include <string.h>
#include "SocketServer.h"

int main(int argc, char** argv){



	char buffer[256];
	memset(buffer, 0, 256);

	const char * mstr = "quit";
	memcpy(buffer, mstr, strlen(mstr));
	cout <<strcmp(buffer, "quit")<<endl;


	SocketServer server;

	server.accept_connections();

	return 0;
}

