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
# include "Client.hpp"
#include <sstream>

enum state
{
	treated = 1,
	ongoing,
	waiting,
};

enum valid_req
{
	valid_req,
	invalid_req,
	valid_body,
	invalid_body,
	empty,
};

enum cmd
{
	PASS,
	NICK,
	USER,
	JOIN,
};

class Client;

class Request
{
	public:
		int							_id;
		std::string					_raw_req;
		std::vector<std::string>	entries; // Max 512 caracteres (including the CR-LF)
		char						_prefix; // Optional : ":" used by servers to indicate the true origin of the message
		std::string					_command;
		int							_cmd_types;
		std::string					_body;
		std::vector<std::string>	_params; // Command parameters	( may be up to 15)
		// Client&						_origin;
		std::string						serv_origin;
		enum state						status;
		enum valid_req					req_validity; //Valid request or not
		std::string					response;

		// int							type;

	public:
		Request(char* buf);
		~Request();
		Request( const Request &x );
		Request & operator = ( const Request &rhs );
		std::string getEntries() const;

};