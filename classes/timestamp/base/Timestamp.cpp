/*
 * Timestamp.cpp
 *	Timestamp implementation file. Has methods to return date and time  that can be used for time-stamping.
 *  Created on: Apr 23, 2013
 *      Author: Nathan Zondlo
 *      		Zachary Swartwood
 */

/* Class Definition */
#include "Timestamp.h"

/* C-derived headers */
#include <cstring>			// String header
#include <ctime>			// Time and Date functions

/* Namespaces */
using namespace std;

/* Default Constructor */
Timestamp::Timestamp() {

}

/* Destructor */
Timestamp::~Timestamp() {

}

/* Basic return for system date */
string Timestamp::getDate(){

	// Create temp variables
	char temp[50];
	string tempDate;

	// New time variable
	time_t 	timer;

	// clear contents of c-string
	memset(&temp, 0, sizeof (temp));

	// get system time
	time(&timer);

	// build formatted c-string, assign it to string
	strftime(temp, 50, "%b %d %Y ", localtime(&timer));
	tempDate = temp;

	//return formatted string
	return tempDate;
}

/* Basic return for system time */
string Timestamp::getTime(){

	// Create temp variables
	char temp[50];
	string tempTime;

	// New time variable
	time_t 	timer;

	// clear contents of c-string
	memset(&temp, 0, sizeof(temp));

	// get system time
	time(&timer);

	// build formatted c-string, assign it to string
	strftime(temp, 50, "%I:%M:%S %p ", localtime(&timer));
	tempTime = temp;

	//return formatted string
	return tempTime;
}
