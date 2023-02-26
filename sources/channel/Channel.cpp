/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:13:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/26 17:49:44 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <algorithm>


/* ****************************** */
/* *** COPLIEN STUFF ************ */
/* ****************************** */

Channel::Channel( vector<Client*>& allUsers, string channelName, Client& owner ) :
_name(channelName), _allUsers(allUsers)
{
	initModes();
	_operators.push_back(&owner); // Client doesn't has a nickName getter yet
	_onlineUsers = 0;
	_maxUsers = -1;
	_topic = "";
	_key = "";
}

Channel::Channel( vector<Client*>& allUsers, string channelName, string channelKey, Client& owner ) :
_name(channelName), _key(channelKey), _allUsers(allUsers)
{
	initModes();
	_operators.push_back(&owner); // Client doesn't has a nickName getter yet
	_onlineUsers = 0;
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
	this->_invited.clear();
	this->_mods.clear();
}

void Channel::initModes()
{
	_mods.insert(make_pair('b', false));
	_mods.insert(make_pair('i', false));
	_mods.insert(make_pair('k', false));
	_mods.insert(make_pair('l', false));
	_mods.insert(make_pair('p', false));
	_mods.insert(make_pair('s', false));
	_mods.insert(make_pair('t', false));
}

/* ****************************** */
/* *** CHAN INFO CHECKERS ******* */
/* ****************************** */

bool Channel::isInChanList(Client const *user, vector<Client*>& list)
{
	vector<Client*>::iterator it;

	it = find(list.begin(), list.end(), user);
	return (it != list.end());
}

Client* Channel::found(string nickname, vector<Client*>&list)
{
	vector<Client*>::iterator it = list.begin();
	while (it != list.end())
	{
		if	((*it)->getNickName() == nickname)
			return *(it);
		it++;
	}
	return NULL;
}

bool Channel::isInServ(string const& user, vector<Client *>&users)
{
	vector<Client *>::iterator it;

	for (size_t i = 0; i < users.size(); i++){
		if (users[i]->getNickName() == user)
			return true;
	}
	return false;
}

bool Channel::clientAccess(Client& cli)
{
	std::vector<Client*>::iterator it = _banned.begin();
	while (it != _banned.end())
	{
		if ((*it)->getNickName() == cli.getNickName())
			return true;
	}
	if (this->activeMode('m'))
	{
		std::vector<Client*>::iterator ita = _operators.begin();
		while (ita != _operators.end())
		{
			if ((*ita)->getNickName() == cli.getNickName())
			return true;
		}
		std::vector<Client*>::iterator ito = _vocal.begin();
		while (ito != _vocal.end())
		{
			if ((*ito)->getNickName() == cli.getNickName())
			return false;
		}
		return true;
	}
	return false;
}



/* ****************************** */
/* *** CHAN MODE CHECKERS ******* */
/* ****************************** */

bool Channel::activeMode(char mode)
{
	map<char, bool>::iterator it;
	it = _mods.find(mode);
	if (it != _mods.end())
		return it->second;
	return false;
}

/* ****************************** */
/* *** ACCESSORS **************** */
/* ****************************** */

string Channel::getName() const
{
	return this->_name;
}

string Channel::getTopic() const
{
	return this->_topic;
}

string Channel::getModes() const
{
	map<char, bool>::const_iterator it = _mods.begin();
	string rep = "";
	if (_mods.size() > 0)
	{
		rep += "+";
		for (;it != _mods.end(); it++){
			if (it->second == true)
				rep += it->first;
		}
	}
	return rep;
}

int Channel::getOnlineCount() const
{
	return this->_onlineUsers;
}

std::string Channel::getKey() const
{
	return this->_key;
}