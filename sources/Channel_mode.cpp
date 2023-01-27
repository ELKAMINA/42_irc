/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:17:09 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/27 18:49:02 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

typedef void (Channel::*act)(Client&, std::string);

// void Channel::modeBan(std::string target, std::string message=0)
// {

// }

// void Channel::modeInvite(bool add)
// {
	
// }

// void Channel::modeKey(bool add, std::string key=0)
// {
	
// }

void Channel::modeLimite(Request& request, std::pair<std::string, std::string> command)
{
	if (command.first[0] == '+')
	{
		try
		{
			int max = stoi(command.second);
			this->_maxUsers = max;
			_mods['l'] = true;
		}
		catch (const std::exception & e)
		{
			//bad value
		}
	}
	else
	{
		this->_maxUsers = -1;
		_mods.erase('l');
	}
}

// void Channel::modeOper(Client& target, std::string message=0)
// {
	
// }

// void Channel::modePrivate(Client& target, std::string message=0)
// {
	
// }

// void Channel::modeSecret(Client& target, std::string message=0)
// {
	
// }

// void Channel::modeVocal(Client& target, std::string message=0)
// {
	
// }

static int isInSet(char c, std::string set)
{
	for (uint i = 0; i < set.size(); i++){
		if (c == set[i])
			return 1;
	}
	return 0;
}

static uint checkModes(std::string params)
{
	bool userMode = false;
	bool chanMode = false;
	int count = 0;
	std::string found = "";
	if ((params[0] != '-' && params[0] != '+') || params.size() < 2)
		return 0;
	for (uint i = 1; i < params.size(); i++){
		if (!isInSet(params[i], "biklopstv"))
			return 0;
		else if (!isInSet(params[i], found))
		{
			if ((params[i] == 'b' || params[i] == 'o' || params[i] == 'v') && !chanMode)
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

static std::map<std::string, std::string> splitModes(std::vector<std::string>params)
{
	std::map<std::string, std::string>modes;
	uint countParams = 0;
	for (uint i = 1; i < params[1].size(); i++){
		std::string mode = "";
		mode += params[1][0];
		mode += params[1][i];
		if (params[1][i] == 'b' || params[1][i] == 'o' || params[1][i] == 'v')
			modes.insert(make_pair(mode, params[2]));
		else
		{
			if (params[1][0] == '+' && (params[1][i] == 'k' || params[1][i] == 'l'))
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

int Channel::addMode(Request& request, std::vector<std::string>params)
{
	uint countParams;
	std::map<std::string, std::string>modes;
	// if (isOperator(request.nickName))
	// {
		countParams = checkModes(params[1]);
		if (countParams != params.size() - 2)
			return (std::cout << "erreur de parametres"<<std::endl, 1);
		modes = splitModes(params);
		for (std::map<std::string, std::string>::iterator it = modes.begin(); it != modes.end(); it++){
			std::cout << "mode = " << it->first << ", param = "<< it->second << std::endl;
		}
	// }
	// else
	// 	raise error not on chan
	return 0;
}
