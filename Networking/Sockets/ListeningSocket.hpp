#pragma once 

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "ASocketinglibc-sockets.hpp"



/* In listening, backlog is the line that is waiting to connect to the server */

namespace Socketing
{
	class ListeningSocket : public BindingSocket
	{
		private:
			int 		backlog;
			int			listening;

		public:
			/* Constructor */
			ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bg);

			/* Function to start listening */
			void	start_listening();

	};
}