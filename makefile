CC=g++
CFLAGS=-c

all: HTTPserver

HTTPserver: main.o Application.o Server.o HTTPserver.o Socket.o Timestamp.o
	$(CC) main.o Application.o Server.o HTTPserver.o Socket.o Timestamp.o -o HTTPserver -lpthread


main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Application.o: application/base/Application.cpp
	$(CC) $(CFLAGS) application/base/Application.cpp

Server.o: application/servers/base/Server.cpp
	$(CC) $(CFLAGS) application/servers/base/Server.cpp

HTTPserver.o: application/servers/HTTP/HTTPserver.cpp
	$(CC) $(CFLAGS) application/servers/HTTP/HTTPserver.cpp

Socket.o: application/socket/base/Socket.cpp
	$(CC) $(CFLAGS) application/socket/base/Socket.cpp

Timestamp.o: classes/timestamp/base/Timestamp.cpp
	$(CC) $(CFLAGS) classes/timestamp/base/Timestamp.cpp

clean:
	rm -rf *o HTTPserver
