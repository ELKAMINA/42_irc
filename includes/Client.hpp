#pragma once

# include "Colors.hpp"
# include <vector>
# include <iostream>
# include <string>
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
	public:

	/* CONSTRUCTORS */
		Client();
		Client( int fd );
		Client( const Client & x );
		~Client();
	
	/* OPERATOR OVERLOADS */
		Client & operator= ( const Client & rhs );
	
	/* GETTERS */
		int	getFdClient();
		std::string getNickName() const;
		std::string getUserName() const;

	/* SETTERS */
		void	setFdClient(int fd);

	/* METHODS */
		void receiveMessage(Message& message);
	
	private:

		int									                _clientFd;
		std::string							                _nickName; //rfc: MAX 9 caracteres
		std::string							                _userName;
        std::string                                         _pass;
		const std::string					                _host;
		std::string							                _id;
		std::map<int, Request>								all_req;	


	// private:

	public:
		Client();
		Client( int fd );
		Client( const Client & x );
		~Client();
		Client & operator= ( const Client & rhs );
		int		getFdClient();
		void	setFdClient(int fd);


};

