/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_cmds.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:51:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 13:27:22 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

typedef std::string	(*err)(string, string);

void Channel::errInCmd(Request& request, string err)
{
	request.reply = err;
}

void Channel::removeUser(string user)
{
	vector<Client *>::iterator it;

	it = existing_user(users, user);
	users.erase(it = existing_user(users, user));
	if ((it = existing_user(_operators, user)) != _operators.end())
		_operators.erase(it);
	if ((it = existing_user(_vocal, user)) != _vocal.end())
		_vocal.erase(it);
	_onlineUsers -= 1;

}

void Channel::cmd_lexer(Request& request, Server* serv)
{
	string cmd_name[] = {"JOIN", "INVITE", "TOPIC", "PART", "PRIVMSG", "KICK", "NAMES", "MODE"};
	if (request.command == "NOTICE")
	{
		(this->*(_cmds[4]))(request, serv);
		return ;
	}
	for (size_t i = 0; i< _cmds.size(); i++){
		if (request.command == cmd_name[i])
			(this->*(_cmds[i]))(request, serv);
	}
}

void Channel::replyJoining(Request& request, Server* serv)
{
	(void)serv;
	string rep = "";
	vector<Client*>::iterator it;
	
	request.reply.clear();
	for (size_t i = 0; i < this->users.size(); i++){
		if ((it=existing_user(_operators, users[i]->getName())) != _operators.end())
			rep +="@";
		else
			rep +=" ";
		rep += users[i]->getName();
		if (i < users.size() -1)
			rep += " ";
	}
	request.reply = "353 " + request.origin.setPrefix() + " = " + "#" + this->getName() + " :" + rep;
	rep.clear();
}

void Channel::join(Request &request, Server* serv)
{
	string user = request.origin.getName();
	vector<Client*>::iterator it;
	int matching_param;
	bool err = false;
	if (isInChanList(request.origin, users))
	{
		errInCmd(request, errUserOnChannel(user,this->getName()));
		err = true;
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
		if (request.entries[matching_param + request.nb_chan] != this->getKey())
		{
			errInCmd(request, errBadChannelKey(user, this->getName()));
			err = true;
		}
	}
	if (_mods['l'] && _onlineUsers == _maxUsers)
	{
		errInCmd(request, errChannelIsFull(this->getName()));
		err = true;
	}
	if (_mods['i'] == true)
	{
		if (!isInChanList(request.origin, _invited))
		{
			errInCmd(request, errInviteOnlyChan(this->getName()));
			err = true;
		}
		_invited.erase(it=existing_user(_invited, user));
	}
	if ( err == false)
	{
		_onlineUsers += 1;
		users.push_back(&(*find_obj(user, serv->all_clients)));
		request.target.insert(request.target.end(), users.begin(), users.end());
		request.response = ":" + request.origin.setPrefix() + " JOIN #" + this->getName();
		if (this->_topic.size() > 0)
		{
			std::string rep = rpl_topic(request.origin.setPrefix(), this->getName(), this->getTopic());
			if (send(request.origin.getFdClient(), rep.c_str(), rep.length(), 0) == -1)
				return (perror("Problem in sending from server ")); // a t on le droit ?
		}
		replyJoining(request, serv);
		serv->chan_requests(request);
		request.response = "UNDEFINED";
		request.reply.clear();
		request.reply = rpl_endofnames(request.origin.setPrefix(), this->getName());
		// request.origin.addChanToList(this);
	}
	serv->chan_requests(request);
}

void Channel::invite(Request& request, Server* serv)
{
	string user = request.origin.getName();
	vector<string>::iterator it;
	vector<Client>::iterator target = find_user(request.entries[0], serv->all_clients);
	
	request.response.clear();
	if (request.entries.size() < 2)
		return (errInCmd(request, errNeedMoreParams(user, request.command)));
	if (target == serv->all_clients.end())
		return (errInCmd(request, errNoSuchNick(user, request.entries[1])));
	if (_mods['l'] && _onlineUsers == _maxUsers)
		return (errInCmd(request, errChannelIsFull(this->getName())));
	if (_mods['i'] == true)
	{
		if (!isInChanList(request.origin, _operators))
			return (errInCmd(request, errChanPrivsNeeded(user, this->getName())));
		request.response = "@";
	}
	if (!isInChanList(*target, _invited))
		_invited.push_back(&(*target));
	
	request.target.push_back(&(*target));
	request.response += request.origin.setPrefix() + " INVITE " + request.entries[0] + " #" + this->getName() + '\n';
	request.reply = rpl_inviting(request.entries[0], this->getName());
	
}

