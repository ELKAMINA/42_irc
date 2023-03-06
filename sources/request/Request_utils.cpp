/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:26:05 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 21:05:59 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int Request::check_lists()
{
	bool oneChan = true;
	bool oneParam = true;

	oneChan = split_entries(entries[0], channels);
	if (entries.size() > 1)
		oneParam = split_entries(entries[1], params);
	if (verifications() != 0)
	{
		transformations(oneChan, oneParam);
		return (0);

	}
	return 1;
}

bool Request::split_entries(std::string entry, std::vector<std::string>&target)
{
	size_t sharp = 0;
	std::string tmp = entry;
	bool commas = true;
	
	while ((sharp = tmp.find(',')) != std::string::npos)
	{
		target.push_back(tmp.substr(0, sharp));
		tmp.erase(0, sharp + 1);
		commas = false;
	}
	target.push_back(tmp);
	return commas;
}

int Request::verifications()
{
	if (command == "JOIN" || command == "PART" || command == "NAMES" || command == "LIST" || command == "KICK")
	{
		if (channels.size() >= 1)
		{
			count_chan_nbr(channels);
			if (nb_chan != channels.size())
				return 0;
		}
		if (params.size() >= 1)
		{
			nb_keys = params.size();
			if (command == "PART")
			{
				if (params[0][0] != '\0' && (params[0][0] != ':'))
					return 0;
			}
			else
			{
				if (nb_keys > nb_chan)
					return 0;
			}
		}
	}
	return 1;
}

int Request::transformations(bool oneChan, bool oneParam)
{
	if (oneChan == false && oneParam == true)
	{
		entries.erase(entries.begin());
		entries.insert(entries.begin(), channels.begin(), channels.end());
	}
	else if (oneChan == false && oneParam == false)
	{
		entries.erase(entries.begin());
		entries.erase(entries.begin() + 1);
		entries.insert(entries.begin(), channels.begin(), channels.end());
		entries.insert(entries.begin() + channels.size(), params.begin(), params.end());
	}
	return 1;
}

int	Request::count_chan_nbr(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.begin();
	
	nb_chan = 0;
	while (it != entries.end())
	{
		if ((*it)[0] != '#' && (*it)[0] != '&')
			return 0;
		it++;
		nb_chan++;
	}
	return nb_chan;
}

void Request::format_entries()
{
	std::vector<std::string>::iterator it;

	this->entries[this->entries.size() - 1] = removing_backslash(this->entries);
	this->command = this->entries[0];
	std::transform(this->command.begin(), this->command.end(), this->command.begin(), ::toupper);
	it = this->entries.begin();
	this->entries.erase(it);
}

int Request::check_validity() const
{
	std::vector<std::string>::iterator it;

	if (this->raw_input.size() == 1 && (this->raw_input[0] == '\n' || this->raw_input[0] == '\r'))
		return 1;
	if (this->raw_input.size() == 0 || this->raw_input[0] == ' ')
		return 2;
	for (size_t i = 0; i < this->entries[0].size() - 1; i++)
	{
		if (isupper(this->entries[0][i]) == 0)
			return 2;
	}
	return 0;
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
	while (i < nb_chan)
	{
		if ((en[i][0] == '#' || en[i][0] == '&') && (command == "JOIN" || command == "PART"))
			en[i].erase(0,1);
		i ++;
	}
}

void Request::req_get_comments(std::vector<std::string> &entries, size_t j)
{
	if (message == "")
	{
		message.clear();
		while (j < entries.size())
		{
			message.append(entries[j]);
			message.append(" ");
			j++;
		}
	}
}

void Request::set_reason_msg(size_t j)
{
	if (message == "")
	{
		message.clear();
		size_t i = j;
		while (i < entries.size())
		{
			message.append(entries[i]);
			message.append(" ");
			i++;
		}
	}
}

void Request::oneChan(Server *serv)
{
	std::vector<Channel>::iterator it_cha;

	it_cha = find_obj(entries[0], serv->all_channels);
	if (it_cha != serv->all_channels.end())
	{
		if ((it_cha->activeMode('k') == true && entries.size() == 1)
		|| (it_cha->activeMode('k') == false && entries.size() > 1))
		{
			reply = "475 " + origin->getName() + " #" +  it_cha->getName() + " :Cannot join channel (+k)";
			serv->chan_requests(*this);
		}
		else
			it_cha->join(*this, serv);
	}
	else
	{
		if (entries.size() == 1)
		{
			serv->all_channels.push_back(Channel(entries[0], origin->getName()));
		}
		else
			serv->all_channels.push_back(Channel(entries[0], entries[1], origin->getName()));
		serv->all_channels.rbegin()->join(*this, serv);
	}	 
}

