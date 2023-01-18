/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:09:46 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 13:54:20 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

class Socket
{
public:

	Socket(int domain, int service, int protocol, int port, u_long interface);
	Socket(const Socket& rhs){};

	~Socket(){};
	Socket& operator=(const Socket& rhs){};

	void test_connection(int socket);

	struct sockaddr_in get_address() const;
	int get_sock() const;
	int get_connection() const;
	void set_connection(int newC);

protected:

	int					_socket;
	int					_connection;
	struct sockaddr_in 	_address;
};
#endif