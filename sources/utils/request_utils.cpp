/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:18:23 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 21:02:33 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Request.hpp"

void all_chan_names(Request& requ, Server* serv)
{
	std::map<std::string, Channel>::iterator it_cha = serv->all_channels.begin();
	std::map<std::string, Client>::iterator it_cli = serv->all_clients.begin();
	std::map<std::string, Client>::iterator it_sender;

	it_sender = serv->all_clients.find(requ.origin);

	while (it_cha != serv->all_channels.end())
	{
		if (it_cha->second.activeMode('s') == false)
		{
			it_cha->second.names(requ, serv);
			requ.reply += rpl_endofnames(it_sender->second.setPrefix(), it_cha->second.getName());
		}
		it_cha++;
	}
	if (serv->all_clients[0].getChanNbr() == 0)
	{
		requ.reply += "*: \n";
		size_t i = 0;
		for( ; it_cli != serv->all_clients.end(); it_cli++){ 
			if (it_cli->second.checkMode('i') == false && it_cli->second.getChanNbr() == 0)
				requ.reply += it_cli->first + ", ";
			i++;
		}
		requ.reply.replace(requ.reply.size() - 2, 2, "\n");
		requ.reply += rpl_endofnames(it_sender->second.setPrefix(), "*");
	}
}