void Request::multiChan(Server *serv)
{
	std::vector<Channel>::iterator it_cha;
	size_t i = 0;
	size_t k = nb_chan;

	while (i < k)
	{
		it_cha = find_obj(entries[i], serv->all_channels);
		if (it_cha == serv->all_channels.end())
		{
			if (nb_keys != 0)
			{
				serv->all_channels.push_back(Channel(entries[i], (entries[i + nb_chan]), origin->getName()));
				nb_keys--;
			}
			else 
				serv->all_channels.push_back(Channel(entries[i], origin->getName()));
			serv->all_channels.rbegin()->join(*this, serv);
		}
		else
		{
			if (it_cha->activeMode('k') == true)
			{
				if (nb_keys != 0)
				{
					nb_keys--;
					it_cha->join(*this, serv);
				}
				else
				{
					reply = errBadChannelKey(origin->getName(), it_cha->getName());
					serv->chan_requests(*this);
				}
			}
			else
					it_cha->join(*this, serv);
			this->target.clear();
		}
		i++;
	}	
}

void Request::mode_for_chans(Server* serv)
{
	std::vector<Channel>::iterator it;

	it = find_obj(&entries[0][1], serv->all_channels);
	if (it != serv->all_channels.end())
	{
		it->mode(*this, serv);
	}
	else
	{
		reply = errNoSuchChannel(origin->getName());
		serv->chan_requests(*this);
	}
}

std::string		Request::retrieve_cli_modes(Client& tmp)
{
	std::string prefix;

	prefix = tmp.getName() + " " + tmp.getmode() + "\n";
	return prefix;
}

void Request::mode_for_clis(Server* serv)
{
	std::vector<Client>::iterator it;

	it = find_obj(entries[0], serv->all_clients);
	if (entries[0] != origin->getName())
			reply = errUsersDontMatch();
	else if (it != serv->all_clients.end())
	{
		if (it->callToMode == 0)
		{
			it->callToMode++;
			return ;
		}
		if (mode_validity() == 0)
			reply = errUModeUnknownFlag();
		if (entries[1][0] == '+')
		{
			if (entries[1][1] == 'o')
				return ;
			it->setMode(entries[1][1], true);
		}
		else if (entries[1][0] == '-')
		{
			if (entries[1][1] == 'r')
				return ;
			it->setMode(entries[1][1], false);
		}
		reply = rpl_umodeis(retrieve_cli_modes(*it));
	}
	else
		reply = errUsersDontMatch();
	serv->chan_requests(*this);
}

int Request::mode_validity()
{
	char c = entries[1][1];
	if (entries[1].size() != 2 || entries[1][0] != '+' || entries[1][0] != '-')
		return 0;
	if (c != 'a' && c != 'i' && c != 'o' && c != 'r' && c != 'O' && c != 'w')
		return 0;
	return 1;
}

void Request::killing_process(std::vector<Client>::iterator to_kill, Server* serv)
{
	std::vector<Client>::iterator it_cli;
	
	reply = ":" + origin->setPrefix() + " KILL " + to_kill->getName() + " :" + message + "\n";
	if (send(to_kill->getFdClient(), reply.c_str(), reply.length(), 0) == -1)
		perror("Send");
	reply.clear();
	reply = "ERROR :Killed by " + origin->getName() + " (" +  &message[1] + ")\n";
	if (send(to_kill->getFdClient(), reply.c_str(), reply.length(), 0) == -1)
		perror("Send");
	reply = "UNDEFINED";
	std::string prefix = to_kill->setPrefix();
	it_cli = serv->all_clients.begin();
	for (; it_cli != serv->all_clients.end(); it_cli++){
		if (!(it_cli == to_kill))
			target.push_back(it_cli->getName());
	}
	serv->removeClient(to_kill);
	response = ":" + prefix + " QUIT :Killed by " + origin->getName() + " (" +  &message[1] + ")\n";
	serv->chan_requests(*this);
}

void Request::all_chan_names(Server* serv)
{
	std::vector<Channel>::iterator it_cha = serv->all_channels.begin();
	std::vector<Client>::iterator it_cli = serv->all_clients.begin();
	size_t end_of_names;

	for( ;it_cha != serv->all_channels.end(); it_cha++)
	{
		if (it_cha->activeMode('s') == false)
		{
			it_cha->names(*this, serv);
			reply += rpl_endofnames(origin->setPrefix(), it_cha->getName());
		}
	}
	end_of_names = reply.size();
	if (serv->all_clients[0].getChanNbr() == 0)
	{
		for( ;it_cli != serv->all_clients.end(); it_cli++)
		{
			if (it_cli->checkMode('i') == false)
				reply += it_cli->getName() + ", ";
		}
		reply.replace(reply.size() - 2, 2, "\n");
		reply += rpl_endofnames(origin->setPrefix(), "*");
		reply.replace(end_of_names, 0, "*: \n");
	}
}