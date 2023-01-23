#pragma once

#include "Server.hpp"
# include "./Colors.hpp"
# include <vector>
# include <iostream>
# include <string>
# include <cstring>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include "ServerSocket.hpp"
# include <map>
// # include "Channels.hpp"
# include "Request.hpp"

class Request;

class Client
{
	private:
		int									                _clientfd;
		std::string							                _Nick; //rfc: MAX 9 caracteres
		std::string							                _User;
        std::string                                         _Pass;
		const std::string					                _Host;
		std::string							                _id;
		std::map<int, Request>								all_req;	


	// private:

	public:
		Client();
		Client( int fd );
		Client( const Client & x );
		~Client();
		Client & operator= ( const Client & rhs );
		int	getFdClient();
		void	setFdClient(int fd);


};

