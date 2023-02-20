/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:14:59 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/16 14:51:21 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

static bool sortClients(Client* a, Client* b)
{
	return a->getChanNbr() < b->getChanNbr();
}

Client* Request::_find(std::string dest, Server *serv)
{
	std::vector<Client *>::iterator it = serv->all_clients.begin();

	while (it != serv->all_clients.end())
	{
		if	((*it)->getNickName() == dest)
			return *it;
		it++;
	}
	return *(serv->all_clients.end());
}

std::vector<Client* >::iterator Request::_findFd(int dest, Server *serv)
{
	std::vector<Client *>::iterator it = serv->all_clients.begin();

	while (it != serv->all_clients.end())
	{
		if	((*it)->getFdClient() == dest)
			return it;
		it++;
	}
	return (serv->all_clients.end());
}

int Request::wrong_nickname()
{
	for (size_t i = 0; i < entries[0].size() - 1; i++)
	{
		if	((isalnum(entries[0][i]) == 0 || entries[0].size() > 9) && entries[0][i]  != '-')
			return 0;
	}
	return 1;
}

Channel* Request::existing_chan(std::string name, Server *serv)
{
	std::vector<Channel *>::iterator it = serv->all_chanels.begin();
	while(it != serv->all_chanels.end())
	{ 
		if ((*it)->getName() == name)
			return *it;
		it++;
	}
	return NULL;
}

int Request::beginning_with_diez(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.begin();
	while (it != entries.end())
	{
		if ((*it)[0] != '#' && (*it)[0] != '&')
			return 0;
		it++;
		jo_nb_chan++; /* Counting nb of diez in the req to check it with the nb of keys*/
	}
	return 1;
}

void Request::resizing_chan(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.begin();
	while (it != entries.end())
	{
		(*it).erase(0,1);
		it++;
	}
}

void Request::counting_keys(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.begin() + (jo_nb_chan - 1);
	while (it != entries.end())
	{
		it++;
		jo_nb_keys++; /* Counting nb of diez in the req to check it with the nb of keys*/
	}
	return ;
}

std::string Request::removing_backslash(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.end() - 1;
	it->erase(it->size() - 1,1);
	return(*it);
}

void Request::removing_sharp(std::vector<std::string>& en)
{
	size_t i = 0;
	while (i < jo_nb_chan)
	{
		if ((en[i][0] == '#' || en[i][0] == '&') && (_command == "JOIN" || _command == "PART"))
			en[i].erase(0,1);
		i ++;
	}
}


void Request::oneChan(Client* cli, Server *serv)
{
	Channel *tmp;
	tmp = existing_chan(entries[0], serv);
	this->status = ongoing;
	// bool yes = false;
	if(jo_nb_keys > jo_nb_chan)
		reply = errNeedMoreParams("bad value", this->_command);
	if (tmp != NULL) /* Channel existe */
	{
		if ((tmp->activeMode('k') == true && entries.size() == 1)
		|| (tmp->activeMode('k') == false && entries.size() > 1))
		{
			// std::cout << "heeeere " << std::endl;
			reply = errBadChannelKey(_origin->getNickName(), tmp->getName());
			return ;
			// serv->replied = true;
		}
		else
		{
			status = ongoing;
			tmp->cmd_lexer(*this, serv);
		}

	}
	else
	{
		Channel *to_add;
		if (entries.size() == 1)
		{
			to_add = new Channel((serv->all_clients), entries[0],  *cli);
		}
		else
		{

			std::cout << "oui oui " << entries[1] << std::endl;
			to_add = new Channel((serv->all_clients), entries[0], entries[1], *cli);
		}
		_origin->setMode('o', true); /* Set the first user to operator*/
		serv->all_chanels.push_back(to_add);
		to_add->cmd_lexer(*this, serv);
	}	 
}

void Request::multiChan(Client* cli,Server *serv)
{
	(void)serv;
	(void)cli;
	Channel* tmp;
	if(jo_nb_keys > jo_nb_chan)
	{
		reply = errBadChannelKey(_origin->getNickName(), "One of them");
		return ;
	}
	size_t i = 0;
	size_t k = jo_nb_chan;
	// std::cout << "Nb de keys " << jo_nb_keys << std::endl;
	while (i < k)
	{
		tmp = existing_chan(entries[i], serv);
		if (tmp == NULL)
		{
			Channel *to_add;
			if (jo_nb_keys != 0) /* cela veut dire quil ya des mdp pr les chans*/
			{
				to_add = new Channel((serv->all_clients), entries[i], ((entries[i + jo_nb_chan])), *cli);
				jo_nb_keys--;
			}
			else 
			{
				to_add = new Channel((serv->all_clients), entries[i], *cli);
			}
			serv->all_chanels.push_back(to_add);
			status =  ongoing;
			to_add->cmd_lexer(*this, serv);

		}
		else
		{
			if (tmp->activeMode('k') == true)
			{
				if (jo_nb_keys != 0)
				{
					jo_nb_keys--;
					status = ongoing;
					tmp->cmd_lexer(*this, serv);
					cli->addChanToList(tmp);
				}
				else
				{
					reply = errNeedMoreParams("bad value", this->_command);
					serv->replied = true;
				}
			}
			else
			{
				if (jo_nb_keys != 0)
				{
					reply = errNeedMoreParams("bad value", this->_command);
					serv->replied = true;					
				}
				else
				{
					status = ongoing;
					tmp->cmd_lexer(*this, serv);
					cli->addChanToList(tmp);
				}
			}
			this->target.clear();
		}
		i++;
	}
	
}

