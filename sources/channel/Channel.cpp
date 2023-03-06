/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:35:05 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 15:43:49 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <algorithm>


/* ****************************** */
/* *** COPLIEN STUFF ************ */
/* ****************************** */

Channel::Channel(string channelName, string owner ) :
_name(channelName)
{
	initModes();
	initLexer();
	_operators.push_back(owner);
	_onlineUsers = 0;
	_maxUsers = -1;
	_topic = "";
	_key = "";
}

Channel::Channel(string channelName, string channelKey, string owner ) :
_name(channelName), _key(channelKey)
{
	initModes();
	initLexer();
	_operators.push_back(owner);
	_onlineUsers = 0;
	_maxUsers = -1;
	_mods['k'] = true;
	_topic = "";
}

Channel::Channel(const Channel& rhs)
{
	*this = rhs;
}

Channel& Channel::operator=(const Channel& rhs)
{
	if (this != &rhs)
	{
		this->_prefix		= rhs._prefix;
		this->_onlineUsers	= rhs._onlineUsers;
		this->_name			= rhs._name;
		this->_key			= rhs._key;
		this->_topic		= rhs._topic;
		this->users			= rhs.users;
		this->_operators	= rhs._operators;
		this->_vocal		= rhs._vocal;
		this->_banned		= rhs._banned;
		this->_mods			= rhs._mods;
	}
	return *this;
}

bool Channel::operator==(const Channel &rhs)
{
	return this->getName() == rhs.getName();
}

Channel::~Channel()
{
	this->users.clear();
	this->_operators.clear();
	this->_vocal.clear();
	this->_banned.clear();
	this->_invited.clear();
	this->_mods.clear();
	this->_cmds.clear();
}

void Channel::initModes()
{
	_mods.insert(make_pair('i', false));
	_mods.insert(make_pair('k', false));
	_mods.insert(make_pair('l', false));
	_mods.insert(make_pair('s', false));
	_mods.insert(make_pair('t', false));
}

void Channel::initLexer()
{
	_cmds.push_back(&Channel::join);
	_cmds.push_back(&Channel::invite);
	_cmds.push_back(&Channel::topic);
	_cmds.push_back(&Channel::part);
	_cmds.push_back(&Channel::privmsg);
	_cmds.push_back(&Channel::kick);
	_cmds.push_back(&Channel::names);
	_cmds.push_back(&Channel::mode);
}

/* ***************** */
/* **** GETTERS **** */
/* ***************** */
int Channel::getOnlineCount() const
{
	return this->_onlineUsers;
}

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

std::string Channel::getKey() const
{
	return this->_key;
}

bool Channel::isInChanList(string user, vector<string>& list)
{
	for (size_t i = 0; i < list.size(); i++){
		if (user == list[i])
			return true;
	}
	return false;
}

vector<Client>::iterator Channel::find_user(string target, vector<Client>& list)
{
	vector<Client>::iterator it;

	for (it = list.begin(); it != list.end(); it++){
		if (target == it->getName())
			return it;
	}
	return list.end();
}

vector<string>::iterator Channel::existing_user(vector<string>& list, string name)
{
	vector<string>::iterator it;

	for (it = list.begin(); it != list.end(); it++){
		if (*it == name)
			return it;
	}
	return list.end();
}

bool Channel::activeMode(char mode)
{
	map<char, bool>::iterator it;
	it = _mods.find(mode);
	if (it != _mods.end())
		return it->second;
	return false;
}
