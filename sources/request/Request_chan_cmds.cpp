/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_chan_cmds.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:23:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/16 15:21:56 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int	Request::_join(Client *cli, Server *serv)
{
	(void)cli;
	(void)serv;
	// if (
	// if (entries[0][0] == '0')
	// {
	// 	cli->leaveAllChans();
	// }
	if (_check_lists() != 0)
	{
			removing_sharp(entries);
			// std::vector<std::string>::iterator it = entries.begin();
			// while (it != entries.end())
			// {
			// 	std::cout << "entriiiizzz " << (*it) << "nb of chans " << jo_nb_chan << std::endl;
			// 	it++;
			// }
			if (entries.size() < 1)
				reply = errNeedMoreParams(cli->getNickName(), _command);
			else if (entries[0][0] == '0')
			{}
				/* Leave all channels */
			if (jo_nb_chan > 1)
				multiChan(cli, serv);
			if ((jo_nb_chan == 1 && jo_nb_keys == 0 ) || (jo_nb_chan == 1 && jo_nb_keys == 1))
			{
				std::cout << "nb of chans " << jo_nb_chan << "nb of keys " << jo_nb_keys << std::endl;
				oneChan(cli, serv);
			}
	}
	else
		reply = "Invalid request \n";
	return 0;
}

int	Request::_part(Client *cli, Server *serv)
{
	vector<Channel *>::iterator it;

	if (entries.size() == 0)
	{
		req_validity = notEnough_params;
		return 1;
	}
	if (_check_lists() != 0)
	{
		if (entries.size() > jo_nb_chan)
		{
			if (message == "")
			{
				message.clear();
				size_t i = jo_nb_chan;
				while(i < entries.size())
				{
					message += entries[i];
					message += ' ';
					i++;
				}
			}
		}
	}
	else
	{
		reply = errUnknownCommand(cli->getNickName(), _command); /* on checke si larg apres les chan sil existe commence bien par : qui est le part message*/
		serv->replied = true;
	}
	size_t i = 0;
	if (reply == "UNDEFINED")
	{
		removing_sharp(entries);
		while (i < jo_nb_chan)
		{
			Channel* tmp = existing_chan(entries[i], serv);
			if (!tmp)
			{
				reply = errNoSuchChannel(cli->getNickName(), entries[i]);
				serv->replied = true;
			}
			else
			{
				status = ongoing;
				tmp->cmd_lexer(*this);
				// temporary solution, need to improve it
				// std::cout << "je rentre ici oui ouis " << "getOnlineCount()" << tmp->getOnlineCount() << std::endl;
				if (tmp->getOnlineCount() == 0)
				{
					for (size_t j = 0; j < serv->all_chanels.size(); j++){
						if (serv->all_chanels[i]->getName() == tmp->getName())
						{
							serv->all_chanels.erase(serv->all_chanels.begin() + i);
							// cli->_isInChan--; /* To get nb of chan, the client is in : for NAMES*/
						}
					}
					// serv->all_chanels.erase(it = find(serv->all_chanels.begin(), serv->all_chanels.end(), tmp)); //doesn't work
				}
			}
			serv->_chan_requests(this);
			i++;
		}
	}
	else
		serv->_chan_requests(this);
	return 0;
}


int	Request::_kick(Client *cli, Server *serv)
{
	if (_check_lists() != 0)
	{
		removing_sharp(entries);
		if (reply == "UNDEFINED")
		{
			size_t users_toKick = 0;
			if (entries.size() > jo_nb_chan)
			{
				std::vector<std::string>::iterator it = entries.begin() + jo_nb_chan;
				bool comment =  false;
				size_t nb = 0;
				while (it != entries.end())
				{
					if ((*it)[0] == ':')
					{
						if (isalnum((*it)[1]) == 0)
						{
							req_validity = invalid_req;
							serv->replied = false;
							return 1;
						}
						
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
			if ((jo_nb_chan == 1 && !users_toKick) || (jo_nb_chan > 1 && users_toKick != jo_nb_chan))
				reply = errNeedMoreParams(cli->getNickName(), _command);
			size_t i = 0;
			while (i < jo_nb_chan)
			{
				Channel* tmp = existing_chan(&entries[i][1], serv);
				if (!tmp)
				{
					reply = errNoSuchChannel(cli->getNickName(), "No such Channel");
					serv->replied = true;
				}
				else
				{
					status = ongoing;
					tmp->cmd_lexer(*this);
				}
				serv->_chan_requests(this);
				i++;
			}
		}

	}
	else
		serv->_chan_requests(this);
	return 0;
}

int	Request::_topic(Client *cli, Server *serv)
{
	beginning_with_diez(entries);
	if(jo_nb_chan == 1 && entries[0][0] == '#')
	{
		Channel *tmp = existing_chan(&entries[0][1], serv);
		if (tmp)
			tmp->cmd_lexer(*this);
		else
		{
			reply = errNoSuchChannel(cli->getNickName(), entries[0]);
			serv->replied = true;
		}
		serv->_chan_requests(this);
	}
	else
		req_validity = invalid_req;
	return 1;
}

int	Request::_mode(Client* cli, Server *serv)
{
	std::cout << "je rentre ici ?" << std::endl;
	beginning_with_diez(entries);
	if(jo_nb_chan == 1 && (entries[0][0] == '#' || entries[0][0] == '&'))
		_mode_for_chans(cli, serv);
	else if (jo_nb_chan == 0 && entries.size() >=2)
	{
		_mode_for_clis(cli, serv);
	}
	else
		req_validity = invalid_req;
	return 1;
}
