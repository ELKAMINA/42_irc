/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:18:23 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/04 08:11:49 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Request.hpp"

void all_chan_names(Request& requ, Server* serv)
{
	std::vector<Channel>::iterator it_cha = serv->all_channels.begin();
	std::vector<Client>::iterator it_cli = serv->all_clients.begin();
	std::vector<Client>::iterator it_sender;

	it_sender = find_obj(requ.origin, serv->all_clients);

	while (it_cha != serv->all_channels.end())
	{
		if (it_cha->activeMode('s') == false)
		{
			it_cha->names(requ, serv);
			requ.reply += rpl_endofnames(it_sender->setPrefix(), it_cha->getName());
		}
		it_cha++;
	}
	if (serv->all_clients[0].getChanNbr() == 0)
	{
		requ.reply += "*: \n";
		size_t i = 0;
		for( ; it_cli != serv->all_clients.end(); it_cli++){ 
			if (it_cli->checkMode('i') == false && it_cli->getChanNbr() == 0)
				requ.reply += it_cli->getName() + ", ";
			i++;
		}
		requ.reply.replace(requ.reply.size() - 2, 2, "\n");
		requ.reply += rpl_endofnames(it_sender->setPrefix(), "*");
	}
}