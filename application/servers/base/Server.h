/*
 * Server.h
 *	Server header file.
 *  Created on: Apr 23, 2013
 *       Author: Zachary Swartwood
 *      		 Nathan Zondlo
 */

#ifndef SERVER_H_
#define SERVER_H_

/* Include headers */
#include "../../base/Application.h"
#include "../../socket/base/Socket.h"

#include <vector>				// For vector STL container


class Server : public Application {


private:
	// structures used for this class
	typedef struct{
		// Pointer to a thread class instance
		Server		*serverInstance;

		// Copy of the clientfd created for this thread
		int			threadClientfd;
	} ThreadArgs;

private:

	void createConversationThread( int thisClientfd);


private:
	// Data members
	int clientfd;									//A client
	vector<pthread_t>		threads;

public:

	// Constructor and Destructor
	Server(Socket &sock);							//Constructor
	Server();
	virtual ~Server();

	// Server methods
	static void * conversationThread(void *tArgs);	// Used by pthread_create to create thread
	virtual void conversation(int thisClientfd) = 0;	// Must be implemented in derived class
	void runThreaded(Socket &s);							// Method that begins server loop

	// Interaction with socket
	void sockAccept();								//Accepts clients
	void closeClient(int thisClientfd);								//Closes the client

	void waitForThreads();

protected:

	int talking;						// Optional for conversation() loop in derived class
};

#endif /* SERVER_H_ */