void Channel::topic(Request& request, Server* serv)
{
	string user = request.origin.getName();
	size_t size = request.entries.size();

	if (size == 1)
	{
		if (this->_topic.size() > 0)
			request.reply = rpl_topic(request.origin.setPrefix(), this->getName(), this->getTopic());
		else
			request.reply = rpl_notopic(request.origin.setPrefix(), this->getName());
		return ;
	}
	else if (!isInChanList(request.origin, _operators))
		errInCmd(request, errChanPrivsNeeded(user, this->getName()));
	else
	{
		if (request.entries[1].size() == 1)
			this->_topic = "";
		else
		{
			request.response.clear();
			if (request.entries[1][0] != ':')
				errInCmd(request, errNeedMoreParams(user, request.command));
			else
			{
				this->_topic = request.entries[1];
				for (size_t i = 2; i < request.entries.size(); i++){
					this->_topic += " " + request.entries[i];
				}
				request.target.insert(request.target.end(), users.begin(), users.end());
				request.response = ":" + request.origin.setPrefix() + " " + "TOPIC #" + this->getName() + " " + _topic;
			}
		}
	}
	serv->chan_requests(request);
	
}

void Channel::part(Request& request, Server* serv)
{
	(void)serv;
	string user = request.origin.getName();
	vector<Client*>::iterator it;
	
	request.response.clear();
	if (!isInChanList(request.origin, users))
		errInCmd(request, errNotOnChannel(this->getName()));
	else
	{
		request.target.insert(request.target.end(), users.begin(), users.end());
		// request.response = user + " leaves #" + this->getName() + " " + request.message + '\n';
		request.response = ":" + request.origin.setPrefix() + " PART #" + this->getName() + " " + request.message;
		serv->chan_requests(request);
		removeUser(user);
		// request.origin.removeChanFromList(this);
		
	}
}

void Channel::privmsg(Request& request, Server* serv)
{
	(void)serv;
	string user = request.origin.getName();
	vector<Client*>::iterator it;

	request.target.clear();
	request.response.clear();
	if (!isInChanList(request.origin, users) && request.command == "PRIVMSG")
		return (errInCmd(request, errNotOnChannel(this->getName())));
	if (activeMode('m') && (!isInChanList(request.origin, _operators) || !isInChanList(request.origin, _vocal)))
		return (errInCmd(request, errCannotSendToChan(user, this->getName())));
	request.target.insert(request.target.begin(), users.begin(), users.end());
	request.target.erase(it=existing_user(request.target, user));
	request.response = ":" + user + " " + request.command + " #" + this->getName() + " " + request.message;
	
}

// work in progress
void Channel::mode(Request& request, Server* serv)
{
	(void)serv;
	string user = request.origin.getName();
	if (!isInChanList(request.origin, this->_operators))
		return(errInCmd(request, errChanPrivsNeeded(user, this->getName())));
	addMode(request, request.entries, serv);
}

void Channel::kick(Request& request, Server* serv)
{
	string user = request.origin.getName();
	vector<Client*>::iterator it;

	request.response.clear();
	if (!isInChanList(request.origin, users))
		return (errInCmd(request, errNotOnChannel(this->getName())));
	if (!isInChanList(request.origin, _operators))
		return(errInCmd(request, errChanPrivsNeeded(user, this->getName())));
	if ((it = existing_user(users, request.user_to_kick)) == users.end())
		return(errInCmd(request, errNoSuchNick(user, request.entries[1])));
	request.target.insert(request.target.end(), users.begin(), users.end());
	request.response = ":" + request.origin.setPrefix() + " KICK #" + this->getName() + " " + request.user_to_kick + " :" + request.message;
	serv->chan_requests(request);
	removeUser(request.user_to_kick);
	request.target.clear();
}

void Channel::names(Request& request,Server* serv)
{
	(void)serv;
	vector<Client*>::iterator it;

	request.reply += this->getName() + ":\n";
	for (it = users.begin(); it != users.end(); it++){
		if ((*it)->checkMode('i') == false)
		{
			if (find(_operators.begin(), _operators.end(), (*it)) != _operators.end())
				request.reply += '@';
			else
				request.reply += ':';
			request.reply += (*it)->getName() + ", ";
		}
	}
	request.reply.replace(request.reply.size() -2, 2, "\n");
}