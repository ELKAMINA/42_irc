/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marvin.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:58:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/03 14:33:04 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "marvin.hpp"

typedef void	(Marvin::*cmd)(Request&);

Marvin::Marvin(vector<Client *>& users) : _allUsers(users)
{
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

void Marvin::giveTime(Request& request)
{
	time_t	current_time;
	tm		*current_tm;
	char	date_str[10];
	char	time_str[8];

	time(&current_time);
	current_tm = localtime(&current_time);
	strftime(date_str, 10, "%Y.%m.%d", current_tm);
	strftime(time_str, 8, "%H:%M:%S", current_tm);
	request.reply = "Date: " + string(date_str) + ",\n";
	request.reply += "Time: " + string(time_str) + '\n';
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

void Marvin::giveQuote(Request& request)
{
	srand(time(NULL));
	int q = rand() % this->_quotes.size();
	request.reply = this->_quotes[q];
}

void Marvin::introduce(Request& request)
{
	request.reply = "Hi, I'm Marvin, what's up?\n";
}

void Marvin::wakeServ(Request& request)
{
	string sender = request._origin->getNickName();
	
	for (size_t i = 0; i < _allUsers.size(); i++){
		if (!(_allUsers[i]->checkMode('i')) && !(_allUsers[i]->checkMode('a')) 
		&& _allUsers[i]->getNickName() != sender)
			request.target.push_back(_allUsers[i]->getNickName());
	}
	request.response = request._origin->setPrefix() + " WANTS TO WAKE YOU UP!!\n";
	request.reply = "Well done, you've waken up this server!\n";
}

void Marvin::affHelp(Request& request)
{
	request.reply = "Marvin can perform:\n";
	for (size_t i = 0; i < _cmd_name.size(); i++){
		request.reply += _cmd_name[i] + '\n';
	}
}

void Marvin::cmd_lexer(Request& request)
{
	size_t i = 0;

	if (request.entries.size() < 2)
		request.reply = errNeedMoreParams(0, request._command);
	else if (request.entries.size() > 2)
		request.reply = "666 * :Marvin doesn't like multiple commands\n";
	else
	{
		for (; i < this->_cmds.size(); i++){
			if (request.entries[1] == _cmd_name[i])
			{
				(this->*(_cmds[i]))(request);
				break ;
			}
		}
		if (i == _cmd_name.size())
			request.reply = "667 * :Marvin doesn't know this freaky command\n";
	}
}