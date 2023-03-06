/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:01:26 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 11:36:57 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(const char* buffer, std::vector<Client>::iterator cli) : origin(cli)
{
	initLexer();
	raw_input = buffer;
	char * token = strtok(const_cast<char *>(buffer) , " ");
	while( token != NULL ) {
		entries.push_back(token);
		token = strtok(NULL, " ");
	}
	reply = "UNDEFINED";
	response = "UNDEFINED";
	user_to_kick = "";
	nb_chan = 0;
	nb_keys = 0;
	message = "";
}

Request::Request( const Request& x ) : origin(x.origin)
{
	*this = x;
}

Request & Request::operator=( const Request& rhs )
{
	if (this != &rhs)
	{
		this->raw_input = rhs.raw_input;
		this->entries = rhs.entries;
		this->channels = rhs.channels;
		this->params = rhs.params;
		this->command = rhs.command;
		this->response = rhs.response;
		this->reply = rhs.reply;
		this->message = rhs.message;
		this->target = rhs.target;
		this->nb_chan = rhs.nb_chan;
		this->nb_keys = rhs.nb_keys;
		this->user_to_kick = rhs.user_to_kick;
	}
	return *this;
}

Request::~Request()
{
	this->entries.clear();
	this->channels.clear();
	this->params.clear();
	this->target.clear();
	this->_request_cmds.clear();
}

void Request::initLexer()
{
	_request_cmds.push_back(&Request::pass);
	_request_cmds.push_back(&Request::nick);
	_request_cmds.push_back(&Request::user);
	_request_cmds.push_back(&Request::privmsg);
	_request_cmds.push_back(&Request::privmsg);
	_request_cmds.push_back(&Request::join);
	_request_cmds.push_back(&Request::part);
	_request_cmds.push_back(&Request::kick);
	_request_cmds.push_back(&Request::topic);
	_request_cmds.push_back(&Request::mode);
	_request_cmds.push_back(&Request::away);
	_request_cmds.push_back(&Request::list);
	_request_cmds.push_back(&Request::names);
	_request_cmds.push_back(&Request::cap);
	_request_cmds.push_back(&Request::invite);
	_request_cmds.push_back(&Request::oper);
	_request_cmds.push_back(&Request::kill);
	_request_cmds.push_back(&Request::ping);
	_request_cmds.push_back(&Request::whois);
	_request_cmds.push_back(&Request::quit);
	_request_cmds.push_back(&Request::who);
	_request_cmds.push_back(&Request::restart);
	_request_cmds.push_back(&Request::marvin);
}

int Request::requestLexer(Server* serv)
{
	std::string cmds[] = {"PASS", "NICK", "USER", "PRIVMSG", "NOTICE", "JOIN", "PART",
						"KICK", "TOPIC", "MODE", "AWAY", "LIST", "NAMES","CAP", "INVITE",
						"OPER", "KILL", "PING", "WHOIS", "QUIT", "WHO", "RESTART", "MARVIN"};
	size_t i = 0;

	for (; i < _request_cmds.size(); i++){
		if (this->command == cmds[i])
				return ((this->*(_request_cmds[i]))(serv));
	}
	if (i == _request_cmds.size())
	{
		reply = errUnknownCommand(command);
		if (send(origin->getFdClient(), reply.c_str(), strlen(reply.c_str()), 0) == -1)
				perror("Send ");
	}
	return 0;
}
