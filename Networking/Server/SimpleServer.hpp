#pragma once 

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "../Sockets/ListeningSocket.hpp"

class ListeningSocket;

/* Is a server a socket ? */
namespace Socketing
{
	class SimpleServer
	{
		private:
			Socketing::ListeningSocket *socket;
			virtual void accepter() = 0;
			virtual void handler() = 0;
			virtual void responder() = 0;

		public:
			/* Constructor */
			SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklog);
			virtual void launch() = 0;
			ListeningSocket *get_server_socket();
			// /* Virtual function to connect a network */
			// virtual int connect_to_network(int sock, sockaddr_in add) = 0;

			// /* Function for testing */
			// void test_connection(int);

			// /* Getters */
			// struct sockaddr_in get_address();
			// int get_sock();
			// int get_connection();
			// void set_connection(int newC);
	};
}