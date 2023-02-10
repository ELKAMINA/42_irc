/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_chan_cmds.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:23:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/08 18:24:19 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"


int	Request::_join(Client *cli, Server *serv)
{
	/* _Find si chanel existe ou non 
	1. s'il existe alors ajouter le client au chanel
	2. s'il nexiste pas, creer un chanel et rajouter dans la liste des chanel existants et ajouter l'utilisateur à la liste de sutilisateurs du chanel.
	*/
	(void)serv;
	(void)cli;

	if (entries.size() < 1)
		std::cout << "error " << std::endl;
	// entries = _finding_comas(entries[1], serv);
	// std::cout << "new entries " << entries[0] << std::endl;
	beginning_with_diez(entries);
	// std::vector<std::string>::iterator it = entries.end() - 1;
	// it->erase(it->length() - 1, 1); //Removing the \n from the last index
	// std::cout << "Nb of channels " << jo_nb_chan << std::endl;
	if (jo_nb_chan != 0)
	{
		size_t k = jo_nb_chan;
		size_t i = 0;
		// std::vector<std::string>::iterator it = entries.begin();
		while (i < k)
		{
			entries[i].erase(0,1); // removing the character '#'
			i++;
		}
	}
	if (entries.size() > jo_nb_chan)
		jo_nb_keys = entries.size() - jo_nb_chan;
	if (jo_nb_chan > 1)
		multiChan(cli, serv);
	if ((jo_nb_chan == 1 && jo_nb_keys == 0 ) || (jo_nb_chan == 1 && jo_nb_keys == 1))
	{
		// std::cout << "one chan is OK " << std::endl;
		oneChan(cli, serv);
	}
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
	beginning_with_diez(entries);
	if (entries.size() > jo_nb_chan)
	{
		jo_nb_keys = entries.size() - jo_nb_chan;
		if (entries[jo_nb_chan][0] != ':' || (entries[jo_nb_chan][0] == ':' && (entries[jo_nb_chan][1] == ' ')))
		{
			reply = errUnknownCommand(cli->getNickName(), _command); /* on checke si larg apres les chan sil existe commence bien par : qui est le part message*/
			serv->_test = true;
		}
		else
		{
			// std::vector<std::string>::iterator it = entries.end() - 1;
			// std::cout << "Nb of channels " << jo_nb_chan << std::endl;
			// if (jo_nb_chan != 0)
			// {
			// 	size_t k = jo_nb_chan;
			// 	size_t i = 0;
			// 	// std::vector<std::string>::iterator it = entries.begin();
			// 	while (i < k)
			// 	{
			// 		entries[i].erase(0,1); // removing the character '#'
			// 		i++;
			// 	}
			// }
			size_t i = jo_nb_chan;
			if (message == "")
			{
				message.clear();
				while(i < entries.size())
				{
					message += entries[i];
					message += ' ';
					i++;
				}
			}
		}
	}
	size_t i = 0;
	if (reply == "UNDEFINED")
	{
		// std::cout << "NUMBEEERS of chnanan " << jo_nb_chan << " msg = " << msg  << std::endl;
		
		while (i < jo_nb_chan)
		{
			Channel* tmp = existing_chan(&entries[i][1], serv);
			if (!tmp)
			{
				reply = errNoSuchChannel(cli->getNickName(), entries[i]);
				serv->_test = true;
			}
			else
			{
				status = ongoing;
				tmp->cmd_lexer(*this);
				// temporary solution, need to improve it
				if (tmp->getOnlineCount() == 0)
				{
					for (size_t j = 0; j < serv->_all_chanels.size(); j++){
						if (serv->_all_chanels[i]->getName() == tmp->getName())
							serv->_all_chanels.erase(serv->_all_chanels.begin() + i);
					}
					// serv->_all_chanels.erase(it = find(serv->_all_chanels.begin(), serv->_all_chanels.end(), tmp)); //doesn't work
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
	beginning_with_diez(entries);
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
						serv->_test = false;
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
		// std::cout << "NUMBEEERS of chnanan " << jo_nb_chan << " msg = " << msg  << std::endl;
		while (i < jo_nb_chan)
		{
			Channel* tmp = existing_chan(entries[i], serv);
			if (!tmp)
			{
				reply = errNoSuchChannel(cli->getNickName(), "No such Channel");
				serv->_test = true;
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
			serv->_test = true;
		}
		serv->_chan_requests(this);
	}
	else
		req_validity = invalid_req;
	return 1;
}

int	Request::_mode(Client* cli, Server *serv)
{
	beginning_with_diez(entries);
	if(jo_nb_chan == 1 && (entries[0][0] == '#' || entries[0][0] == '&') && entries.size() > 3)
		_mode_for_chans(cli, serv);
	else if (jo_nb_chan == 0 && entries.size() > 3)
		_mode_for_clis(cli, serv);
	return 1;
}
