/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:37:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/19 12:59:32 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP


# include <vector>
# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/epoll.h>
# include "Server.hpp"
# include "ServerSocket.hpp"

class ServerSocket;

class Server
{
public:

	/* CONSTRUCTORS */
	Server(int domain, int service, int protocol, int port, u_long interface, int max_co, std::string name, std::string pass);
	Server(const Server& rhs);

	/* DESTRUCTOR */
	~Server();

	/* OPERATOR OVERLOAD */
	Server& operator=(const Server& rhs);

	/* GETTERS */
	struct sockaddr_in			get_address() const;
	const int&					get_socket() const;
	const int&					get_domain() const;
	const int&					get_service() const;
	const int&					get_protocol() const;
	const int&					get_port() const;
	const u_long&				get_interface() const;
	const std::string&			get_name() const;
	const std::string&			get_pass() const;

/* EXCEPTIONS ????*/

	/* METHODS */
	void start_server();
	int routine();
	// config method

	ServerSocket*	server_socket;
	// Epoll*			server_epoll;

	struct epoll_event*	_client_events;
	struct epoll_event*	_server_events;
	int	epfd; // epoll instance
	int nb_client_events; // aka nfds
	char read_buffer[30000 + 1];

	
private:

	struct sockaddr_in _address;
	int					_domain;
	int					_service;
	int					_protocol;
	int					_port;
	u_long				_interface;
	int					_max_co;
	std::string			_name;
	std::string			_pass;
	int					_online_clients;


	// std::map<undefined, undefined>_client_socket;
};

#endif