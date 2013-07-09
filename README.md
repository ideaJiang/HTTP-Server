HTTP-Server
===========

###### HTTP Server implementation written in C/C++
###### Development OS: Fedora 16
###### IDE: Eclipse Juno

This is a C/C++ implementation of an HTTP Server that serves back a request, time, date,  404 error page to the connecting client.

Currently, sending a browser request to the top level domain, /date, /time, all perform as expected. With a 404 error response sent otherwise.


### Inheritance Hierarchy:

```
Legend
--------------------------------------------------------------					                                         	
 <- : inclusion of a class				                           
 ^                                                          
 |  : Lower class inherits from the class it is pointing to 
--------------------------------------------------------------


		      Application <- Timestamp
		      ^     ^    
      		 _|     |_	  
		Server		Socket			
		 ^		
		_|
	HTTPServer
```

# main()

All code is *thoroughly* commented.

```C++
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

```

# Run server

### Compile necessary files
