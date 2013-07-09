/*
 * Socket.h
 *	Socket file header
 *  Created on: Apr 18, 2013
 *       Author: Zachary Swartwood
 *      		 Nathan Zondlo
 */

#ifndef SOCKET_H_
#define SOCKET_H_

/* Implementation Header */
#include "../../base/Application.h"

/* Network sockets */
#include <netinet/in.h>			//Network sockets
#include <sys/socket.h>			//System sockets


class Socket : public Application {
public:
	//Constructors
	Socket(int port);							// Construct with int
	Socket(int argc, char **argv);				// Construct with arguments
	Socket();									// Blank object

	//Deconstructor
	virtual ~Socket();

	void createSocket(int argc, char **argv);	// Create socket method
	void sockAccept();							// Accepts socket
	void sockBind();							// Binds
	void sockListen();							// Listens
	string sockRead(int thisClientfd);							// Reads input from user
	void sockWrite(int thisClientfd, string &response);			// Writes response back to user
	void closeSocket();							// Closes the socket

	// Member methods
	int getSockfd();							// Returns the sockfd
	int getClientfd();							// Returns clientfd

private:

	// Sock Address structure
	struct sockaddr_in    address;

	// Instance fields
	int clientfd;								// Client file descriptor
	int sockfd;									// Socket file descriptor
	int result;									// result of error checking

	// Internal methods
	void construct(int port);

};

#endif /* SOCKET_H_ */
