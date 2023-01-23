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
# include "Request.hpp"
# include "Client.hpp"

class Channel
{
	private:
		char							_prefix;
		Client*							_Op;
		int								_onlineUsers;
		std::string						_name;
		std::string						_key;
		std::string						_topic;
		std::map<int, Client *>			_members;
		std::map<int, Client *>			_operators;
		std::map<int, Client *>			_voice;
		std::vector<std::string>		_banned;

	private:
		Channel();

	public:
		Channel( std::string channelName, Client *Creater );
		Channel( std::string channelName, std::string channelKey, Client *Creater );
		Channel( const Channel& x );
		Channel &operator=( const Channel& rhs );
		~Channel();
};


