/*
 * Application.h
 *	Application Header file
 *  Created on: Apr 18, 2013
 *     Author: Nathan Zondlo
 *      	   Zachary Swartwood
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

/* Inclusion of the Timestamp class header */
#include "../../classes/timestamp/base/Timestamp.h"

/* System libraries */
#include <fstream>					// File streams
#include <sstream>					// String streams

/* C-derived headers */
#include <csignal> 					// Signal library

/* Include everything in std namespace */
using namespace std;

class Application {

public:
	// Constructor(s) and Destructor
	Application();
	virtual ~Application();

	// writes message to log
	void logWrite(string message);

	// writes message to log, checks result/fd first. Outputs SUCCESS or FAILURE
	void logWrite(int suspect, string message);
	//sets the signal handler
	void setSignalHandler();

private:
	// One log to rule them all
	static ofstream logFile;

	// Instance of Timestamp
	Timestamp timer;

	// used in logWrite() to cut down confusion
	void logOpen(string fileName);
	void logClose();
	//for the signal
	static void signalHandler( int signal );
};

#endif /* APPLICATION_H_ */
