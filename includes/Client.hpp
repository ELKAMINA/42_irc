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

enum valid_modes
{
	away = 'a',
	invisible = 'i',
	wallops = 'w',
	restricted = 'r',
	op = 'o',
	localOp = 'O',
};

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
		std::string		getmode() const;
		std::string 	getPwd() const;
		std::string		getHost() const;

	/* SETTERS */
		std::string			setPrefix();
		void				setPwd(std::string passwd);
		void				setNickname(std::string name);
		void				setUsername(std::string name);
		void				setRealname(std::string name);
		void				setMode(char mode, bool state);
		void				setAwayMessage(std::string message);
		void				setAllModes(char mode);
		std::string			getAwayMessage() const;
		std::map<char,bool>	get_rbtModes() const;
		std::string			getAllModes() const;

	/* METHODS */
		void			errInCmd(Request& request, string err);
		bool			checkMode(char mode) const;
		// void receiveMessage(Message& message);
	
	private:

		void						initModes();
		int				            _clientFd;
		std::string					_nickName; //rfc: MAX 9 caracteres
		std::string					_userName;
		std::string					_realName;
        std::string					_pass;
		const std::string			_host;
		std::string					_away_msg;
		std::string					_id;
		std::map<char, bool>		_mode;
		std::string					_all_modes;
		std::map<int, Request>		all_req;



};

