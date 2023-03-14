/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:04:50 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/14 16:25:51 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port, u_long interface, int max_co,
std::string name, std::string pass) : _domain(domain), _service(service), _protocol(protocol),
_port(port), _interface(interface), _max_co(max_co), _name(name), _pass(pass)
{
	_online_clients = 1;
	client_events = new pollfd[_max_co + 1];
	std::pair<std::string, std::string> pair("oper", "pwdoper");
	opers.insert(pair);
	// bzero(&read_buffer[0], sizeof(read_buffer));
	readBytes = 0;
	marvin =  new Marvin();
	dup_nickName = false;
}

Server::Server(const Server &rhs)
{
	*this = rhs;
}

Server &Server::operator=(const Server &rhs)
{
	if (this != &rhs)
	{
		this->_address = rhs._address;
		this->_domain = rhs._domain;
		this->_service = rhs._service;
		this->_protocol = rhs._protocol;
		this->_port = rhs._port;
		this->_interface = rhs._interface;
		this->_max_co = rhs._max_co;
		this->all_channels.clear();
		this->all_channels = rhs.all_channels;
		this->all_clients.clear();
		this->all_clients = rhs.all_clients;
		this->_name = rhs._name;
		this->_pass = rhs._pass;
		this->_online_clients = rhs._online_clients;
	}
	return *this;
}

Server::~Server()
{
	delete[] client_events;
	delete marvin;
	all_channels.clear();
	all_clients.clear();
	names_history.clear();
	opers.clear();
}

/* ***************************** */
/* **** GETTERS **************** */
/* ***************************** */

int Server::get_socket() const
{
	return this->_socket;
}

std::string Server::get_name() const
{
	return _name;
}

std::string Server::get_pass() const
{
	return _pass;
}

int Server::getOnlineClient() const
{
	return this->_online_clients;
}

void Server::decremOnline()
{
	this->_online_clients -= 1;
}
/* ***************************** */
/* **** INIT METHODS *********** */
/* ***************************** */

int Server::start_server()
{
	this->_socket = init_socket_server();
	if (this->get_socket() == -1)
		return -1;
	return 0;
}

void Server::update_user_data(Request& request, std::string old_name, std::string new_name)
{
	std::vector<Channel>::iterator it_cha;
	std::vector<Client>::iterator it_cli;

	for (it_cha = all_channels.begin(); it_cha != all_channels.end(); it_cha++){
		it_cha->updateUser(old_name, new_name);
	}
	for (it_cli = all_clients.begin(); it_cli != all_clients.end(); it_cli++){
			request.target.push_back(it_cli->getName());
	}
	request.response = ":" + old_name + " NICK " + new_name;
}

int Server::treat_leaving_clients()
{
	std::vector<Client>::iterator obj;
	std::vector<Client> tmp;
	int	erased = 0;
	for (int i = 0; i < _online_clients; i++){
		if (client_events[i].revents != 0 && client_events[i].revents & POLLRDHUP)
		{
			obj = find_obj(client_events[i].fd, all_clients);
			if (obj != all_clients.end())
			{
				tmp.push_back(*obj);
				all_clients.erase(obj);
				close(client_events[i].fd);
				client_events[i] = client_events[_online_clients - 1];
				client_events[i].events = POLLIN | POLLRDHUP;
				client_events[i].revents = 0;
				erased++;
			}
			
		}
	}
	for (size_t i = 0; i < tmp.size(); i++){
		std::string rep = ":" + tmp[i].setPrefix() + " QUIT :\n";
		for (size_t j = 0; j < all_clients.size(); j++){
			
			send(all_clients[j].getFdClient(), rep.c_str(), rep.size(), MSG_DONTWAIT);
		}
	}
	tmp.clear();
	return erased;
}