/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_cmds_serv.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:27:26 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/10 17:53:42 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerStatus.hpp"

/* COMMAND LIST */
/* *** PASS *** NICK *** USER  *** PRIVMSG *** AWAY *** */
/* *** CAP  *** PING *** WHOIS *** LIST    *** KILL *** */
/* *** QUIT *** OPER *** MODE  *** RESTART *** */

int Request::pass(Server *serv)
{
	if (origin->getPwd() != "")
		reply = errAlreadyRegistered();
	else if (entries.size() == 1)
	{
		if (entries[0] == serv->get_pass() && origin->loggedIn == false)
		{
			origin->setPwd(serv->get_pass());
			return 0;
		}
		else if (entries[0] == serv->get_pass() && origin->loggedIn == true)
		{
			reply = errAlreadyRegistered();
		}
		else
		{
			reply = "464 PASS :Password incorrect";
			serv->chan_requests(*this);
			reply = "ERROR :Password incorrect";
			serv->chan_requests(*this);
			return 1;
		}
		serv->chan_requests(*this);
	}
	else
	{
			reply = errNeedMoreParams(origin->getName(), command);
			serv->chan_requests(*this);
			return 0;
	}
	return 0;
}

int Request::nick(Server *serv)
{
	std::string old_nick;
	if (origin->getPwd() != serv->get_pass())
	{
		reply = "464 PASS :Password incorrect";
		serv->chan_requests(*this);
		reply = "ERROR :Password incorrect";
		serv->chan_requests(*this);
		return 1;
	}
	else if (used_nickname(entries[0], serv->names_history) != serv->names_history.end())
	{
		reply = errNicknameInUse(entries[0]);
	}
	else if (entries.empty() == true)
	{
			reply = errErroneusNickname("");
			serv->chan_requests(*this);
			return 0;
	}
	else if (entries.empty() == false && wrong_nickname(entries[0]) == 1)
	{
		reply = errErroneusNickname(entries[0]);
		serv->chan_requests(*this);
		return 0;
	}
	else
	{
		old_nick = origin->getName();
		origin->setNickname(entries[0]);
		serv->names_history.push_back(entries[0]);
		if (origin->loggedIn == true)
		{
			serv->update_user_data(*this, old_nick, entries[0]);
		}
		else if (!origin->loggedIn && origin->getRealName() != "" && origin->getUserName() != "")
		{
			reply = "001 " + origin->getName() + " :Welcome to the Internet Relay Network " + origin->setPrefix() + "!";
			origin->loggedIn = true;
		}
	}
	serv->chan_requests(*this);
	return 0;
}

int Request::user(Server *serv)
{
	if (entries.size() < 4)
		reply = errNeedMoreParams(origin->getName(), command);
	else if (origin->loggedIn == false)
	{
		origin->setUsername(entries[0]);
		origin->setRealname(entries[3]);
		if (origin->getName() != "")
		{
			reply = "001 " + origin->getName() + " :Welcome to the Internet Relay Network " + origin->setPrefix() + "!";
			origin->loggedIn = true;
		}
	}
	else
		reply = errAlreadyRegistered();
	serv->chan_requests(*this);
	return 0;
}

int Request::privmsg(Server *serv)
{
	std::vector<Client>::iterator it_cli;
	std::vector<Channel>::iterator it_cha;

	if (entries[0][0] != '&' && entries[0][0] != '#')
	{
		it_cli = find_obj(entries[0], serv->all_clients);
		if (it_cli != serv->all_clients.end())
		{
			if (it_cli->checkMode('a') == true && command == "PRIVMSG")
				reply = it_cli->getAwayMessage();
			else if (it_cli->checkMode('a') == false)
			{
				req_get_comments(entries, 1);
				target.push_back(it_cli->getName());
				response =  ":" + origin->getName() + " " + command + " " + entries[0]
				+ " " + ((message[0] == ':')? &message[1] : message);
			}
		}
		else if (command == "PRIVMSG")
			reply = "401 " + origin->setPrefix() + " " + entries[0] + " :No such nickname";
	}
	else
	{
		it_cha = find_obj(&entries[0][1], serv->all_channels);
		if (it_cha == serv->all_channels.end() && command == "PRIVMSG")
			reply = errNoSuchChannel(entries[0]);
		else
		{
			req_get_comments(entries, 1);
			it_cha->privmsg(*this, serv);
		}
	}
	serv->chan_requests(*this);
	return 0;
}

