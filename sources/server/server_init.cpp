/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_init.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:41:31 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/07 11:16:56 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

struct sockaddr_in Server::set_socket_datas()
{
	struct sockaddr_in	address;

	address.sin_addr.s_addr = htons(this->_interface);
	address.sin_port = htons(this->_port);
	address.sin_family = AF_INET;
	return address;
}

int Server::init_socket_server()
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
	if (fcntl(sockFd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(sockFd);
		return (perror("fcntl options"), -1);
	}
	address = set_socket_datas();
	if ((sockAddr = bind(sockFd, (const sockaddr*)&address, sizeof(address))) == -1)
	{
		close(sockFd);
		return (perror("bind"), -1);
	}
	if ((sockAddr = listen(sockFd,42)) == -1)
	{
		close(sockFd);
		return (perror("listen"), -1);
	}
	return sockFd;
}

