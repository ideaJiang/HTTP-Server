/*
 * HTTPserver.h
 *
 *  Created on: May 1, 2013
 *      Author: nzondlo
 */

#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

/* Parent Class */
#include "../base/Server.h"

class HTTPserver: public Server {

public:
	// Constructors and Destructor
	HTTPserver();								//Default
	HTTPserver(Socket &sock);					//With Socket
	virtual ~HTTPserver();

	// Pure virtual from parent
	void conversation(int thisClientfd);		//The conversation with the client

	// Analyzes the request and generates a response
	string analyze(string &input);				// Return response

private:
	string fileNotFound();
	string appendTop(string &input);
	string appendBottom(string input);
};

#endif /* HTTPSERVER_H_ */