void Request::_mode_for_chans(Client* cli, Server* serv)
{
	Channel *tmp = existing_chan(&entries[0][1], serv);
	if (tmp)
		tmp->cmd_lexer(*this, serv);
	else
	{
		reply = errNoSuchChannel(cli->getNickName(), entries[0]);
		serv->replied = true;
	}
	serv->_chan_requests(*this);
}

std::string		Request::retrieve_cliModes(Client* tmp)
{
	std::string prefix;
	prefix = tmp->getNickName() + " " + tmp->getmode() + "\n";
	return prefix;
}

void Request::_mode_for_clis(Client* cli, Server* serv)
{
	Client* tmp = _find(entries[0], serv);
	if (tmp != NULL)
	{
		if (tmp->callToMode == 0) /* TO deal with MODE + i from the client, at the beginning*/
		{
			tmp->callToMode++;
			return ;
		}
		if (mode_validity() == 0)
			reply = errUModeUnknownFlag(cli->getNickName(), ":Unknown MODE flag\n");
		if (entries[1][0] == '+')
		{
			if (entries[1][1] == 'o')
				return ;
			tmp->setMode(entries[1][1], true);
		}
		else if (entries[1][0] == '-')
		{
			if (entries[1][1] == 'r')
				return ;
			tmp->setMode(entries[1][1], false);
		}
		reply = rpl_umodeis(retrieve_cliModes(tmp), tmp->getNickName());
		tmp->callToMode ++;
	}
	else
		reply = errUsersDontMatch(cli->getNickName(), ":Cannot change mode for other users\n");
	// serv->replied = true;
}

int Request::mode_validity()
{
	char c = entries[1][1];
	if (entries[1].size() != 2 || entries[1][0] != '+' || entries[1][0] != '-')
		return 0;
	if (c != away && c != invisible && c != localOp && c != restricted && c != op && c != wallops)
		return 0;
	return 1;
}

void Request::chan_names(Server* serv)
{
	std::vector<Channel*>::iterator it = serv->all_chanels.begin();
	while (it != serv->all_chanels.end())
	{
		// std::cout << "je rentre ici 2 " << std::endl;
		if ((*it)->activeMode('s') == false)
		{
			(*it)->cmd_lexer(*this, serv);
			reply += rpl_endofnames(*this, (*it)->getName(), "option");
		}
		it++;
	}
}

void Request::noChan_names(Server* serv)
{
	sort((serv->all_clients.begin()), (serv->all_clients.end()), sortClients);
	std::string rep;
	if (serv->all_clients[0]->getChanNbr() == 0)
	{
		reply += "*: \n";
		size_t i = 0;
		while(i < serv->all_clients.size() && serv->all_clients[i]->getChanNbr() == 0)
		{
			if (serv->all_clients[i]->checkMode('i') == false)
			{
				rep.clear();
				rep = serv->all_clients[i]->getNickName() + ", ";
				reply += rep;
			}
			i++;
		}
		reply.replace(reply.size() - 2, 2, "\n");
		reply += rpl_endofnames(*this, "*", "option");
	}
}

int Request::_check_lists()
{
	if (entries.size() >= 1)
		first_arg_for_entries(entries);
	if (entries.size() >= 2)
		second_arg_for_entries(entries);
	if (_verifications() == 0)
		return 0;
	return 1;
}

int Request::_verifications()
{
	if (_command == "JOIN" || _command == "PART" || _command == "NAMES" || _command == "LIST" || _command == "KICK")
	{
		if (_channels.size() >= 1)
		{
			beginning_with_diez(_channels);
			if (jo_nb_chan != _channels.size())
				return 0;
		}
		if (_else.size() >= 1)
		{
			jo_nb_keys = _else.size();
			if (_command == "PART")
			{
				if (_else[0][0] != '\0' && (_else[0][0] != ':'))
					return 0;
			}
			else
			{
				if (jo_nb_keys > jo_nb_chan)
					return 0;
			}
		}
	}

	_transformations();
	return 1;
}

int Request::_transformations()
{
	if (commas_c == false && commas_e == true)
	{
		entries.erase(entries.begin());
		entries.insert(entries.begin(), _channels.begin(), _channels.end());
	}
	else if (commas_c == false && commas_e == false)
	{
		entries.erase(entries.begin());
		entries.erase(entries.begin() + 1);
		entries.insert(entries.begin(), _channels.begin(), _channels.end());
		entries.insert(entries.begin() + _channels.size(), _else.begin(), _else.end());
	}
	return 1;
}