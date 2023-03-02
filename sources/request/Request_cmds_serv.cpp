/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_cmds_serv.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:27:26 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 22:18:21 by jcervoni         ###   ########.fr       */
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
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(origin);
	if (entries.size() == 1)
	{
		if (entries[0] == serv->get_pass() && it_sender->second.loggedIn == false)
		{
			it_sender->second.setPwd(serv->get_pass());
			return 0;
		}
		else
		{
			reply = errPasswMismatch(entries[0]);
			serv->chan_requests(*this);
		}
	}
	return 1;
}

int Request::nick(Server *serv)
{
	std::map<std::string, Client>::iterator it_cli;

	it_cli = serv->all_clients.find(origin);
	std::cerr<<"dans nick, origin ="<<origin<<std::endl;
	std::cerr<<"dans nick, pass = "<<it_cli->second.getPwd()<<std::endl;
	if (it_cli->second.getPwd() != serv->get_pass())
		reply = errNotRegistered();
	else if (serv->all_clients.find(entries[0]) != serv->all_clients.end())
	{
		reply = errNicknameInUse(entries[0]);
		it_cli->second.setNickname("Guest");
		Client tmp = Client(it_cli->second);
		serv->all_clients.erase(it_cli);
		serv->all_clients.insert(std::make_pair(entries[0], tmp));
	}
	else if (wrong_nickname(entries[0]) == 0)
		reply = errErroneusNickname(entries[0]);
	else
	{
		it_cli->second.setNickname(entries[0]);
		Client tmp = Client(it_cli->second);
		std::cerr<<"dans nick on a set le nickname a "<<it_cli->second.getName()<<std::endl;
		serv->all_clients.erase(it_cli);
		serv->all_clients.insert(std::make_pair(entries[0], tmp));
	}
	serv->chan_requests(*this);
	return 0;
}

int Request::user(Server *serv)
{
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(origin);
	if (it_sender->second.loggedIn == false && origin!= "UNDEFINED")
	{
		it_sender->second.setUsername(entries[0]);
		it_sender->second.setRealname(entries[3]);
		it_sender->second.loggedIn = true;
		reply = "001 " + origin + " :Welcome to the Internet Relay Network "
		+ it_sender->second.setPrefix() + "\r\n";
	}
	else
		reply = errAlreadyRegistered();
	serv->chan_requests(*this);
	return 0;
}

int Request::privmsg(Server *serv)
{
	std::map<std::string, Client>::iterator it_cli;
	std::map<std::string, Channel>::iterator it_cha;

	if (entries[0][0] != '&' && entries[0][0] != '#')
	{
		it_cli = serv->all_clients.find(entries[0]);
		if (it_cli != serv->all_clients.end())
		{
			if (it_cli->second.checkMode('a') == true && command == "PRIVMSG")
				reply = it_cli->second.getAwayMessage();
			else
			{
				req_get_comments(entries, 1);
				message.append("\n");
				target.push_back(it_cli->first);
				response =  ":" + origin + " " + command + " " + entries[0] + " " + &message[1];
			}
		}
		else if (command == "PRIVMSG")
			reply = errNoSuchNick(origin, entries[0]);
	}
	else
	{
		nb_chan = count_chan_nbr(entries);
		it_cha = serv->all_channels.find(&entries[0][1]);
		if (it_cha == serv->all_channels.end() && command == "PRIVMSG")
			reply = errNoSuchChannel(origin);
		else
		{
			req_get_comments(entries, 1);
			it_cha->second.privmsg(*this, serv);
		}
	}
	serv->chan_requests(*this);
	return 0;
}

int Request::away(Server *serv)
{
	std::string away;
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(origin);

	if (entries.size() == 0)
	{
		if (it_sender->second.checkMode('a') == true)
		{
			reply = rpl_unaway(it_sender->first, ":You are no longer marked as being away!\n");
			it_sender->second.setMode('a', false);
		}
	}
	else if (entries.size() >= 2 && entries[0][0] == ':')
	{
		it_sender->second.setMode('a', true);
		size_t i = 0;
		away += it_sender->first + " ";
		while (i < entries.size())
		{
			away += entries[i];
			away += " ";
			i++;
		}
		away += "\n";
		it_sender->second.setAwayMessage(&away[1]);
		reply = rpl_away(it_sender->first, "away");
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
	(void)serv;
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(origin);
	if (entries.size() < 1)
		reply = errNeedMoreParams(origin, command);
	else
		reply = ":" + it_sender->second.setPrefix() + "PONG: " + entries[0] + "\r\n";
	return 0;
}

int Request::whois(Server *serv) /* A modifier avec les bonnes replies */
{
	(void)serv;
	return 0;
}

int Request::list(Server *serv) /* A voir si on garde*/
{
	std::map<std::string, Channel>::iterator it_cha = serv->all_channels.begin();
	if (check_lists() == 0)
	{
		string rep = "";

		for ( ; it_cha != serv->all_channels.end(); it_cha++)
		{
			if (!it_cha->second.activeMode('s'))
				rep += "#" + it_cha->first + ", ";
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
	std::map<std::string, Client>::iterator it_cli;
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(origin);
	if (it_sender->second.checkMode('o') == false)
		reply = errNoPrivileges(it_sender->second.setPrefix() + " :Permission Denied - You're not an IRC operator\n");
	else
	{
		it_cli = serv->all_clients.find(entries[0]);
		if (it_cli == serv->all_clients.end())
			reply = errNoSuchNick(origin, entries[0]);
		else
		{
			if (entries.size() >= 2)
				set_reason_msg(1);
			killing_process(it_cli, serv);
		}
	}
	return 0;
}

int Request::quit(Server *serv)
{
	std::map<std::string, Client>::iterator target;

	target = serv->all_clients.find(origin);
	serv->removeClient(target);
	return 0;
}

int Request::oper(Server *serv)
{
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(origin);
	if (entries.size() == 2)
	{
		if (serv->opers[entries[0]] == entries[1])
		{
			reply = rpl_youreoper("381 " + it_sender->second.setPrefix() + " :You are now an IRC operator\n");
			it_sender->second.setMode('o', true);
		}
		else
			reply = errPasswMismatch(it_sender->second.setPrefix());
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
			mode_for_chans(serv);
	}
	else if (nb_chan == 0 && entries.size() >= 2)
		mode_for_clis(serv);
	return 0;
}

int Request::restart(Server *serv)
{
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(origin);
	if (it_sender->second.checkMode('o') == false)
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