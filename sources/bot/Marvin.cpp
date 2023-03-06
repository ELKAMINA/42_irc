/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Marvin.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:58:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 20:23:29 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Marvin.hpp"

Marvin::Marvin()
{
	initQuotes();
	_cmds.push_back(&Marvin::affHelp);		_cmd_name.push_back("HELP");
	_cmds.push_back(&Marvin::introduce);	_cmd_name.push_back("HELLO");
	_cmds.push_back(&Marvin::giveTime);		_cmd_name.push_back("TIME");
	_cmds.push_back(&Marvin::giveQuote);	_cmd_name.push_back("TALK");
	_cmds.push_back(&Marvin::wakeServ);		_cmd_name.push_back("SHAKE");
}

Marvin::~Marvin()
{
	_cmds.clear();
	_cmd_name.clear();
	_quotes.clear();
}

void Marvin::giveTime(Request& request, Server* serv)
{
	time_t	current_time;
	tm		*current_tm;
	char	date_str[10];
	char	time_str[8];

	time(&current_time);
	current_tm = localtime(&current_time);
	strftime(date_str, 10, "%Y%m%d", current_tm);
	strftime(time_str, 8, "%H%M%S", current_tm);
	request.reply = "Date: ";
	request.reply += string(date_str).substr(0, 4) + ".";
	request.reply += string(&date_str[4]).substr(0, 2) + ".";
	request.reply += string(&date_str[7]).substr(0, 2) + ",\n";
	request.reply += "and it is ";
	request.reply += string(time_str).substr(0, 2) + ":";
	request.reply += string(&time_str[2]).substr(0, 2) + ":";
	request.reply += string(&time_str[4]).substr(0, 2) + ".\n";
	serv->chan_requests(request);
}

void Marvin::initQuotes()
{
	ifstream quotes("./sources/bot/quotes.txt");
	if (quotes)
	{
		string quote;
		while (getline(quotes, quote))
			this->_quotes.push_back(quote);
	}
}

void Marvin::giveQuote(Request& request, Server* serv)
{
	srand(time(NULL));
	int q = rand() % this->_quotes.size();
	request.reply = this->_quotes[q];
	serv->chan_requests(request);
}

void Marvin::introduce(Request& request, Server* serv)
{
	request.reply = "Hi, I'm Marvin, what's up?\n";
	serv->chan_requests(request);
}

void Marvin::wakeServ(Request& request, Server* serv)
{
	string sender = request.origin->getName();
	
	for (size_t i = 0; i < serv->all_clients.size(); i++){
		if (!(serv->all_clients[i].checkMode('i')) && !(serv->all_clients[i].checkMode('a')) 
		&& serv->all_clients[i].getName() != sender)
			request.target.push_back(serv->all_clients[i].getName());
	}
	request.response = request.origin->setPrefix() + " WANTS TO WAKE YOU UP!!\n";
	request.reply = "Well done, you've waken up this server!\n";
	serv->chan_requests(request);
}

void Marvin::affHelp(Request& request, Server* serv)
{
	request.reply = "Marvin can perform:\n";
	for (size_t i = 0; i < _cmd_name.size(); i++){
		request.reply += _cmd_name[i] + '\n';
	}
	serv->chan_requests(request);
}

void Marvin::cmd_lexer(Request& request, Server* serv)
{
	size_t i = 0;

	if (request.entries.size() < 2)
		request.reply = errNeedMoreParams(request.origin->getName(), request.command);
	if (request.entries.size() > 2)
		request.reply = "666 * :Marvin doesn't like multiple commands\n";
	else
	{
		for (; i < this->_cmds.size(); i++){
			if (request.entries[0] == _cmd_name[i])
			{
				(this->*(_cmds[i]))(request, serv);
				return;
			}
		}
		if (i == _cmd_name.size())
			request.reply = "667 * :Marvin doesn't know this freaky command\n";
	}
	serv->chan_requests(request);
}

