/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmds.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:31:04 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/26 18:47:31 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Request.hpp"
#include "Client.hpp"
#include "numeric_replies.hpp"

typedef std::string	(*err)(string, string);

void Channel::errInCmd(Request& request, string err)
{
	request.reply = err;
	//request.status = treated;
}

void Channel::removeUser(Client * client)
{
	vector<Client *>::iterator it;

	_users.erase(it = find(_users.begin(), _users.end(), client));
		if ((it = find(_operators.begin(), _operators.end(), client)) != _operators.end())
			_operators.erase(it);
		if ((it = find(_vocal.begin(), _vocal.end(), client)) != _vocal.end())
			_vocal.erase(it);
		_onlineUsers -= 1;

}

void Channel::reply_joining(Request& request, Server* serv)
{
	(void)serv;
	string rep = "";
	vector<Client *>::iterator it;
	request.reply.clear();
	for (size_t i = 0; i < this->_users.size(); i++){
		if ((it=find(_operators.begin(), _operators.end(), _users[i])) != _operators.end())
			rep +="@";
		else
			rep +=" ";
		rep += _users[i]->getNickName();
		if (i < _users.size() -1)
			rep += " ";
	}
	// rep += "\r\n"; /* Commenté par Amina */
	request.reply = "353 " + request._origin->setPrefix() + " = " + "#" + this->getName() + " :" + rep;
	rep.clear();
}

void Channel::join(Request &request, Server* serv)
{
	string user = request._origin->getNickName();
	vector<Client *>::iterator it;
	int matching_param = 0;
	bool yes = false;

	if (isInChanList((request._origin), _users))
	{
		errInCmd(request, errUserOnChannel(user,this->getName()));
		yes = true;
	}
	if (_mods['k'] == true)
	{
		for (size_t i = 0; i < request.entries.size(); i++){
			if (request.entries[i] == _name)
			{
				matching_param = i;
				break;
			}
		}
		if (request.entries[matching_param + request.jo_nb_chan] != this->getKey())
		{
			errInCmd(request, errBadChannelKey(user, this->getName()));
			yes = true;
		}
	}
	if (_mods['l'] && _onlineUsers == _maxUsers)
	{
		errInCmd(request, errChannelIsFull(user, this->getName()));
		yes = true;
	}
	if (_mods['i'] == true)
	{
		if (!isInChanList((request._origin), _invited))
		{
			errInCmd(request, errInviteOnlyChan(user, this->getName()));
			yes = true;
		}
		else
			_invited.erase(it=find(_invited.begin(), _invited.end(), request._origin));
	}
	if ( yes == false)
	{
		_onlineUsers += 1;
		_users.push_back(request._origin);
		request.target.insert(request.target.end(), _users.begin(), _users.end());
		request.response = ":" + request._origin->setPrefix() + " JOIN #" + this->getName();
		if (this->_topic.size() > 0)
		{
			std::string rep = rpl_topic(request, this->getName(), this->getTopic());
			if (send(request._origin->getFdClient(), rep.c_str(), rep.length(), 0) == -1)
				return (perror("Problem in sending from server ")); // a t on le droit ?
		}
		reply_joining(request, serv);
		serv->_chan_requests(request);
		request.response = "UNDEFINED";
		request.reply.clear();
		request.reply = rpl_endofnames(request, this->getName(), "option");
		request._origin->addChanToList(this);
	}
	serv->_chan_requests(request);
}

void Channel::invite(Request& request, Server* serv)
{
	(void)serv;
	string user = request._origin->getNickName();
	vector<string>::iterator it;
	request.response.clear();
	Client* to_add = found(request.entries[0], _allUsers);
	if (request.entries.size() < 2)
		return (errInCmd(request, errNeedMoreParams(user, request._command)));
	if (!isInServ(request.entries[0], this->_allUsers))
		return (errInCmd(request, errNoSuchNick(user, request.entries[1])));
	if (_mods['l'] && _onlineUsers == _maxUsers)
		return (errInCmd(request, errChannelIsFull(user, this->getName())));
	if (_mods['i'] == true)
	{
		if (!isInChanList(request._origin, _operators))
			return (errInCmd(request, errChanPrivsNeeded(user, this->getName())));
		request.response = "@";
	}
	if (!isInChanList(to_add, _invited))
		_invited.push_back(to_add);
	request.target.push_back(to_add);
	request.response += request._origin->setPrefix() + " INVITE " + request.entries[0] + " #" + this->getName() + '\n';
	request.reply = rpl_inviting(request.entries[0], this->getName());
}

