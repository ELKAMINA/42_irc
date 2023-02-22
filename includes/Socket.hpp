/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:09:46 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/22 16:35:25 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

class Socket
{
public:

	Socket(int domain, int service, int protocol, int port, u_long interface, int max_co);
	Socket(const Socket& rhs);

	~Socket();
	Socket& operator=(const Socket& rhs);


	struct sockaddr_in	set_socket_datas();
	int					init_socket_server();
	void				start_server();

	struct sockaddr_in	get_address() const;
	int					get_sock() const;

	int					state;
	
protected:

	int					_socket;
	int					_connection;
	struct sockaddr_in 	_address;
	int					_domain;
	int					_service;
	int					_protocol;
	int					_port;
	u_long				_interface;
	int					_max_co;
};
#endif