int Request::away(Server *serv)
{
	std::string away;

	if (entries.size() == 0)
	{
		if (origin->checkMode('a') == true)
		{
			reply = rpl_unaway(origin->getName(), " :You are no longer marked as being away");
			origin->setMode('a', false);
		}
	}
	else if (entries.size() >= 1 && entries[0][0] == ':')
	{
		origin->setMode('a', true);
		size_t i = 0;
		away += origin->getName() + " ";
		while (i < entries.size())
		{
			away += entries[i];
			away += " ";
			i++;
		}
		origin->setAwayMessage(away);
		reply = rpl_away(origin->getName(), " :You have been marked as being away");
	}
	serv->chan_requests(*this);
	return 0;
}

int Request::cap(Server *serv)
{
	(void)serv;
	return 0;
}

int Request::ping(Server *serv)
{
	if (entries.size() < 1)
		reply = errNeedMoreParams(origin->getName(), command);
	else
		reply = "PONG :" + entries[0];
	serv->chan_requests(*this);
	return 0;
}

int Request::whois(Server *serv)
{
	(void)serv;
	return 0;
}

int Request::who(Server *serv)
{
	(void)serv;
	return 0;
}

int Request::list(Server *serv)
{
	std::vector<Channel>::iterator it_cha = serv->all_channels.begin();
	if (check_lists() == 0)
	{
		string rep = "";

		for ( ; it_cha != serv->all_channels.end(); it_cha++)
		{
			if (!it_cha->activeMode('s'))
				rep += "#" + it_cha->getName() + ", ";
		}
		if (rep.size() != 0)
		{
			rep.replace(rep.size() - 2, 2, "\n");
		}
		reply = rep;
	}
	return 0;
}

int Request::kill(Server *serv)
{
	std::vector<Client>::iterator it_cli;
	
	if (origin->checkMode('o') == false)
		reply = errNoPrivileges(origin->setPrefix() + " :Permission Denied - You're not an IRC operator\n");
	else
	{
		it_cli = find_obj(entries[0], serv->all_clients);
		if (it_cli == serv->all_clients.end())
			reply = "401 " + origin->setPrefix() + " " + entries[0] + " :No such nickname";
		else
		{
			if (entries.size() >= 2)
				req_get_comments(entries, 1);
			killing_process((it_cli), serv);
			return 0;
		}
	}
	serv->chan_requests(*this);
	return 0;
}

int Request::quit(Server *serv)
{
	std::vector<std::string>::iterator it;
	std::vector<Client>::iterator it_cli;
	std::vector<Channel>::iterator target_chan;
	int online = serv->getOnlineClient();

	if (origin->loggedIn == false)
	{
		std::cerr<<"va chier poulet"<<std::endl;
		return 0;
	}
	for (it = origin->chans.begin(); it != origin->chans.end(); it++)
	{
		target_chan = find_obj(*it, serv->all_channels);
		if (target_chan != serv->all_channels.end())
		{
			target_chan->part(*this, serv);
			if (target_chan->getOnlineCount() == 0)
				serv->all_channels.erase(target_chan);
		}
	}
	for (it_cli = serv->all_clients.begin(); it_cli != serv->all_clients.end(); it_cli++){
		if (it_cli->getFdClient() != origin->getFdClient())
			target.push_back(it_cli->getName());
	}
	response = ":" + origin->setPrefix() + " QUIT :" + message;
	serv->chan_requests(*this);
	for (int i = 0; i < online; i++){
		if (serv->client_events[i].fd == origin->getFdClient())
		{
			close(serv->client_events[i].fd);
			serv->client_events[i] = serv->client_events[online - 1];
			serv->decremOnline();
			break ;
		}
	}
	serv->all_clients.erase(origin);
	return 0;
}

int Request::oper(Server *serv)
{
	if (entries.size() == 2)
	{
		if (serv->opers[entries[0]] == entries[1])
		{
			reply = rpl_youreoper("381 " + origin->setPrefix() + " :You are now an IRC operator\n");
			origin->setMode('o', true);
		}
		else
		{
			reply = errPasswMismatch(origin->setPrefix());

		}
	}
	else
		reply = errNoOperHost(":No O-lines for your host\n");
	serv->chan_requests(*this);
	return 0;
}

int Request::mode(Server *serv)
{
	count_chan_nbr(entries);
	if (nb_chan == 1 && (entries[0][0] == '#' || entries[0][0] == '&'))
	{
		if (entries.size() > 1)
		{
			mode_for_chans(serv);
		}
	}
	else if (nb_chan == 0 && entries.size() >= 2)
		mode_for_clis(serv);
	return 0;
}

int Request::restart(Server *serv)
{
	if (origin->checkMode('o') == false)
		reply = errNoOperHost(":No O-lines for your host\n");
	else
	{
		serv->disconnectAll();
		std::cout<<"Disconnecting every clients\n";
		status = 1;
	}
	serv->chan_requests(*this);
	return 0;
}

int Request::marvin(Server* serv)
{
	serv->marvin->cmd_lexer(*this, serv);
	return 0;
}