void Channel::topic(Request& request, Server* serv)
{
	size_t size = request.entries.size();

	if (size == 1)
	{
		if (this->_topic.size() > 0)
			request.reply = rpl_topic(request, this->getName(), this->getTopic());
		else
			request.reply = rpl_notopic(request, this->getName(), "");
	}
	else if (!isInChanList((request._origin), _operators))
		errInCmd(request, errChanPrivsNeeded(request._origin->getNickName(), this->getName()));
	else // new topic and user is operator
	{
		if (request.entries[1].size() == 0)
			this->_topic = "";
		else
		{
			if (request.entries[1][0] != ':')
				errInCmd(request, errNeedMoreParams(request._origin->getNickName(), request._command));
			else
			{
				this->_topic = request.entries[1];
				for (size_t i = 2; i < request.entries.size(); i++){
					this->_topic += " " + request.entries[i];
				}
				request.target.insert(request.target.end(), _users.begin(), _users.end());
				request.response = ":" + request._origin->setPrefix() + " " + "TOPIC #" + this->getName() + " " + _topic;
			}
		}
	}
	serv->_chan_requests(request);
}

void Channel::part(Request& request, Server* serv)
{
	vector<Client*>::iterator it;
	
	if (!isInChanList((request._origin), _users))
		errInCmd(request, errNotOnChannel(request._origin->getNickName(), this->getName()));
	else
	{
		request.target.insert(request.target.end(), _users.begin(), _users.end());
		// request.response = user + " leaves #" + this->getName() + " " + request.message + '\n';
		request.response = ":" + request._origin->setPrefix() + " PART #" + this->getName() + " " + request.message;
		serv->_chan_requests(request);
		removeUser(request._origin);
		request._origin->removeChanFromList(this);
	}
}

void Channel::privmsg(Request& request, Server* serv)
{
	(void)serv;
	string user = request._origin->getNickName();
	vector<Client*>::iterator it;

	request.target.clear();
	request.response.clear();
	if (!isInChanList((request._origin), _users) && request._command == "PRIVMSG")
		return (errInCmd(request, errNotOnChannel(user, this->getName())));
	if (clientAccess(*(request._origin)) == true&&  request._command == "PRIVMSG")
		return (errInCmd(request, errCannotSendToChan(user, this->getName())));
	request.target.insert(request.target.begin(), _users.begin(), _users.end());
	request.target.erase(it=find(request.target.begin(), request.target.end(), request._origin));
	request.response = ":" + request._origin->getNickName() + " " + request._command + " #" + this->getName() + " " + request.message;
}

// work in progress
void Channel::mode(Request& request, Server* serv)
{
	(void)serv;
	string user = request._origin->getNickName();
	if (!isInChanList((request._origin), this->_operators))
		return(errInCmd(request, errChanPrivsNeeded(user, this->getName())));
	addMode(request, request.entries);
}

void Channel::kick(Request& request, Server* serv)
{
	Client* to_kick = NULL;
	string user = request._origin->getNickName();
	if (request.user_to_kick != "UNDEFINED")
		to_kick = found(request.user_to_kick, _users);
	vector<Client *>::iterator it;

	if (!isInChanList((request._origin), _users))
		return (errInCmd(request, errNotOnChannel(user, this->getName())));
	if (!isInChanList((request._origin), _operators))
		return(errInCmd(request, errChanPrivsNeeded(user, this->getName())));
	if ((it = find(_users.begin(), _users.end(), to_kick)) == _users.end())
		return(errInCmd(request, errNoSuchNick(user, request.entries[1])));
	request.target.insert(request.target.begin(), _users.begin(), _users.end());
	request.response = ":" + request._origin->setPrefix() + " KICK #" + this->getName() + " " + request.user_to_kick + " :" + request.message;
	serv->_chan_requests(request);
	removeUser(to_kick);
	to_kick->removeChanFromList(this);
}

void Channel::names(Request& request,Server* serv)
{
	(void)serv;
	vector<Client*>::iterator it;

	request.reply += "#" + this->getName() + ":\n";
	for (it = _users.begin(); it != _users.end(); it++){
		if ((*it)->checkMode('i') == false)
		{
			if (find(_operators.begin(), _operators.end(), (*it)) != _operators.end())
				request.reply += '@';
			else
				request.reply += ':';
			request.reply += (*it)->getNickName() + ", ";
		}
	}
	request.reply.replace(request.reply.size() -2, 2, "\n");
}