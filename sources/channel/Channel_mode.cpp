/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:02:20 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 20:57:56 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

typedef void (Channel::*act)(Client&, string);

// void Channel::modeBan(Request& request, pair<string, string> command)
// {
// 	vector<Client *>::iterator it;
	
// 	if (command.first[0] == '+')
// 	{
// 		if (!isInChanList(request._origin, this->_users))
// 			return(errInCmd(request, errUserNotOnChannel(request._origin->getNickName(), this->getName())));
// 		it = find(_users.begin(), _users.end(), *it);
// 		_banned.push_back(*it);
// 		_users.erase(it);
// 		_operators.erase(find(_operators.begin(), _operators.end(), request._origin));
// 		_vocal.erase(find(_vocal.begin(), _vocal.end(), request._origin));
// 		this->_onlineUsers -= 1;
// 	}
// 	else
// 	{
// 		if (!isInChanList(request._origin, this->_banned))
// 			return (errInCmd(request, errUserNotOnChannel(request._origin->getNickName(), this->getName())));
// 		else
// 		{
// 			it = find(_banned.begin(), _banned.end(), request._origin);
// 			_banned.erase(it);
// 		}
// 	}
// }

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

void Channel::changeChanMode(Request& request, pair<string, string> command)
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
}
//modif to do
void Channel::changeUserMode(Request& request, pair<string, string> command, vector<string>& target, Server* serv)
{
	map<string, Client>::iterator it_cli;
	string user = request.origin;

	it_cli = serv->all_clients.find(request.entries[2]);
	if (it_cli == serv->all_clients.end())
	{
		request.reply = errNoSuchNick(request.origin, request.entries[2]);
		return;
	}
	if (!isInChanList(it_cli->first, users))
	{
		request.reply = errUserNotOnChannel(request.entries[2], this->getName());
		return;
	}
	if(command.first.size() != 2)
	{
		request.reply = errUModeUnknownFlag();
		return;
	}
	else
	{
		if (command.first[0] == '+')
		{
			if (!isInChanList(it_cli->first, target))
				target.push_back(it_cli->first);
		}
		else
		{
			for (size_t i = 0; i < target.size(); i++){
				if (it_cli->first == target[i])
				{
					target.erase(target.begin() + i);
					break;
				}
			}
		}
	}
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
	if ((params[0] != '-' && params[0] != '+') || params.size() < 2)
		return -1;
	for (size_t i = 1; i < params.size(); i++){
		if (!isInSet(params[i], "biklompstv"))
			return (request.reply = errUModeUnknownFlag(), -1);
		else if (!isInSet(params[i], found))
		{
			if ((params[i] == 'b' || params[i] == 'o' || params[i] == 'v') && !chanMode)
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
	if (params.size() - count != 2)
		return -1;
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
		// if (countParams != params.size() - 2)
		// 	return (request.reply = errNeedMoreParams(request._origin->getNickName(), request._command), 1);
		modes = splitModes(params, countParams);
		for (map<string, string>::iterator it = modes.begin(); it != modes.end(); it++){
			if (it->first[1] == 'o')
				changeUserMode(request, *it, _operators, serv);
			else if (it->first[1] == 'v')
				changeUserMode(request, *it, _vocal, serv);
			// else if (it->first[1] == 'b')
			// 	modeBan(request, *it);
			else
				changeChanMode(request, *it);
		}
	}
	return 0;
}
