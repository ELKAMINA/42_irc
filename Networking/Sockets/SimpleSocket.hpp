#pragma once 

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
// #include "ASocketinglibc-sockets.hpp"

/* This is an abstract class with a pure connect_to_network function */
namespace Socketing
{
	class SimpleSocket
	{
		private:
			struct sockaddr_in 	address;



	/* 
	The structure sockaddr is a generic container that just allows the OS to be able to read the first couple of bytes that identify the address family. The address family determines what variant of the sockaddr struct to use that contains elements that make sense for that specific communication type.
	
	struct sockaddr_in needs to be filled out : The three more importants attributes are :
	
	>> sin_family

	The address family we used when we set up the socket. In our case, it’s AF_INET (IPv4)

	>> sin_port

	The port number (the transport address). You can explicitly assign a transport address (port) or allow the operating system to assign one. If you’re a client and won’t be receiving incoming connections, you’ll usually just let the operating system pick any available port number by specifying port 0. If you’re a server, you’ll generally pick a specific number since clients will need to know a port number to connect to.

	>> sin_addr

	The address for this socket. This is just your machine’s IP address. With IP, your machine will have one IP address for each network interface. For example, if your machine has both Wi-Fi and ethernet connections, that machine will have two addresses, one for each interface. Most of the time, we don’t care to specify a specific interface and can let the operating system use whatever it wants. The special address for this is 0.0.0.0, defined by the symbolic constant INADDR_ANY.

	Since the address structure may differ based on the type of transport used, the third parameter specifies the length of that structure. This is simply sizeof(struct sockaddr_in).
	*/
			int 		sock; /* File descriptor for the socket as in files system*/
			int 		connection;

		public:
			/* Constructor */
			SimpleSocket(int domain, int service, int protocol, int port, u_long interface);

			/* Virtual function to connect a network */
			virtual int connect_to_network(int sock, sockaddr_in add) = 0;

			/* Function for testing */
			void test_connection(int);

			/* Getters */
			struct sockaddr_in get_address();
			int get_sock();
			int get_connection();
			void set_connection(int newC);
	};
}