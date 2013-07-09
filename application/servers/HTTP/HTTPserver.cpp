/*
 * HTTPserver.cpp
 *
 *  Created on: May 1, 2013
 *      Author: nzondlo
 */

/* Class Definition */
#include "HTTPserver.h"


#include <iostream>
#include <sstream>


#define SERVER_NAME (const string)("ZaN v0.2.2")

using namespace std;

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;


/* Default Constructor */
HTTPserver::HTTPserver() {}

/* Constructor, passes the socket to super */
HTTPserver::HTTPserver(Socket &sock){

	// run server immediately
	runThreaded(sock);
}

/* Destructor */
HTTPserver::~HTTPserver(){}

/* The conversation with the client */
void HTTPserver::conversation(int thisClientfd){

	Socket sock;

    // Get request
	pthread_mutex_lock(&mutex_lock);
    string request = sock.sockRead(thisClientfd);
    pthread_mutex_unlock(&mutex_lock);

    //Generate response
    string response = analyze(request);

    //Respond
    pthread_mutex_lock(&mutex_lock);
    sock.sockWrite(thisClientfd,response);
    pthread_mutex_unlock(&mutex_lock);

	// Close client connection
	closeClient(thisClientfd);

}

/* Analyzes what the user entered in and returns the appropriate response */
string HTTPserver::analyze(string &input){

	Timestamp timer;
	stringstream request(input);


	// Strings to hold parses
	string command;
	string path;
	string output;

	// Get HTTP command from request, for use later
	request >> command;

	// Get path from request
	request >> path;

	//Checks if /date was requested
	if(path.compare("/") == 0){
		output = appendTop(path) + appendBottom("Welcome to ZaN Server 0.2.3");
	}
	else if(path.compare("/date") == 0){
		output = appendTop(path) + appendBottom(timer.getDate());
		logWrite("Client request: date");
	}
	//Checks if /time was requested
	else if(path.compare("/time") == 0){
 		output = appendTop(path) + appendBottom(timer.getTime());
		logWrite("Client request: time");
	}
	//Invalid input
	else{
		output = fileNotFound();
	}
	//Return the response
	return output;
}

string HTTPserver::appendTop(string &input){
    string  header	=       "HTTP/1.1 200 OK\r\n";
    header     		+=      "Server: ";
    header			+=		SERVER_NAME;
    header			+=		"\r\n";
    header      	+=      "Content-Type: text/html\r\n";
    header 			+= 		"\r\n";
    header			+=		"<html><head><title>";
    header			+= 		input;
    header			+=		"</title></head>";
	return header;
}

string HTTPserver::appendBottom(string input){
    string  closer	=      "<body><h1>";
    closer			+=		input;
    closer			+= 		"</h1></body></html>";


    return closer;
}

string HTTPserver::fileNotFound(){
    string  response	=       "HTTP/1.1 404 Not Found\r\n";
    response     		+=      "Server: ";
    response			+=		SERVER_NAME;
    response			+=		"\r\n";
    response      		+=      "Content-Type: text/html\r\n";
    response   			+=      "\r\n";
    response  			+=      "<html><head><title>404: Not Found</title></head><body><h1>Error: 404 File not found</h1></body></html>";

    return response;
}
