/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:13:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/07 18:31:31 by jcervoni         ###   ########.fr       */
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
	_operators.push_back(owner.getNickName()); // Client doesn't has a nickName getter yet
	// _users.push_back(owner.getNickName()); 
	_onlineUsers = 1;
	_maxUsers = -1;
	_topic = "";
	_key = "";
}

Channel::Channel( vector<Client*>& allUsers, string channelName, string channelKey, Client& owner ) :
_name(channelName), _key(channelKey), _allUsers(allUsers)
{
	initModes();
	_operators.push_back(owner.getNickName()); // Client doesn't has a nickName getter yet
	// _users.push_back(owner.getNickName());
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
		// this->_banned = rhs._banned;
		this->_mods = rhs._mods;
	}
	return *this;
}

Channel::~Channel()
{
	this->_users.clear();
	this->_operators.clear();
	this->_vocal.clear();
	// this->_banned.clear();
	this->_invited.clear();
	this->_mods.clear();
}

void Channel::initModes()
{
	_mods.insert(make_pair('i', false));
	_mods.insert(make_pair('k', false));
	_mods.insert(make_pair('l', false));
	_mods.insert(make_pair('p', false));
	_mods.insert(make_pair('s', false));
	_mods.insert(make_pair('t', false));
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

/* ****************************** */
/* *** CHAN INFO CHECKERS ******* */
/* ****************************** */

bool Channel::isInChanList(string const &user, vector<string>& list)
{
	vector<string>::iterator it;

	it = find(list.begin(), list.end(), user);
	return (it != list.end());
}

/* ****************************** */
/* *** CHAN MODE CHECKERS ******* */
/* ****************************** */

bool Channel::activeMode(char mode)
{
	map<char, bool>::iterator it;
	it = _mods.find(mode);
	if (it != _mods.end())
		return true;
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

int Channel::getOnlineCount() const
{
	return this->_onlineUsers;
}