/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmds.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:31:04 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/01 13:04:20 by jcervoni         ###   ########.fr       */
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
	request.response = err;
	request.status = treated;
}

void Channel::cmd_lexer(Request& request)
{
	vector<cmds>cmds;
	cmds.push_back(&Channel::join);
	cmds.push_back(&Channel::invite);
	string cmd_name[] = {"JOIN", "INVITE"};
	for (size_t i = 0; i< cmds.size(); i++){
		if (request._command == cmd_name[i])
			(this->*(cmds[i]))(request);
	}
}

void Channel::join(Request &request)
{
	string user = request._origin->getNickName();
	vector<string>::iterator it;
	if (isInChanList(user, _users))
	{
		// std::cout << " heeerewww " << std::endl;
		return (errInCmd(request, errUserOnChannel(user,0)));
	}
	if (isInChanList(user, _banned))
		return (errInCmd(request, errBannedFromChan(0, request.entries[2])));
	if (_mods['l'] && _onlineUsers == _maxUsers)
		return (errInCmd(request, errChannelIsFull(0, request.entries[2])));
	if (_mods['i'] == true)
	{
		if (!isInChanList(user, _invited))
			return (errInCmd(request, errInviteOnlyChan(0, request.entries[2])));
		_invited.erase(it=find(_invited.begin(), _invited.end(), user));
	}
	_onlineUsers += 1;
	request.target.insert(request.target.end(), _users.begin(), _users.end());
	_users.push_back(user);
	request.status = treated;
}

void Channel::invite(Request& request)
{
	string user = request._origin->getNickName();
	vector<string>::iterator it;
	if (request.entries.size() < 3)
		return (errInCmd(request, errNeedMoreParams(0, request.entries[1])));
	if (_mods['l'] && _onlineUsers == _maxUsers)
		return (errInCmd(request, errChannelIsFull(0, request.entries[2])));
	if (_mods['i'] == true)
	{
		if (!isInChanList(user, _operators))
			return (errInCmd(request, errChanPrivsNeeded(0, request.entries[1])));
		request.response = "@";
	}
	_invited.push_back(request.entries[2]);
	request.target.push_back(request.entries[2]);
	//send message notif to dest;
	//send RPL_to src;
}