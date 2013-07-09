/*
 * DateTimeServer.h
 *	Date Time Server header file
 *  Created on: Apr 25, 2013
 *      Author: Zachary Swartwood
 *      		Nathan Zondlo
 *
 */

#ifndef DATETIMESERVER_H_
#define DATETIMESERVER_H_

#include "../base/Server.h"

class DateTimeServer : public Server{
public:

	DateTimeServer(Socket &sock);				//Constructors
	DateTimeServer();
	virtual ~DateTimeServer();				//Deconstructor

	void conversation(int thisClientfd);					//The conversation with the client
	string analyze(string &input);			//Analyze the input from the client
};

#endif /* DATETIMESERVER_H_ */
