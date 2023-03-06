/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:18:08 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 11:22:35 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(): _clientFd(0), _nickName(""), _userName(""), _pass(""),
_host("IRC_with_love")
{
	_initModes();
	_away_msg = "";
	loggedIn = false;
	callToMode = 0;
}

Client::Client(int fd): _clientFd(fd), _nickName(""), _userName(""), _pass(""),
_host("IRC_with_love")
{
	_initModes();
	_away_msg = "";
	loggedIn = false;
	callToMode = 0;
}

Client::Client( const Client& x ): _host(x._host) { *this = x; };

Client & Client::operator=( const Client& rhs )
{
	if (this != &rhs)
	{
		this->_clientFd = rhs._clientFd;
		this->_nickName = rhs._nickName;
		this->_userName = rhs._userName;
		this->_realName = rhs._realName;
		this->_away_msg = rhs._away_msg;
		this->loggedIn	= rhs.loggedIn;
		this->callToMode	= rhs.callToMode;
		this->chans 	= rhs.chans;
		this->_pass 	= rhs._pass;
		this->_host 	= rhs._host;
		this->_mode 	= rhs._mode;
	}
	return *this;
}

bool	Client::operator==(const Client& rhs)
{
	return this->_nickName == rhs._nickName;
}

Client::~Client()
{
	// this->_mode.clear();
	// this->chans.clear();
}

/* ***************************** */
/* **** GETTERS **************** */
/* ***************************** */

int Client::getFdClient()
{
	return this->_clientFd;
}

std::string Client::getName() const
{
	return this->_nickName;
}

std::string Client::getUserName() const
{
	return this->_userName;
}

std::string Client::getRealName() const
{
	return this->_realName;
}

std::string Client::getPwd() const
{
	return this->_pass;
}

size_t Client::getChanNbr() const
{
	return this->chans.size();
}

std::string Client::getAwayMessage() const
{
	return this->_away_msg;
}

std::string Client::getmode() const
{
	std::map<char, bool>::const_iterator it;
	std::string ret = "";
	for (it = _mode.begin(); it != _mode.end(); it++){
		if (it->second == true)
			ret += it->first;
	}
	return ret;
}

/* ***************************** */
/* **** SETTERS **************** */
/* ***************************** */

void Client::setFdClient(int fd)
{
	_clientFd = fd;
}

void Client::setNickname(std::string name)
{
	this->_nickName = name;
}

void Client::setUsername(std::string name)
{
	this->_userName = name;
}

void Client::setRealname(std::string name)
{
	this->_realName = name;
}

void Client::setMode(char mode, bool state)
{
	this->_mode[mode] = state;
}

void Client::setPwd(std::string pwd)
{
	_pass = pwd;
}

std::string Client::setPrefix()
{

	std::string msg =  _nickName + "!" + _userName + "@localhost";
	return (msg);
}

void Client::setAwayMessage(std::string message)
{
	this->_away_msg = message;
}

/* ***************************** */
/* **** METHODS **************** */
/* ***************************** */

void Client::_initModes()
{
	this->_mode.insert(std::make_pair('i', false));
	this->_mode.insert(std::make_pair('s', false));
	this->_mode.insert(std::make_pair('w', false));
	this->_mode.insert(std::make_pair('r', false));
	this->_mode.insert(std::make_pair('o', false));
	this->_mode.insert(std::make_pair('O', false));
}

bool Client::checkMode(char mode) const
{
	std::map<char, bool>::const_iterator it;
	it = _mode.find(mode);
	if (it != _mode.end())
		return it->second;
	return false;
}

void Client::addChanToList(std::string chan)
{
	this->chans.push_back(chan);
}

void Client::removeChanFromList(std::string chan)
{
	std::vector<string>::iterator it;
	for (it = chans.begin(); it != chans.end(); it++){
		if (*it == chan)
		{
			chans.erase(it);
			break ;
		}
	}
}

void Client::leaveAllChans(Server *serv)
{
	std::vector<string>::iterator it = chans.begin();
	std::vector<Channel>::iterator it_cha;
	for (; it != chans.end(); it++){
		it_cha = find_obj(*it, serv->all_channels);
		it_cha->removeUser(this->getName());
	}
}