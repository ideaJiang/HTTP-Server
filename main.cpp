/*
 * main.cpp
 *
 *  Created on: May 5, 2013
 *      Author: Nathan Zondlo
 *      		Zachary Swartwood
 *        Name: ZaN Server v0.2.2
 * Description: Deliverable 1 (4/30/13)
 * 				-The main for project 2. It takes user inputed port number
 *				 and then creates and socket and dateTimeserver with that port number.
 *
 *				Deliverable 2 (5/5/13)
 *				-Accepts a request from a client through a web browser.
 *				-Returns response with basic HTML
 */

/* Class headers */
#include "application/socket/base/Socket.h"
#include "application/servers/HTTP/HTTPserver.h"

/* System libraries */
#include <stdexcept>			// Standard Exception Library
#include <iostream>

/* C-derived headers */
#include <cstring>				// Signal output


/* Main executed at runtime */
int main(int argc, char ** argv){

	// Declare Server and Socket
	HTTPserver httpServer;
	Socket sock;

	try{

		// Sets the signals
		httpServer.setSignalHandler();

		// Create socket
		sock.createSocket(argc, argv);

		// Start server with Socket object
		httpServer.runThreaded(sock);

	}
	catch (int signal){

		// Create signal message and log it
		stringstream message;
		message << "Signal received: " << strsignal(signal) <<  " - " << signal << flush;

		// Output to console and log
		cout << message.str() << endl << flush;
		httpServer.logWrite(message.str());
	}
	catch (exception &e){

		// Create Error message
		stringstream message;
		message << "Fatal Exception:   "<< e.what();

		// Output to cerr and log
		cerr << message.str() << endl << flush;
		httpServer.logWrite(message.str());
	}

	return (0);
}
