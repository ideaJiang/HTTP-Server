/*
 * Application.cpp
 *	Application implementation file. It has a logWrite that writes to
 *	a file and allows for logging. Also has a signal handler.
 *  Created on: Apr 18, 2013
 *      Author: Nathan Zondlo
 *      		Zachary Swartwood
 *
 */

/* Class definition */
#include "Application.h"

/* Class header */
#include "../../classes/timestamp/base/Timestamp.h"

/* System libraries */
#include <iostream>			// System Input/Output streams
#include <fstream>			// File streams
#include <sstream>			// String streams
#include <iomanip>			// In/Out manipulation (formatting)
#include <stdexcept>		// Standard Exception Library

/* C-Derived libs */
#include <cerrno>			// Error handling


/* Namespace*/
using namespace std;

ofstream Application::logFile;

/* Default Constructor */
Application::Application() {}

/* Destructor */
Application::~Application() {}

/* Open the log file */
void Application::logOpen(string fileName){

	// open the log file
	if ( !logFile.is_open() ){
		logFile.open(fileName.c_str(), ios::app);

		// Test if failed
		if (logFile.fail()){

			// Build and throw error message
			stringstream message;
			message << "File didn't open: " << fileName;
			throw( runtime_error(message.str()) );
		}
	}
    // return finished
    return;
}

/* Close the log file */
void Application::logClose(){

	// close file
	if ( logFile.is_open() )
		logFile.close();

	// Test if close failed
	if(logFile.fail()){

		stringstream message;
		message << "File failed to close" << endl;
		throw( runtime_error(message.str()) );
	}
	return;
}

/* Prints message passed in to the file log with Date and Timestamp */
void Application::logWrite(string message){

	// Open log, write timestamp, close log
	logOpen("log.txt");
	logFile << timer.getDate()<<" "<< timer.getTime() <<" - "<< message << endl << flush;
	logClose();
}

/* Prints message, checks int suspect, appends FAILURE for -1 / else SUCCESS*/
void Application::logWrite(int suspect, string message){

	// Check if our suspect was en error and append correct descriptor
	(suspect == -1) ? message.append(" FAIL") : message.append(" SUCCESS");
	logWrite(message);

}

/* Handler for Signals */
void Application::signalHandler( int signal ){

	// throw an exception
	throw( signal );
}

/* Sets the signal handler for graceful exiting */
void Application::setSignalHandler(){
		/*
		 * Used sigaction instead of signal
		 * signal was restarting accept() and write() instead of next line
		 * sa_flags = 0 means the function you're waiting on does not get restarted
		 *
		 */
		struct sigaction sig;
		sig.sa_handler = signalHandler;
		sig.sa_flags = 0;
		sigemptyset( &sig.sa_mask );

	    // handle SIGINT differently
	    if ( sigaction( SIGINT, &sig, NULL ) == -1){

	    	// Build error message
	    	stringstream message;
	    	message << "Error assigning the handler for SIGINT" << endl;

	    	// Log it, and throw it
	        logWrite(message.str());
	        throw(runtime_error(message.str()));
	    }

	    // handle SIGTERM differently
	    if ( sigaction( SIGTERM, &sig, NULL ) == -1 ){

	    	// Build error message
	    	stringstream message;
	    	message << "Error assigning the handler for SIGTERM" << endl;

	    	// Log it, and throw it
	    	logWrite(message.str());
	    	throw(runtime_error(message.str()));

	    }
}
