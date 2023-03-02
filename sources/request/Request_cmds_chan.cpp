/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_cmds_chan.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:23:52 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 12:39:21 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

/* COMMAND LIST */
/* *** JOIN *** INVITE *** PART  *** */
/* *** KICK *** TOPIC  *** NAMES *** */

int Request::join(Server *serv)
{

	if (check_lists() == 0)
	{

		removing_sharp(entries);
		if (nb_chan > 1)
			multiChan(serv);
		else
			oneChan(serv);
	}
	return 0;
}

int Request::invite(Server *serv)
{
	std::vector<Channel>::iterator it = find_obj(&entries[1][1], serv->all_channels);
	if (it != serv->all_channels.end())
		it->cmd_lexer(*this, serv);
	else
		reply = errNoSuchChannel(origin.getName());
	serv->chan_requests(*this);
	return 0;
}

int Request::part(Server *serv)
{
	vector<Channel>::iterator it;

	if (check_lists() == 0)
	{
		if (entries.size() > nb_chan)
			req_get_comments(entries, nb_chan);
	}
	else
		reply = errNoSuchChannel(origin.getName());
	serv->chan_requests(*this);
	size_t i = 0;
	if (reply == "UNDEFINED")
	{
		removing_sharp(entries);
		while (i < nb_chan)
		{
			it = find_obj(entries[i], serv->all_channels);
			if (it == serv->all_channels.end())
			{
				reply = errNoSuchChannel(origin.getName());
				serv->chan_requests(*this);
			}
			else
			{
				it->part(*this, serv);
				if (it->getOnlineCount() == 0)
				{
					for (size_t j = 0; j < serv->all_channels.size(); j++)
					{
						if (serv->all_channels[j].getName() == it->getName())
							serv->all_channels.erase(serv->all_channels.begin() + j);
					}
				}
			}
			i++;
		}
	}
	return 0;
}

int Request::kick(Server *serv)
{
	vector<Channel>::iterator it;

	if (check_lists() == 0)
	{
		nb_chan = count_chan_nbr(entries);
		
		removing_sharp(entries);
		if (reply == "UNDEFINED")
		{
			if (entries.size() >= nb_chan + 2)
				req_get_comments(entries, nb_chan + 1);
			size_t i = 0;
			while (i < nb_chan)
			{
				it = find_obj(&entries[i][1], serv->all_channels);
				if (it == serv->all_channels.end())
					reply = errNoSuchChannel(origin.getName());
				else
				{
					user_to_kick.clear();
					user_to_kick = entries[nb_chan];
					it->kick(*this, serv);
				}
				i++;
			}
		}
	}
	return 0;
}

int Request::topic(Server *serv)
{
	vector<Channel>::iterator it;

	it = find_obj(&entries[0][1], serv->all_channels);
	if (it != serv->all_channels.end())
		it->topic(*this, serv);
	else
	{
		reply = errNoSuchChannel(origin.getName());
		serv->chan_requests(*this);
		return 1;
	}
	return 0;
}

int Request::names(Server *serv)
{
	size_t i = 0;
	
	if (check_lists() == 0)
	{
		if (reply == "UNDEFINED")
		{
			//
			// a virer
			//
			removing_sharp(entries);
			reply.clear();
			if (entries.size() == 0 && nb_chan == 0)
				all_chan_names(serv);
			else
			{
				while (i < entries.size() && nb_chan != 0)
				{
					std::vector<Channel>::iterator it = find_obj(entries[i], serv->all_channels);
					if (it != serv->all_channels.end())
					{
						if (it->activeMode('s') == false)
							it->cmd_lexer(*this, serv);
						reply += rpl_endofnames(origin.setPrefix(), it->getName());
					}
					i++;
				}
			}
		}
	}
	serv->chan_requests(*this);
	return 0;
}
