/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:18:23 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/01 18:15:47 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Request.hpp"

static bool sortClients(Client& a, Client& b)
{
	return a.getChanNbr() < b.getChanNbr();
}

void all_chan_names(Request& requ, Server* serv)
{
	std::vector<Channel>::iterator it = serv->all_channels.begin();
	
	while (it != serv->all_channels.end())
	{
		if (it->activeMode('s') == false)
		{
			it->names(requ, serv);
			requ.reply += rpl_endofnames(requ.origin.setPrefix(), it->getName());
		}
		it++;
	}
	sort((serv->all_clients.begin()), (serv->all_clients.end()), sortClients);
	if (serv->all_clients[0].getChanNbr() == 0)
	{
		requ.reply += "*: \n";
		size_t i = 0;
		while(i < serv->all_clients.size() && serv->all_clients[i].getChanNbr() == 0)
		{
			if (serv->all_clients[i].checkMode('i') == false)
				requ.reply += serv->all_clients[i].getName() + ", ";
			i++;
		}
		requ.reply.replace(requ.reply.size() - 2, 2, "\n");
		requ.reply += rpl_endofnames(requ.origin.setPrefix(), "*");
	}
}