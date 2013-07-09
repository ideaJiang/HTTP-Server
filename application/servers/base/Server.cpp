/*
 * Server.cpp
 *	Server implementation that inherits from Application.
 *	Accepts connections, reads, and writes.
 *  Created on: Apr 23, 2013
 *      Author: Zachary Swartwood
 *      		Nathan Zondlo
 */

/* Header definition */
#include "Server.h"

/* System headers */
#include <string>				// String Library
#include <stdexcept>			// Standard Exception library

/* C-derived headers*/
#include <pthread.h>			// POSIX Threads
#include <cstdio>				// Standard Input/Output
#include <cstring>				// String Header
#include <cstdlib>				// Standard Library
#include <cerrno>				// Error codes



/* Server constructor that takes a socket */
Server::Server(Socket &sock) : Application(){

	clientfd = sock.getClientfd();
	runThreaded(sock);
}

/* Default constructor */
Server::Server(){}

/* Server destructor */
Server::~Server(){

	// Close client
	logWrite("Closing client connection");
	close(clientfd);
}

/* Loop that continually accepts client connections, using implemented conversation() */
void Server::runThreaded(Socket &sock){

	logWrite("Starting Server");

	// Do forever
	while(true){

		// Accept a connection from a user
		sock.sockAccept();

		// Assign our client file descriptor
		clientfd = sock.getClientfd();

		createConversationThread(clientfd);

		// Talk with client
		// conversation(clientfd);
	}
}

/* Closes the client connection */
void Server::closeClient(int thisClientfd){

	// Close client
	logWrite("Closing client connection");
	close(thisClientfd);
}

/* start a Server thread */
void Server::createConversationThread(int thisClientfd){
	// this holds a thread identifier
	//		returned from pthread_create
	pthread_t	thread;

	// structure for thread arguments
	//		it is using new because we
	//		want it to continue to exist
	//		after this function has ended.
	//		if it was a local variable, it
	//		would be deleted at the end of this
	//		function. we may still want it after
	//		that.
	ThreadArgs *arguments = new ThreadArgs;

	// set the arguments
	//		this is a reference
	//		to the class instance. we are going
	//		to pass it to HelloWorldThread so that
	//		it can call HelloWorld. the thread number
	//		will be used by HelloWorld to show which
	//		thread is producing the output. this is how
	//		you would pass multiple arguments to a thread.
	//		you can add as many arguments as you need.
	arguments->serverInstance	=	this;
	arguments->threadClientfd	=   thisClientfd;

	// create and start the thread
	//		the second argument is attributes
	//		for the thread. we are not setting
	//		any attributes.
	int	result	=	pthread_create( &thread, NULL, conversationThread, arguments );

	// check for an error
	//		pthread_create returns zero if success
	//		and something else if an error
	if ( result != 0 ){

		// build an error message
		stringstream	Message;
		Message<<"Error creating thread: "<<errno<<" - "<<strerror(errno);
		throw( runtime_error( Message.str() ));
	}

	// add to the thread list
	threads.push_back( thread );

	// return finished
	return;
}

void * Server::conversationThread(void *tArgs){

	sleep(10);

	// recast the arg to the threadarguments
	//		structure. this is because Arg
	//		is a pointer to a void.
	ThreadArgs *arguments = (ThreadArgs*) tArgs;

	// call the conversation of the class instance
	//		passed in the arguments
	arguments->serverInstance->conversation(arguments->threadClientfd);

	delete arguments;
	return (0);
}

// this method waits for all threads to complete
void Server::waitForThreads(){

	// run through the vector of thread identifiers
	//		when this loop is complete, all threads
	//		will be done.
	for( vector<pthread_t>::iterator ID = threads.begin(); ID != threads.end(); ID++ )
	{
		// this call will not return until the
		//		thread has completed its processing.
		//		if it is already complete, the call
		//		will return immediately.
		pthread_join( (*ID), NULL );
	}

	// return finished
	return;
}

