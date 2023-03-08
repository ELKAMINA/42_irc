/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:02:20 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/08 19:49:25 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

typedef void (Channel::*act)(Client&, string);

void Channel::modeBan(Request& request, pair<string, string> command, Server* serv)
{
	std::vector<std::string>::iterator it;

	if (command.second == "")
		return;
	if (command.first[0] == '+' && !isInChanList(command.second, users))
	{
		request.reply = "441 " + request.origin->setPrefix() + " " +  command.second + " #" + this->getName() + " :They aren't on that channel";
		serv->chan_requests(request);
		return;
	}
	if (command.first[0] == '+' && !isInChanList(command.second, _banned))
	{
		request.target.insert(request.target.end(), users.begin(), users.end());
		request.response = ":" + request.origin->setPrefix() + " KICK #" + this->getName() 
		+ " " + command.second + " :" + ((request.message[0] == ':')? &request.message[1]:request.message);
		_banned.push_back(command.second);
		serv->chan_requests(request);
		removeUser(command.second);
		request.target.clear();
	}
	else if (command.first[0] == '-')
	{
		it = existing_user(_banned, command.second);
		if (it != _banned.end())
			_banned.erase(it);
		else
		{
			request.reply = "441 " + request.origin->setPrefix() +" " +  command.second + " " + this->getName() + " :They aren't on that channel";
			serv->chan_requests(request);
		}
	}
}

void Channel::modeLimite(Request& request, pair<string, string> command, Server* serv)
{
	int max = 0;

	if (command.second == "")
		return;
	if (command.first[0] == '+')
	{
		max = atoi(command.second.c_str());
		if (max <= 0)
			return;
	}
	_maxUsers = (command.first[0] == '+') ? max : -1;
	_mods['l'] = (command.first[0] == '+') ? true : false;
	request.target.insert(request.target.end(), users.begin(), users.end());
	request.response = ":" + request.origin->setPrefix() + " MODE #" + this->getName() +
	" " + command.first + ((command.second == "")? "":" " + command.second);
	serv->chan_requests(request);
	request.target.clear();
}

void Channel::modeKey(Request& request, pair<string, string> command, Server* serv)
{
	if (command.second == "")
		return;
	this->_key = (command.first[0] == '+') ? command.second : "";
	_mods['k'] = (command.first[0] == '+') ? true : false;
	request.target.insert(request.target.end(), users.begin(), users.end());
	request.response = ":" + request.origin->setPrefix() + " MODE #" + this->getName() +
	" " + command.first + ((command.second == "")? "":" " + command.second);
	serv->chan_requests(request);
	request.target.clear();
}

void Channel::changeChanMode(Request& request, pair<string, string> command, Server* serv)
{
	if (command.first[1] == 'l')
		return (modeLimite(request, command, serv));
	else if (command.first[1] == 'k')
		return (modeKey(request, command, serv));
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
	" " + command.first + ((command.second == "")? "":" " + command.second);
	serv->chan_requests(request);
	request.target.clear();
}

void Channel::changeUserMode(Request& request, pair<string, string> command, vector<string>& target, Server* serv)
{
	vector<Client>::iterator it_cli;
	string user = request.origin->getName();

	it_cli = find_obj(command.second, serv->all_clients);
	if (it_cli == serv->all_clients.end())
		request.reply = errNoSuchNick(user, command.second);
	else if (!isInChanList(it_cli->getName(), users))
		request.reply = errUserNotOnChannel(command.second, this->getName());
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
	" " + command.first + ((command.second == "")? "" : " " + command.second);
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

static map<string, string> splitModes(vector<string>params)
{
	map<string, string>modes;

	for (uint i = 1; i < params[1].size(); i++){
		string mode = "";
		mode += params[1][0];
		mode += params[1][i];
		modes.insert(make_pair(mode, (params.size() > 2)? params[2]:""));
		if (params.size() > 2)
			params.erase(params.begin() + 2);
	}
	return modes;
}

int Channel::addMode(Request& request, vector<string>params, Server* serv)
{
	map<string, string>modes;

	if (params.size() == 1)
		request.reply = rpl_channelmodeis(this->getName(), this->getModes());
	else
	{
		modes = splitModes(params);
		for (map<string, string>::iterator it = modes.begin(); it != modes.end(); it++){
			if (!isInSet(it->first[1], "biklomstv"))
			{
				request.reply = "501 " + request.origin->getName() + ":Unknown MODE flag";
				serv->chan_requests(request);
				request.reply.clear();
			}
			else if (it->first[1] == 'o')
				changeUserMode(request, *it, _operators, serv);
			else if (it->first[1] == 'v')
				changeUserMode(request, *it, _vocal, serv);
			else if (it->first[1] == 'b')
				modeBan(request, *it, serv);
			else
				changeChanMode(request, *it, serv);
		}
	}
	return 0;
}
