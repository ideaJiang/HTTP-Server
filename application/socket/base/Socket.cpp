/*
 * Socket.cpp
 *	Socket implementation that inherits from Application.
 *	Socket binds and listens on construction.
 *  Created on: Apr 18, 2013
 *      Author: Zachary Swartwood
 *      		Nathan Zondlo
 */

/* Header definition */
#include "Socket.h"

/* System Libs */
#include <netinet/in.h>			//Network sockets
#include <sys/socket.h>			//System sockets
#include <stdexcept>			//Standard Exception library

/* C-Derived Headers */
#include <cstdio>				//Standard Input/Output
#include <cstring>				//c string
#include <cstdlib>				//Standard Library


#define ASSIGN_FAIL (const string)("Socket Assign FAIL")
#define PORT_FAIL (const string)("Port Assign FAIL")
#define CLOSE_FAIL (const string)("Socket Close FAIL")
#define BIND_FAIL (const string)("Socket Bind FAIL")
#define LISTEN_FAIL (const string)("Socket Listen FAIL")

#define CLIENT_CONNECT_FAIL (const string)("Client Connection FAIL")
#define BUFFER_WRITE_FAIL (const string)("Buffer write FAIL")
#define BUFFER_READ_FAIL (const string)("Buffer read FAIL")

using namespace std;




/* Default constructor needed for inheritance */
Socket::Socket() : Application() {}

/* Optional constructor based on an int port */
Socket::Socket(int port) : Application(){

	// Socket construction logic
	construct(port);
}
/* Optional constructor based on args at runtime */
Socket::Socket(int argc, char **argv) : Application(){

	createSocket(argc, argv);

}
/* Destructor */
Socket::~Socket(){

	// Writes to log and closes socket
	logWrite("Close listening socket");
	close(sockfd);
}
void Socket::createSocket(int argc, char **argv){

	int port = 0;
	// If argument, make it int and assign to 'port' */
	if (argc > 1){
		port = strtol(argv[1], NULL, 0);
	}else
		throw(runtime_error("No arguments passed to program"));

	// Socket construction logic
	construct(port);

}
/* Common functionality between the two optional constructors */
void Socket::construct(int port){

	result = 0;

	// Declare/Initialize socket  and check
	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	if (sockfd == -1)throw (runtime_error(ASSIGN_FAIL));

	// Invalid port number, throw error
	if( port <= 0 || port > 65535)throw (runtime_error(PORT_FAIL));

	// Set the address to the computer's
	memset( &address, 0 , sizeof( address ) );
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( port );


	// Binds the socket
	sockBind();

	//  Listens on the socket
	sockListen();

}

/* Accepts clients */
void Socket::sockAccept(){

	// declare a variables for the client address
	struct sockaddr_in      client_addr;
	int                     client_addr_len;

	// initialize the client address
	memset( &client_addr, 0, sizeof( client_addr ) );

	// call accept to get a connection, throw error if failed
	clientfd = accept( sockfd, (struct sockaddr *) &client_addr, (unsigned int *) &client_addr_len );
	if (clientfd == -1) throw (runtime_error(CLIENT_CONNECT_FAIL));

}

/* Binds the socket */
void Socket::sockBind(){

	// Bind socket, throw error if failed
	result = bind( sockfd, (struct sockaddr *) &address, sizeof( address ) );
	if(result == -1) throw(runtime_error(BIND_FAIL));
}

/* Listens on the socket */
void Socket::sockListen(){

	//Listens on the socket
	result = listen(sockfd, 5);
	if(result == -1)throw(runtime_error(LISTEN_FAIL));

}

/* Reads in from the client */
string Socket::sockRead(int thisClientfd){

	// A read buffer
	char read_buffer[65535];
	memset( read_buffer, 0, sizeof( read_buffer) );

	// Bytes read in
	int read_bytes = 0;
	string input;

	// Reads from the client, throw error if failed
	read_bytes = read( thisClientfd, read_buffer, 65535 );
	if(read_bytes == -1) throw (runtime_error(BUFFER_READ_FAIL));

	input = read_buffer;

	//Returns the input
	return input;
}

/* Writes to the client */
void Socket::sockWrite(int thisClientfd, string &response){

	int bytes_written;

	// Writes back to the client, throw error if failed
	bytes_written = write( thisClientfd, response.c_str(), strlen( response.c_str() ) );
	if(bytes_written == -1) throw (runtime_error(BUFFER_WRITE_FAIL));

}

//Returns the sockfd
int Socket::getSockfd(){
	return sockfd;
}
// Returns the clientfd
int Socket::getClientfd(){
	return clientfd;
}



