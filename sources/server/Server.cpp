/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:04:50 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/05 23:01:17 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port, u_long interface, int max_co,
std::string name, std::string pass) : _domain(domain), _service(service), _protocol(protocol),
_port(port), _interface(interface), _max_co(max_co), _name(name), _pass(pass)
{
	_online_clients = 1;
	client_events = new pollfd[_max_co];
	std::pair<std::string, std::string> pair("oper", "pwdoper");
	opers.insert(pair);
	bzero(&read_buffer[0], sizeof(read_buffer));
	readBytes = 0;
	marvin =  new Marvin();
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
