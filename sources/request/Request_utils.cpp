/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:14:59 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/09 15:40:06 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int Request::user_existence(std::string dest, Server *serv)
{
	// std::map<Client*, std::vector<Request*> >::key_compare my_comp = serv->_req_per_id.key_comp();
	std::map<Client*, std::vector<Request*> >::iterator it = serv->_req_per_id.begin();

	size_t i = 0;
	while (i < serv->_req_per_id.size())
	{
		if	((*it).first->getNickName() == dest)
			return 0;
		i++;
		it++;
	}
	return 1;
}

Client* Request::_find(std::string dest, Server *serv)
{
	// std::map<Client*, std::vector<Request*> >::key_compare my_comp = serv->_req_per_id.key_comp();
	std::map<Client*, std::vector<Request*> >::iterator it = serv->_req_per_id.begin();

	// size_t i = 0;
	while (it != serv->_req_per_id.end())
	{
		if	((*it).first->getNickName() == dest)
			return it->first;
		it++;
	}
	return NULL; // returning the end of the tree
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
	std::vector<Channel *>::iterator it = serv->_all_chanels.begin();
	while(it != serv->_all_chanels.end())
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


void Request::oneChan(Client* cli, Server *serv)
{
	Channel *tmp;
	tmp = existing_chan(entries[0], serv);
	this->status = ongoing;
	if(jo_nb_keys > jo_nb_chan)
		reply = errNeedMoreParams("bad value", this->_command);
	if (tmp != NULL) /* Channel existe */
	{
		if ((tmp->activeMode('k') == true && entries.size() == 1)
		|| (tmp->activeMode('k') == false && entries.size() > 1))
		{
			reply = errPasswMismatch("Wrong Pwd for the Channel", "Wrong WRONG");
			serv->_test = true;
		}
		else
		{
			status = ongoing;
			tmp->cmd_lexer(*this);
		}
		serv->_chan_requests(cli, this, tmp);
	}
	else
	{
		Channel *to_add;
		if (entries.size() == 1)
			to_add = new Channel((serv->_all_clients), entries[0],  *cli);
		else
			to_add = new Channel((serv->_all_clients), entries[0], entries[1], *cli);
		serv->_all_chanels.push_back(to_add);
		to_add->cmd_lexer(*this);
		serv->_chan_requests(cli, this, to_add);
	}	 
}

void Request::multiChan(Client* cli,Server *serv)
{
	(void)serv;
	(void)cli;
	Channel* tmp;
	// entries[0].erase(0, 1); // RÉCUPÉRATION UNIQUEMENT DU NOM DU CHANEL
	// std::vector<std::string>::iterator it = entries.begin();
	// std::cout << "MULTICHAN => " << "nb of keys " << jo_nb_keys << " && " << " Nb of chan " << jo_nb_chan << std::endl;
	if(jo_nb_keys > jo_nb_chan)
	{
		reply = errNeedMoreParams("bad value", this->_command);
		serv->_test = false;
		return ;
	}
	size_t i = 0;
	size_t k = jo_nb_chan;
	while (i < k)
	{
		tmp = existing_chan(entries[i], serv);
		// std::cout << "chan name " << tmp << std::endl;
		if (tmp == NULL)
		{
			Channel *to_add;
			if (jo_nb_keys != 0) /* cela veut dire quil ya des mdp pr les chans*/
			{
				// std::cout << "mdp " << (entries[i + jo_nb_chan]) << std::endl;
				to_add = new Channel((serv->_all_clients), entries[i], ((entries[i + jo_nb_chan])), *cli);
				jo_nb_keys--;
				// i++;
			}
			else 
			{
				// std::cout << " pas de mdp " << std::endl;
				to_add = new Channel((serv->_all_clients), entries[i], *cli);
			}
			serv->_all_chanels.push_back(to_add);
			status =  ongoing;
			to_add->cmd_lexer(*this);
			serv->_chan_requests(cli, this, to_add);
			// std::cout << "jarrive a la fin " << (*(serv->_all_chanels.begin() + i))->getName() << std::endl;
		}
		else
		{
			if (tmp->activeMode('k') == true)
			{
				if (jo_nb_keys != 0)
				{
					// std::string pass_to_verify = (entries[i + jo_nb_chan]);
					// if (pass_to_verify == tmp->getKey())
					// {
						jo_nb_keys--;
						status = ongoing;
						tmp->cmd_lexer(*this);
					}
					else
					{
						reply = errNeedMoreParams("bad value", this->_command);
						serv->_test = true;
					}
				// }
				// else
				// {
				// 	reply = "Key is needed \n";
				// 	serv->_test = true;
				// }
			}
			else //if (tmp->getKey() == "")
			{
				// std::cout << "WALAAAAAAAH " << std::endl;
				if (jo_nb_keys != 0)
				{
					reply = errNeedMoreParams("bad value", this->_command);
					serv->_test = true;					
				}
				else
				{
					status = ongoing;
					tmp->cmd_lexer(*this);
				}
			}
			serv->_chan_requests(cli, this, tmp);
			this->target.clear();
		}
		i++;
	}
	
}
