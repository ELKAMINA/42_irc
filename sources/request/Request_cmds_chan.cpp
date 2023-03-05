/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_cmds_chan.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:23:52 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/05 13:41:22 by jcervoni         ###   ########.fr       */
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
		{
			// std::cout << "heroos " << std::endl;
			oneChan(serv);
		}
	}
	return 0;
}

int Request::invite(Server *serv)
{
	std::vector<Channel>::iterator it = find_obj(&entries[1][1], serv->all_channels);
	if (it != serv->all_channels.end())
	{
		std::cerr<<"channel found: "<<it->getName()<<std::endl;
		it->invite(*this, serv);
	}
	else
		reply = errNoSuchChannel(origin->getName());
	serv->chan_requests(*this);
	return 0;
}

int Request::part(Server *serv)
{
	vector<Channel>::iterator it_cha;
	size_t i = 0;

	if (check_lists() == 0)
	{
		if (entries.size() > nb_chan)
			req_get_comments(entries, nb_chan);
	}
	else
		reply = errNoSuchChannel(origin->getName());
	serv->chan_requests(*this);
	if (reply == "UNDEFINED")
	{
		removing_sharp(entries);
		while (i < nb_chan)
		{
			it_cha = find_obj(entries[i], serv->all_channels);
			if (it_cha == serv->all_channels.end())
			{
				reply = errNoSuchChannel(origin->getName());
				serv->chan_requests(*this);
			}
			else
			{
				it_cha->part(*this, serv);
				if (it_cha->getOnlineCount() == 0)
					serv->all_channels.erase(it_cha);
			}
			i++;
		}
	}
	return 0;
}

int Request::kick(Server *serv)
{
	vector<Channel>::iterator it_cha;

	if (check_lists() == 0)
	{
		count_chan_nbr(entries);
		
		removing_sharp(entries);
		if (reply == "UNDEFINED")
		{
			if (entries.size() >= nb_chan + 2)
				req_get_comments(entries, nb_chan + 1);
			size_t i = 0;
			while (i < nb_chan)
			{
				it_cha = find_obj(&entries[i][1], serv->all_channels);
				if (it_cha == serv->all_channels.end())
					reply = errNoSuchChannel(origin->getName());
				else
				{
					user_to_kick.clear();
					user_to_kick = entries[nb_chan];
					it_cha->kick(*this, serv);
				}
				i++;
			}
		}
	}
	return 0;
}

int Request::topic(Server *serv)
{
	vector<Channel>::iterator it_cha;

	it_cha = find_obj(&entries[0][1], serv->all_channels);
	if (it_cha != serv->all_channels.end())
		it_cha->topic(*this, serv);
	else
	{
		reply = errNoSuchChannel(origin->getName());
		serv->chan_requests(*this);
		return 1;
	}
	return 0;
}

int Request::names(Server *serv)
{
	vector<Channel>::iterator it_cha;
	size_t i = 0;
	// std::vector<Client>::iterator it_sender;

	// it_sender = find_obj(origin, serv->all_clients);
	if (check_lists() != 0)
	{
		if (reply == "UNDEFINED")
		{
			removing_sharp(entries);
			reply.clear();
			if (entries.size() == 0 && nb_chan == 0)
				all_chan_names(serv);
			else
			{
				while (i < entries.size() && nb_chan != 0)
				{
					it_cha = find_obj(entries[i], serv->all_channels);
					if (it_cha != serv->all_channels.end())
					{
						if (it_cha->activeMode('s') == false)
							it_cha->names(*this, serv);
						reply += rpl_endofnames(origin->setPrefix(), it_cha->getName());
					}
					i++;
				}
			}
		}
	}
	serv->chan_requests(*this);
	return 0;
}
