#pragma once

# include "Server.hpp"
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
# include "numeric_replies.hpp"

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
	notEnough_params,
	incorrect_pwd,
	already_registered,
	omitted_cmd,
	nickname_exists,
	erroneous_nickname,
	privmsg_one,
	welcome_msg,
	empty,
};

enum cmd
{
	PASS,
	NICK,
	USER,
	JOIN,
	UNKNOWN,
};

class Client;
class Server;

class Request
{
	public:
		int							_id;
		std::string					_raw_req;
		std::vector<std::string>	entries; // Params + Commands (entries[0] Max 512 caracteres (including the CR-LF)
		char						_prefix; // Optional : ":" used by servers to indicate the true origin of the message
		std::string					_command;
		enum cmd					_cmd_types;
		std::string					_body;
		// std::string					_origin;
		// std::string					_nickname_cli;
		Client*						_origin; // a remplacer ac le nickname du client
		std::string					serv_origin;
		enum state					status;
		enum valid_req				req_validity; //Valid request or not
		std::string					response;
		// ajouter une reply pour lexpediteur en cas de commande ou lexpediteur attend une réponse 
		std::vector<std::string>	target;
		// std::vector<Channel*>		all_chans;
		// int							type;

	public:
		Request		(char* buf, Client* cli);
		~Request	();
		Request		( const Request &x );
		Request & 	operator = ( const Request &rhs );

		/* Getters */
		std::string getEntries(size_t i) const;

		/* Commands */
		void		_pass(Client* cli, Request* req, Server *serv);
		void		_nick(Client* cli, Request* req, Server *serv);
		void		_user(Client* cli, Request* req, Server *serv);
		int			_privmsg(Client* cli, Request* req, Server *serv);
		int			_join(Client* cli, Request* req, Server *serv);

		/* Utils for commands*/
		void		msg_to_user(Client* cli, Request* req, Server *serv);
		int			user_existence(std::string dest, Server *serv);
		Client*		find(std::string dest, Server *serv);
		int			wrong_nickname();
		void		oneChan(Client* cli, Request* req, Server *serv);
		void		multiChan(Client* cli, Request* req, Server *serv);

};