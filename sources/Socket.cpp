/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:14:08 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 12:21:04 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
	_address.sin_family = domain;

	/* naming a socket =  assigning a transport address to the socket (a port number in IP networking)*/
	_address.sin_port = htons(port);

	_address.sin_addr.s_addr = htonl(interface); /*the interface on which the socket will run (it's the IP Adress) */

	_socket = socket(domain, service, protocol);
	test_connection(_socket);
}

Socket::Socket(const Socket& rhs)
{
	*this = rhs;
}

Socket::~Socket()
{

}

Socket& Socket::operator=(const Socket& rhs)
{
	if (this != &rhs)
	{
		this->_socket = rhs._socket;
		this->_connection = rhs._connection;
		this->_address = rhs._address;
	}
	return *this;
}

void Socket::test_connection(int item_to_test)
{
	if(item_to_test < 0 )
	{
		perror("Failed to connect");
		exit(0);
	}
}

sockaddr_in Socket::get_address() const
{
	return _address;
}
int Socket::get_sock() const
{
	return this->_socket;
}

int Socket::get_connection() const
{
	return this->_connection;
}

void Socket::set_connection(int newC)
{
	this->_connection = newC;
}
