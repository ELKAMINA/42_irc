/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_chan_cmds.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:23:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/24 11:07:40 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int Request::_join(Client *cli, Server *serv)
{

	if (_check_lists() != 0)
	{
		removing_sharp(entries);
		if (jo_nb_chan > 1)
			multiChan(cli, serv);
		else
			oneChan(cli, serv);
	}
	return 0;
}

int Request::_part(Client *cli, Server *serv)
{
	vector<Channel *>::iterator it;
	if (_check_lists() != 0)
	{
		if (entries.size() > jo_nb_chan)
			req_get_comments(entries, jo_nb_chan);
	}
	else
		reply = errNoSuchChannel(cli->getNickName(), entries[0]);
	serv->_chan_requests(*this);
	size_t i = 0;
	if (reply == "UNDEFINED")
	{
		removing_sharp(entries);
		while (i < jo_nb_chan)
		{
			Channel *tmp = existing_chan(entries[i], serv);
			if (!tmp)
			{
				reply = errNoSuchChannel(cli->getNickName(), entries[i]);
				return 1;
			}
			else
			{
				tmp->part(*this, serv);
				// temporary solution, need to improve it
				if (tmp->getOnlineCount() == 0)
				{
					for (size_t j = 0; j < serv->all_chanels.size(); j++)
					{
						if (serv->all_chanels[i]->getName() == tmp->getName())
							serv->all_chanels.erase(serv->all_chanels.begin() + i);
					}
				}
			}
			i++;
		}
	}
	// else
		// serv->_chan_requests(*this);
	return 0;
}

int Request::_kick(Client *cli, Server *serv)
{
	// sleep(10);
	if (_check_lists() != 0)
	{
		jo_nb_chan = 0;
		std::vector<std::string>::iterator ita = entries.begin();
		while (ita != entries.end())
		{
			std::cout << "Entriiies " << (*ita) << std::endl;
			ita++;
		}
		beginning_with_diez(entries);
		removing_sharp(entries);
		if (reply == "UNDEFINED")
		{
			size_t users_toKick = 0;
			if (entries.size() > jo_nb_chan)
			{
				std::vector<std::string>::iterator it = entries.begin() + jo_nb_chan;
				bool comment = false;
				size_t nb = 0;
				while (it != entries.end())
				{
					if ((*it)[0] == ':')
					{
						while (it != entries.end())
						{
							message.clear();
							message += *it;
							message += ' ';
							it++;
							comment = true;
							nb++;
						}
					}
					if (comment == false)
						it++;
				}
				users_toKick = entries.size() - jo_nb_chan - nb;
			}
			if ((jo_nb_chan >= 1 && !users_toKick))
				reply = errNeedMoreParams(cli->getNickName(), _command);
			size_t i = 0;
			// std::cout << "nb of channels " << jo_nb_chan << std::endl;
			while (i < jo_nb_chan)
			{
				Channel *tmp = existing_chan(&entries[i][1], serv);
				if (!tmp)
					reply = errNoSuchChannel(cli->getNickName(), "No such Channel");
				else
				{
					user_to_kick.clear();
					user_to_kick = entries[jo_nb_chan];
					tmp->kick(*this, serv);
				}
				i++;
			}
		}
	}
	return 0;
}

int Request::_topic(Client *cli, Server *serv)
{
	Channel *tmp = existing_chan(&entries[0][1], serv);
	if (tmp)
		tmp->topic(*this, serv);
	else
	{
		reply = errNoSuchChannel(cli->getNickName(), entries[0]);
		serv->_chan_requests(*this);
		return 1;
	}
	return 0;
}

int Request::_mode(Client *cli, Server *serv)
{
	beginning_with_diez(entries);
	if (jo_nb_chan == 1 && (entries[0][0] == '#' || entries[0][0] == '&'))
	{
		if (entries.size() > 1)
			_mode_for_chans(cli, serv);
	}
	else if (jo_nb_chan == 0 && entries.size() >= 2)
		_mode_for_clis(cli, serv);
	return 0;
}
