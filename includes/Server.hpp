/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:38:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 23:48:48 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <map>
# include <vector>
# include <iostream>
# include <algorithm>
# include <string>
# include <cstring>
# include <utility>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "Client.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include "Marvin.hpp"
# include "numeric_replies.hpp"
// #include "sig.hpp"
// # include "Colors.hpp"

class Client;
class Request;
class Channel;
class Socket;
class Marvin;

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
	
	/* ***************** */
	/* **** GETTERS **** */
	/* ***************** */
	int								get_socket() const;
	std::string						get_name() const;
	std::string						get_pass() const;
			
	/* ***************** */
	/* **** METHODS **** */
	/* ***************** */
	/*
	---- INIT METHODS
	*/
	int								init_socket_server();
	struct sockaddr_in				set_socket_datas();
	/*
	---- RUNNING METHODS
	*/
	void							update_user_data(Request& request, std::string old_name, std::string new_nick);
	void							handle_request(char *buf, int fd_client, int readBytes, int i);
	void							read_client_req(int fd_client, int i);
	void							chan_requests(Request& req);
	int								treating_req(Request& req);
	void							init_pollfd_struct();
	int								manage_connections();
	int 							start_server();
	int								new_client();
	int								routine();
	/*
	---- DISCONNECT METHODS 
	*/
	void							removeClient(std::vector<Client>::iterator to_remove);
	void							disconnectAll();
	/*
	---- CHANNELS AND CLIENTS DATA
	*/
	struct pollfd*								client_events;
	std::vector<Client> 						all_clients;
	std::vector<Channel>						all_channels;
	std::map<std::string, std::string>			opers;
	Marvin*										marvin;
	char 										read_buffer[1000];
	size_t 										readBytes;


	
private:

	int					_socket;
	struct sockaddr_in	_address;
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