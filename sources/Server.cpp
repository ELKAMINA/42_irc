/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:41:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/19 17:31:24 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port, u_long interface, int max_co, std::string name, std::string pass) :
_domain(domain), _service(service), _protocol(protocol), _port(port), _interface(interface), _max_co(max_co), _name(name), _pass(pass)
{
	this->_server_events = new epoll_event;
	this->_client_events = new epoll_event[max_co];
	_online_clients = 0;
	nb_client_events = 0;
}

Server::Server(const Server& rhs)
{
	*this = rhs;
}

Server::~Server()
{
	delete(_server_events);
	delete[](_client_events);
}

Server& Server::operator=(const Server& rhs)
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
	}
	return *this;
}


/* GETTERS */

struct sockaddr_in Server::get_address() const
{
	return _address;
}

// const int& Server::get_socket() const
// {
// 	return _socket;
// }

const int& Server::get_domain() const
{
	return _domain;
}

const int& Server::get_service() const
{
	return _service;
}

const int& Server::get_protocol() const
{
	return _protocol;
}

const int& Server::get_port()const
{
	return _port;
}

const u_long& Server::get_interface() const
{
	return _interface;
}

const std::string& Server::get_name() const
{
	return _name;
}

const std::string& Server::get_pass() const
{
	return _pass;
}

void Server::start_server()
{
	this->server_socket = new ServerSocket(this->_domain, this->_service, this->_protocol,
	this->_port, this->_interface, this->_max_co);
	_server_events->events = EPOLLIN|EPOLLET;
	_server_events->data.fd = server_socket->get_sock();
}

int Server::routine()
{
	this->epfd = epoll_create(20);
	if (epfd == -1)
		return (std::cout << "Failed to create epoll shit " << std::endl, 1);
	// real routine starts here ( or something like that)
	int timeout = 2000;
	epoll_ctl(this->epfd, EPOLL_CTL_ADD, _server_events->data.fd, _server_events);
	epoll_ctl(this->epfd, EPOLL_CTL_MOD, _server_events->data.fd, _server_events);
	while (1)
	{
		nb_client_events += epoll_wait(this->epfd, _client_events, sizeof(_client_events), timeout);
		if (nb_client_events > 0)
		{
			std::cout << "nb of connexions: " << nb_client_events << std::endl;
		}
	}
}
