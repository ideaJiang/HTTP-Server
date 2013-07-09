/*
 * Timestamp.h
 *	Timestamp header file.
 *  Created on: Apr 23, 2013
 *      Author: Nathan Zondlo
 *      		Zachary Swartwood
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

/* System libraries */
#include <sstream>			// String Streams

/* C-derived headers */
#include <ctime>			//Time and Date functions

/* Namespace */
using namespace std;

class Timestamp {

private:

public:
	Timestamp();
	virtual ~Timestamp();

	string getDate();
	string getTime();
};

#endif /* TIMESTAMP_H_ */
