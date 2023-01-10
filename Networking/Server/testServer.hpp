#pragma once 

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include "./SimpleServer.hpp"
#include "../Sockets/ListeningSocket.hpp"

namespace Socketing
{
	class testServer : public SimpleServer
	{
		private:
			Socketing::ListeningSocket* socket;
			int	new_socket;
			std::string buffer;
			void accepter();
			void handler();
			void responder();

		public:
			/* Constructor */
			testServer();
			void launch();
	};
}