/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:41:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 14:07:14 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port, u_long interface, int backlog)
{

}

Server::Server(const Server& rhs)
{
	*this = rhs;
}

Server::~Server()
{

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
		this->_socket = rhs._socket;
	}
	return *this;
}


/* GETTERS */

struct sockaddr_in Server::get_address() const
{
	return _address;
}

const int& Server::get_socket() const
{
	return _socket;
}

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

int Server::start_server()
{
	this->_socket = socket(PF_INET, SOCK_STREAM, 0);
		return _socket;
}
