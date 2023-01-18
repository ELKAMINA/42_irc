/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:37:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 14:14:04 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP


# include <vector>
# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include "Server.hpp"
# include "Socket.hpp"

class ServerSocket;

class Server
{
public:

	/* CONSTRUCTORS */
	Server(int domain, int service, int protocol, int port, u_long interface, int backlog);
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

/* EXCEPTIONS ????*/

	/* METHODS */
	int start_server();
	int bind_port();
	// config method

	std::vector<ServerSocket> server_sockets;

	
private:

	struct sockaddr_in _address;
	int					_socket;
	int					_domain;
	int					_service;
	int					_protocol;
	int					_port;
	int					_backlog;
	u_long				_interface;
	std::string			_name;

	// std::map<undefined, undefined>_server_socket;
	// std::map<undefined, undefined>_client_socket;
};

#endif