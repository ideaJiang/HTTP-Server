HTTP-Server
===========

HTTP Server implementation written in C/C++

This is a C/C++ implementation of an HTTP Server that serves back a request, time, date,  404 error page to the connecting client.

Currently, sending a browser request to the top level domain, /date, /time, all perform as expected. With a 404 error response sent otherwise.


### Inheritance Hierarchy:

##### Legend  					                                         	
 <- : inclusion of a class				                           
 ^                                                          
 |  : Lower class inherits from the class it is pointing to 



		      Application <- Timestamp
		      ^     ^    
      		 _|     |_	  
		Server		Socket			
		 ^		
		_|
	HTTPServer
