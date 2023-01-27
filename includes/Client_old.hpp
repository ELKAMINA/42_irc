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
# include "./numeric_replies/numeric_replies.hpp"

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
		int				getFdClient();
		void			setFdClient(int fd);
		std::string 	getNickName() const;
		std::string 	getUserName() const;
		std::string 	getRealName() const;
		int 			getmode() const;
		std::string 	getPwd() const;

	/* SETTERS */
		std::string		setPrefix();
		void			setPwd(std::string passwd);
		void			setNickname(std::string name);
		void			setUsername(std::string name);
		void			setRealname(std::string name);
		void			setMode(int mode);
		// void			setId(std::string);

	/* METHODS */
		// void receiveMessage(Message& message);
	
	private:

		int									                _clientFd;
		std::string							                _nickName; //rfc: MAX 9 caracteres
		std::string							                _userName;
		std::string							                _realName;
        std::string                                         _pass;
		const std::string					                _host;
		std::string							                _id;
		int													_mode;
		std::map<int, Request>								all_req;	



};

