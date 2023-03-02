/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:38:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/04 08:12:36 by jcervoni         ###   ########.fr       */
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
# include <unistd.h>
# include <stdio.h>
# include "Client.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include "numeric_replies.hpp"
// #include "sig.hpp"
// # include "Colors.hpp"

class Client;
class Request;
class Channel;
class Socket;

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
	// struct sockaddr_in				get_address() const;
	int								get_socket() const;
	// int								get_domain() const;
	// int								get_service() const;
	// int								get_protocol() const;
	// int								get_port() const;
	// const u_long&					get_interface() const;
	std::string						get_name() const;
	std::string						get_pass() const;
			
	/* ***************** */
	/* **** METHODS **** */
	/* ***************** */
	/*
	---- INIT METHODS
	*/
	struct sockaddr_in				set_socket_datas();
	int								init_socket_server();
	/*
	---- RUNNING METHODS
	*/
	int								routine();
	int								new_client();
	int 							start_server();
	void							init_pollfd_struct();
	int								manage_connections();
	// void							close_and_remove_user(Client& cli);
	void							read_client_req(std::vector<Client>::iterator client, int i);
	void							chan_requests(Request& req);
	int								treating_req(Request& req);
	void							handle_request(char *buf, std::vector<Client>::iterator client, int readBytes, int i);
	// bool							contld(char* buf, int nci);
	/*
	---- DISCONNECT METHODS 
	*/
	void							disconnectAll();
	void							removeClient(std::vector<Client>::iterator to_remove);
	/*
	---- CHANNELS AND CLIENTS DATA
	*/
	struct pollfd*								client_events;
	std::vector<Client> 						all_clients;
	std::vector<Channel>						all_channels;
	std::map<std::string, std::string>			opers;
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