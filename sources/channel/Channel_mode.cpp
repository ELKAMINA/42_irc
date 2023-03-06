/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:02:20 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 18:53:14 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

typedef void (Channel::*act)(Client&, string);

void Channel::modeLimite(Request& request, pair<string, string> command)
{
	(void)request;
	if (command.first[0] == '+')
	{
		int max = atoi(command.second.c_str());
		if (max <= 0)
			return;
		this->_maxUsers = max;
		_mods['l'] = true;
	}
	else
	{
		this->_maxUsers = -1;
		_mods['l'] = false;
	}
}

void Channel::changeChanMode(Request& request, pair<string, string> command, Server* serv)
{
	(void)request;
	cout<< "command = " << command.first << ", param = "<<command.second<<endl;
	if (command.first[1] == 'l')
		modeLimite(request, command);
	else if (command.first[1] == 'k')
		_key = command.second;
	else if (command.first[1] == 't')
		_topic = command.second;
	if (command.first[0] == '+')
	{
		map<char, bool>::iterator it = _mods.find(command.first[1]);
		if (it != _mods.end())
			_mods[command.first[1]] = true;
	}
	else
	{
		_mods[command.first[1]] = false;
	}
	request.target.insert(request.target.end(), users.begin(), users.end());
	request.response = ":" + request.origin->setPrefix() + " MODE #" + this->getName() +
	" " + command.first + (command.second == "" ? "" : " " + command.second);
	serv->chan_requests(request);
	request.target.clear();
}

void Channel::changeUserMode(Request& request, pair<string, string> command, vector<string>& target, Server* serv)
{
	vector<Client>::iterator it_cli;
	string user = request.origin->getName();

	it_cli = find_obj(request.entries[2], serv->all_clients);
	if (it_cli == serv->all_clients.end())
		request.reply = errNoSuchNick(user, request.entries[2]);
	else if (!isInChanList(it_cli->getName(), users))
		request.reply = errUserNotOnChannel(request.entries[2], this->getName());
	else if(command.first.size() != 2)
		request.reply = errUModeUnknownFlag();
	else
	{
		if (command.first[0] == '+')
		{
			if (!isInChanList(it_cli->getName(), target))
				target.push_back(it_cli->getName());
		}
		else
		{
			for (size_t i = 0; i < target.size(); i++){
				if (it_cli->getName() == target[i])
				{
					target.erase(target.begin() + i);
					break;
				}
			}
		}
	}
	request.target.insert(request.target.end(), users.begin(), users.end());
	request.response = ":" + request.origin->setPrefix() + " MODE #" + this->getName() +
	" " + command.first + (command.second == "" ? "" : " " + command.second);
	serv->chan_requests(request);
	request.target.clear();
}

static int isInSet(char c, string set)
{
	for (uint i = 0; i < set.size(); i++){
		if (c == set[i])
			return 1;
	}
	return 0;
}

static int checkModes(Request& request, string params)
{
	bool userMode = false;
	bool chanMode = false;
	int count = 0;
	string found = "";
	std::cout << params << params.size() << std::endl;
	if ((params[0] != '-' && params[0] != '+') || params.size() < 2)
		return -1;
	for (size_t i = 1; i < params.size(); i++){
		if (!isInSet(params[i], "iklostv"))
			return (request.reply = errUModeUnknownFlag(), -1);
		else if (!isInSet(params[i], found))
		{
			if ((params[i] == 'o' || params[i] == 'v') && !chanMode)
			{
				userMode = true;
				found += params[i];
			}
			else if (!userMode)
			{
				if (params[0] == '+' && (params[i] == 'k' || params[i] == 'l' || params[i] == 't'))
					count += 1;
				chanMode = true;
				found += params[i];
			}
			else
				return -1;
		}
	}
	return count;
}

static map<string, string> splitModes(vector<string>params, int countParams)
{
	(void)countParams;
	
	map<string, string>modes;
	for (uint i = 1; i < params[1].size(); i++){
		string mode = "";
		mode += params[1][0];
		mode += params[1][i];
		if (params[1][i] == 'b' || params[1][i] == 'o' || params[1][i] == 'v')
			modes.insert(make_pair(mode, params[2]));
		else
		{
			if (params[1][0] == '+' && (params[1][i] == 'k' || params[1][i] == 'l'
			|| params[1][i] == 't'))
			{
				modes.insert(make_pair(mode, params[2]));
				params.erase(params.begin() + 2);
			}
			else
				modes.insert(make_pair(mode, ""));
		}
	}
	return modes;
}

int Channel::addMode(Request& request, vector<string>params, Server* serv)
{
	int countParams;
	map<string, string>modes;

	if (params.size() == 1)
		request.reply = rpl_channelmodeis(this->getName(), this->getModes());
	else if ((countParams = checkModes(request, params[1])) != -1)
	{
		modes = splitModes(params, countParams);
		for (map<string, string>::iterator it = modes.begin(); it != modes.end(); it++){
			if (it->first[1] == 'o')
				changeUserMode(request, *it, _operators, serv);
			else if (it->first[1] == 'v')
				changeUserMode(request, *it, _vocal, serv);
			else
				changeChanMode(request, *it, serv);
		}
	}
	return 0;
}
