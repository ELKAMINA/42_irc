/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:17:09 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/10 15:47:29 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <string>

typedef void (Channel::*act)(Client&, string);

// void Channel::modeBan(Request& request, pair<string, string> command)
// {
// 	string user = request.entries[1];

// 	vector<string>::iterator it;
// 	if (command.first[0] == '+')
// 	{
// 		if (!isInChanList(user, this->_users))
// 			return(errInCmd(request, errUserNotOnChannel(user, this->getName())));
// 		_banned.push_back(*it);
// 		_users.erase(it);
// 		_operators.erase(find(_operators.begin(), _operators.end(), command.second));
// 		_vocal.erase(find(_vocal.begin(), _vocal.end(), command.second));
// 		this->_onlineUsers -= 1;
// 	}
// 	else
// 	{
// 		if (!isInChanList(user, this->_banned))
// 			return (errInCmd(request, errUserNotOnChannel(user, this->getName())));
// 		else
// 		{
// 			it = find(_banned.begin(), _banned.end(), command.second);
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
		if (max == 0)
		{
			cout<<"bad value"<<endl;
			return;
		}
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
void Channel::changeUserMode(Request& request, pair<string, string> command, vector<Client*>& target)
{
	string user = request._origin->getNickName();
	Client* to_add = found(request.entries[2], _users);
	vector<Client*>::iterator it;
	
	if(command.first.size() != 2)
		return (errInCmd(request, errUModeUnknownFlag(user, this->getName())));
	else
	{
		it = find(_users.begin(), _users.end(), to_add);
		if (command.first[0] == '+')
		{
			if (find(target.begin(), target.end(), to_add) == target.end())
				target.push_back(*it);
		}
		else
		{
			it = find(target.begin(), target.end(), to_add);
			target.erase(it);
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

static uint checkModes(string params)
{
	bool userMode = false;
	bool chanMode = false;
	int count = 0;
	string found = "";
	if ((params[0] != '-' && params[0] != '+') || params.size() < 2)
		return 0;
	for (uint i = 1; i < params.size(); i++){
		if (!isInSet(params[i], "iklopstv"))
			return 0;
		else if (!isInSet(params[i], found))
		{
			if ((params[i] == 'o' || params[i] == 'v') && !chanMode)
			{
				count = 1;
				userMode = true;
				found += params[i];
			}
			else if (!userMode)
			{
				if (params[0] == '+' && (params[i] == 'k' || params[i] == 'l'))
					count += 1;
				chanMode = true;
				found += params[i];
			}
			else
				return 0;
		}
	}
	return count;
}

static map<string, string> splitModes(vector<string>params)
{
	map<string, string>modes;
	uint countParams = 0;
	for (uint i = 1; i < params[1].size(); i++){
		string mode = "";
		mode += params[1][0];
		mode += params[1][i];
		if (params[1][i] == 'o' || params[1][i] == 'v')
			modes.insert(make_pair(mode, params[2]));
		else
		{
			if (params[1][0] == '+' && (params[1][i] == 'k' || params[1][i] == 'l'
			|| params[1][i] == 't'))
			{
				modes.insert(make_pair(mode, params[2 + countParams]));
				countParams += 1;
			}
			else
				modes.insert(make_pair(mode, ""));
		}
	}
	return modes;
}

int Channel::addMode(Request& request, vector<string>params)
{
	uint countParams;
	map<string, string>modes;

	countParams = checkModes(params[1]);
	if (countParams != params.size() - 2)
		return (request.response = errNeedMoreParams(request._origin->getNickName(), request._command), 1);
	modes = splitModes(params);
	for (map<string, string>::iterator it = modes.begin(); it != modes.end(); it++){
		if (it->first[1] == 'o')
			changeUserMode(request, *it, _operators);
		else if (it->first[1] == 'v')
			changeUserMode(request, *it, _vocal);
		else
			changeChanMode(request, *it);
	}
	request.status = treated;
	return 0;
}
