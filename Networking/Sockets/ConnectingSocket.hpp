#pragma once 

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "ASocketinglibc-sockets.hpp"

namespace Socketing
{
	class ConnectingSocket : public SimpleSocket
	{
		private:
			struct sockaddr_in 	address;
			int 		sock;
			int 		connection;

		public:
			/* Constructor */
			ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);

			/* Function to connect a network */
			int	connect_to_network(int sock, struct sockaddr_in add);

			/* Function for testing */
			void test_connection(int);

			/* Getters */
			struct sockaddr_in get_address();
			int get_sock();
			int get_connection();

	};
}