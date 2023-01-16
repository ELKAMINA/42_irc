#pragma once 

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include "./SimpleServer.hpp"
#include "../Sockets/ListeningSocket.hpp"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>

namespace Socketing
{
	class testServer : public SimpleServer
	{
		private:
			int	new_socket;
			// int nb_fd[30]; // number of clients fds
			// int status;
			// int max_fds;
			// fd_set select_set_read; //set of read socket descriptors
			// fd_set select_set_read_ready;
			// struct timeval select_timeout;
			// std::vector<int> fds;
			char buffer[30000] = {0};
			void accepter();
			void handler();
			void responder();

		public:
			/* Constructor */
			testServer();
			void launch();
	};
}