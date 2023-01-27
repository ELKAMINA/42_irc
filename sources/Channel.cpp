/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:13:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/27 18:57:13 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <algorithm>


/* ****************************** */
/* *** COPLIEN STUFF ************ */
/* ****************************** */

Channel::Channel( std::vector<Client>& allUsers, std::string channelName, Client& owner ) :
_name(channelName), _allUsers(allUsers)
{
	_operators.push_back(owner.getNickName()); // Client doesn't has a nickName getter yet
	_onlineUsers = 1;
	_maxUsers = -1;
	_topic = "";
	_key = "";
}

Channel::Channel( std::vector<Client>& allUsers, std::string channelName, std::string channelKey, Client& owner ) :
_name(channelName), _key(channelKey), _allUsers(allUsers)
{
	_operators.push_back(owner.getNickName()); // Client doesn't has a nickName getter yet
	_onlineUsers = 1;
	_maxUsers = -1;
	_mods['k'] = true;
	_topic = "";
}

Channel::Channel(const Channel& rhs) : _allUsers(rhs._allUsers)
{
	*this = rhs;
}

Channel& Channel::operator=(const Channel& rhs)
{
	if (this != &rhs)
	{
		this->_prefix = rhs._prefix;
		this->_onlineUsers = rhs._onlineUsers;
		this->_name = rhs._name;
		this->_key = rhs._key;
		this->_topic = rhs._topic;
		this->_users = rhs._users;
		this->_operators = rhs._operators;
		this->_vocal = rhs._vocal;
		this->_banned = rhs._banned;
		this->_mods = rhs._mods;
	}
	return *this;
}

Channel::~Channel()
{
	this->_users.clear();
	this->_operators.clear();
	this->_vocal.clear();
	this->_banned.clear();
	this->_mods.clear();
}

/* ****************************** */
/* *** RIGHTS & STATUS ********** */
/* ****************************** */

void Channel::addUser(Client& user)
{
	std::vector<std::string>::iterator target;
	target = find(_users.begin(), _users.end(), user.getNickName());
	if (target != _users.end())
		std::cout << "User already in channel" << std::endl;
	else
	{
		std::cout << user.getNickName() << "has successfully joined channel" << std::endl;
		_users.push_back(user.getNickName());
	}
}

void Channel::deleteUser(Client& user)
{
	std::vector<std::string>::iterator target;
	target = find(_users.begin(), _users.end(), user.getNickName());
	if (target == _users.end())
		std::cout << "No such User" << std::endl;
	else
	{
		std::cout << user.getNickName() << "has been successfully erased from channel" << std::endl;
		_users.erase(target);
	}
}

// void Channel::addOperator(Client& user)
// {

// }

// void Channel::deleteOperator(Client& user, std::string fault)
// {
	
// }

void Channel::ban(Client& ope, Client& user, std::string fault)
{
	std::vector<std::string>::iterator sender;
	std::vector<std::string>::iterator target;
	sender = find(_operators.begin(), _operators.end(), ope.getNickName());
	target = find(_users.begin(), _users.end(), user.getNickName());
	if (sender == _operators.end())
		std::cout << "Tu t'es pris pour le boss ?" << std::endl;
	else if (target == _users.end())
		std::cout << "Bro, y'a personne ici avec ce blase" << std::endl;
	else
	{
		std::cout << "et c'est le ban, BOUYAAAA" << fault<< std::endl;
		_users.erase(target);
		_banned.push_back(user.getNickName());
	}
}

void Channel::inviteIn(Client& inviter, Client& invited)
{
	std::vector<std::string>::iterator src;
	std::vector<std::string>::iterator dst;

	src = find(_users.begin(), _users.end(), inviter.getNickName());
	dst = find(_users.begin(), _users.end(), invited.getNickName());
	if (src == _users.end())
		std::cout << "casse-toi tu pues t'es pas d'ma bande" << std::endl;
	else if (dst != _users.end())
		std::cout << "il est deja parmis nous ducon" << std::endl;
	else
	{
		dst = find(_banned.begin(), _banned.end(), invited.getNickName());
		if (dst != _banned.end())
			std::cout << "son exil n'est pas fini" << std::endl;
	}
}

/* ****************************** */
/* *** CHAN INFO CHECKERS ******* */
/* ****************************** */

bool Channel::isMember(Client& user)
{
	std::vector<std::string>::iterator it;

	it = find(_users.begin(), _users.end(), user.getNickName());
	return (it != _users.end());
}

bool Channel::isOperator(std::string& user)
{
	std::vector<std::string>::iterator it;

	it = find(_operators.begin(), _operators.end(), user);
	return (it != _operators.end());
}

bool Channel::isBanned(Client& user)
{
	std::vector<std::string>::iterator it;

	it = find(_banned.begin(), _banned.end(), user.getNickName());
	return (it != _banned.end());
}

bool Channel::canTalk(Client& user)
{
	std::vector<std::string>::iterator it;

	it = find(_vocal.begin(), _vocal.end(), user.getNickName());
	return (it != _vocal.end());
}

/* ****************************** */
/* *** CHAN MODE CHECKERS ******* */
/* ****************************** */

bool Channel::activeMode(char mode)
{
	std::map<char, bool>::iterator it;
	it = find(_mods.begin(), _mods.end(), mode);
	if (it != _mods.end())
		return true;
	return false;
}

/* ****************************** */
/* *** COMMAND MANAGER ********** */
/* ****************************** */
// cote chan:
// 		JOIN KICK KICKBAN INVITE PART TOPIC (OP) 
// cote server:
// 		LIST 
// void Channel::treatAndReturn(Request& message)
// {
	
// }