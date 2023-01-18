/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:43:34 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 13:59:00 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int domain, int service, int protocol, int port, u_long interface, int bg) :
	Socket(domain, service, protocol, port, interface)
{
	set_connection(connect_to_network(get_sock(), get_address()));
	test_connection(get_connection());
	this->_backlog = bg;
	start_listening();
	test_connection(_listening);
}

ServerSocket::ServerSocket(const ServerSocket& rhs) : Socket(rhs)
{

}

ServerSocket::~ServerSocket()
{

}

int ServerSocket::connect_to_network(int sock, struct sockaddr_in add)
{
	return bind(sock, (struct sockaddr *)&add, sizeof(add));
}

void ServerSocket::start_listening()
{
	_listening = listen(get_sock(), _backlog);
}