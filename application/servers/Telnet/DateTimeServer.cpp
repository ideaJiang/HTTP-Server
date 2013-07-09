/*
 * DateTimeServer.cpp
 *	Date Time Server. Inherits from Server and adds an analyze and conversation.
 *	Allows the user to enter date, time, and done to get appropriate responses
 *  Created on: Apr 25, 2013
 *      Author: Zachary Swartwood
 *      		Nathan Zondlo
 */

/* Definition Header */
#include "DateTimeServer.h"

/* Sys libraries */
#include <algorithm>			// Algorithm library

/* DateTimeServer Constructor, passes the socket to super */
DateTimeServer::DateTimeServer(Socket &sock){

	// Run server immediately
	runThreaded(sock);
}

/* Default constructor */
DateTimeServer::DateTimeServer(){}

/* Destructor */
DateTimeServer::~DateTimeServer(){}


/* The conversation with the client */
void DateTimeServer::conversation(int thisClientfd){

	string input;
	string response = "Please enter \"date\", \"time\", or \"quit\"\n";
	Socket sock;
	talking = 1;
	sock.sockWrite(thisClientfd, response);

	while(talking){

		//Read
		input = sock.sockRead(thisClientfd);
		//Understand
		response = analyze(input);
		//Respond
		sock.sockWrite(thisClientfd, response);
	}
}

/* Analyzes what the use entered in and returns the appropriate response */
string DateTimeServer::analyze(string &input){

	Timestamp timer;
	string output = "";

	//Changes the string to lowercase using transform() algorithm
	transform(input.begin(), input.end(), input.begin(), ::tolower );

	//Checks if date was entered
	if(input.compare("date\r\n") == 0){
		output = timer.getDate() + "\n";
		logWrite("user entered: date.");
	}
	//Checks if time was entered
	else if(input.compare("time\r\n") == 0){
 		output = timer.getTime() + "\n";
		logWrite("user entered: time");
	}
	//Checks if done was entered
	else if(input.compare("quit\r\n")== 0){
		talking = 0;
		output = "Goodbye!\n";
		logWrite("user entered: done");

	}
	//Invalid input
	else{
		output = "Incorrect input. Please enter \"date\", \"time\", or \"quit\".\n";
	}

	//Return the response
	return output;
}
