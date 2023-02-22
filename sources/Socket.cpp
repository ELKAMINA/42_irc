/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:14:08 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/22 16:35:48 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(int domain, int service, int protocol, int port, u_long interface, int max_co) :
_domain(domain), _service(service), _protocol(protocol), _port(port), _interface(interface), _max_co(max_co)
{

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

struct sockaddr_in Socket::set_socket_datas()
{
	struct sockaddr_in	address;

	address.sin_addr.s_addr = htons(this->_interface);
	address.sin_port = htons(this->_port);
	address.sin_family = AF_INET;
	return address;
}

int Socket::init_socket_server()
{
	int 				sockFd;
	int 				sockAddr;
	int					val = 1;
	struct sockaddr_in	address;

	if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return (perror("socket"), -1);
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) == -1)
	{
		close(sockFd);
		return (perror("set socket options"), -1);
	}
	address = set_socket_datas();
	if ((sockAddr = bind(sockFd, (const sockaddr*)&address, sizeof(address))) == -1)
	{
		close(sockFd);
		return (perror("bind"), -1);
	}
	if ((sockAddr = listen(sockFd, 200)) == -1)
	{
		close(sockFd);
		return (perror("listen"), -1);
	}
	return sockFd;
}

void Socket::start_server()
{
	this->_socket = init_socket_server();
}

sockaddr_in Socket::get_address() const
{
	return _address;
}
int Socket::get_sock() const
{
	return this->_socket;
}

