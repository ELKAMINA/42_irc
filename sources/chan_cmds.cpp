/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmds.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:31:04 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/03 10:34:40 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Request.hpp"
#include "Client.hpp"
#include "numeric_replies.hpp"

typedef std::string	(*err)(string, string);
typedef void		(Channel::*cmds)(Request&);

void errInCmd(Request& request, string err)
{
	request.reply = err;
	request.status = treated;
}

void Channel::cmd_lexer(Request& request)
{
	vector<cmds>cmds;
	cmds.push_back(&Channel::join);
	cmds.push_back(&Channel::invite);
	cmds.push_back(&Channel::topic);
	cmds.push_back(&Channel::part);
	string cmd_name[] = {"JOIN", "INVITE", "TOPIC", "PART"};
	for (size_t i = 0; i< cmds.size(); i++){
		if (request._command == cmd_name[i])
			(this->*(cmds[i]))(request);
	}
}

void Channel::reply_joining(Request& request)
{
	string rep = "";
	vector<string>::iterator it;

	if (this->_topic.size() > 0)
		rep += rpl_topic(this->getName(), this->getTopic());
	else
		rep += rpl_notopic(this->getName(), this->getTopic());
	for (size_t i = 0; i < this->_users.size(); i++){
		if ((it=find(_operators.begin(), _operators.end(), _users[i])) != _operators.end())
			rep +="@";
		else
			rep +=":";
		rep += _users[i];
		if (i < _users.size() -1)
			rep += ", ";
	}
	rep += '\n';
	request.reply = rep;
}

void Channel::join(Request &request)
{
	string user = request._origin->getNickName();
	vector<string>::iterator it;
	if (isInChanList(user, _users))
		return (errInCmd(request, errUserOnChannel(user,0)));
	if (isInChanList(user, _banned))
		return (errInCmd(request, errBannedFromChan(0, this->getName())));
	if (_mods['l'] && _onlineUsers == _maxUsers)
		return (errInCmd(request, errChannelIsFull(0, this->getName())));
	if (_mods['i'] == true)
	{
		if (!isInChanList(user, _invited))
			return (errInCmd(request, errInviteOnlyChan(0, this->getName())));
		_invited.erase(it=find(_invited.begin(), _invited.end(), user));
	}
	_onlineUsers += 1;
	request.target.insert(request.target.end(), _users.begin(), _users.end());
	request.response = ":" + request._origin->setPrefix() + " has join #" + this->getName() + '\n';
	reply_joining(request);
	_users.push_back(user);
	request.status = treated;
}

void Channel::invite(Request& request)
{
	string user = request._origin->getNickName();
	vector<string>::iterator it;
	if (request.entries.size() < 2)
		return (errInCmd(request, errNeedMoreParams(0, request._command)));
	if (!isInServ(request.entries[1], this->_allUsers))
		return (errInCmd(request, errNoSuchNick(user, request.entries[1])));
	if (_mods['l'] && _onlineUsers == _maxUsers)
		return (errInCmd(request, errChannelIsFull(0, this->getName())));
	if (_mods['i'] == true)
	{
		if (!isInChanList(user, _operators))
			return (errInCmd(request, errChanPrivsNeeded(0, this->getName())));
		request.response = "@";
	}
	_invited.push_back(request.entries[1]);
	request.target.push_back(request.entries[1]);
	request.response += request._origin->setPrefix() + " INVITE " + request.entries[1] + " #" + this->getName() + '\n';
	request.reply = rpl_inviting(request.entries[1], this->getName());
}

void Channel::topic(Request& request)
{
	size_t size = request.entries.size();
	string user = request._origin->getNickName();

	if (size > 3)
		errInCmd(request, errNeedMoreParams(0, request._command));
	else if (size == 2)
	{
		if (this->_topic.size() > 0)
			request.reply = rpl_topic(this->getName(), this->getTopic());
		else
			request.reply = rpl_notopic(this->getName(), this->getTopic());
	}
	else if (!isInChanList(user, _operators))
		errInCmd(request, errChanPrivsNeeded(0, this->getName()));
	else // new topic and user is operator
	{
		if (request.entries[2] == ":")
			this->_topic = "";
		else
		{
			if (request.entries[2][0] != ':')
				errInCmd(request, errNeedMoreParams(0, request._command));
			else
				this->_topic = &request.entries[2][1];
		}
	}
}

void Channel::part(Request& request)
{
	string user = request._origin->getNickName();
	string reason = "";
	vector<string>::iterator it;

	if (!isInChanList(user, this->_users))
		errInCmd(request, errNotOnChannel(user, this->getName()));
	else
	{
		if ((*(request.entries.end()-1))[0] != '#')
		{
			if ((*(request.entries.end()-1))[0] == ':')
				reason = " " + (*(request.entries.end()-1));
			else
				return (errInCmd(request, errNeedMoreParams(0, request._command)));
		}
		_users.erase(it = find(_users.begin(), _users.end(), user));
		_operators.erase(it = find(_users.begin(), _users.end(), user));
		_onlineUsers -= 1;
		request.target.insert(request.target.end(), _users.begin(), _users.end());
		request.response = user + " leaves #" + this->getName() + reason + '\n';
	}
}