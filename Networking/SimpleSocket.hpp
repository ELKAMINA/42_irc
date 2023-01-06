#pragma once 

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

namespace Socketing
{
	class SimpleSocket
	{
		private:
			struct sockaddr_in 	address;
			int 		sock;
			int 		connection;

		public:
			/* Constructor */
			SimpleSocket(int domain, int service, int protocol, int port, u_long interface);

			/* Virtual function to connect a network */
			virtual void connect_to_network(int sock, sockaddr_in address) = 0;

			/* Function for testing */
			void test_connection(int);

			/* Getters */
			struct sockaddr_in get_address();
			int get_sock();
			int get_connection();

	};
}