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


#include "Server.hpp"
# include "./Colors.hpp"
# include <vector>
# include <iostream>
# include <string>
# include <cstring>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include <utility>
# include "ServerSocket.hpp"
# include <map>
# include "Client.hpp"
# include "Request.hpp"
# include "./numeric_replies/numeric_replies.hpp"

class Client;
class Request;

struct cinfo
{
	int fd;
	char buf[30000 + 1];
	int n;
	int state;
	int	id_requests;
};

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
	void 			start_server();
	int				routine();
	void			new_client();
	void			read_client_req(Client* cli, int *i);
	void			write_to_client(struct pollfd client);
	std::string		welcoming_newClients();
	
	/* Utils */
	int	is_charset(char c);


	/* Receiving and handling request */
	void			handle_request(char *buf, int *i, Client *cli);
	void			check_req_validity(Request **req);
	void			_parsing(Client *cli, Request *req, std::vector<Request*>);

	cinfo					global;
	std::string				name; // limited to 63 characters
	ServerSocket*			server_socket;

	struct pollfd*			_client_events;
	struct pollfd*			_server_events;
	int 					nb_client_events; // aka nfds
	char 					read_buffer[30000 + 1];
	int n_ci;
	int fd_ci;
	std::string 				client_welcoming;
	std::vector<Client *> 		_all_clients;
	// std::map<Client*, Request*>	_req_per_id; /* differentiate Clients by their nickname as it is unique*/
	std::map<Client*, std::vector<Request*> >	_req_per_id; /* differentiate Clients by their nickname as it is unique*/
	// <std::vector<Channel*>		_all_chanels; //list of all existing channels

	
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
};

#endif