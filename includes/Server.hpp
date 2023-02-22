/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:37:43 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/16 15:25:13 by jcervoni         ###   ########.fr       */
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
# include "Channel.hpp"
# include "./numeric_replies/numeric_replies.hpp"
#include "sig.hpp"

class Client;
class Request;
class Channel;
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
	struct sockaddr_in							get_address() const;
	const int&									get_socket() const;
	const int&									get_domain() const;
	const int&									get_service() const;
	const int&									get_protocol() const;
	const int&									get_port() const;
	const u_long&								get_interface() const;
	const std::string&							get_name() const;
	const std::string&							get_pass() const;

/* EXCEPTIONS ????*/				

	/* METHODS */				
	void 										start_server();
	int											routine();
	void										new_client();
	void										read_client_req(Client* cli, int *i);
	std::string									welcoming_newClients();

	/* Utils */							
	int											is_charset(char c);

	/* Receiving and handling re				quest */
	bool										contld(char* buf, int nci);
	void										handle_request(char *buf, int *i, Client *cli, int nci);
	void										_treating_req(Request *request, Client* cli, int* i);
	void										check_req_validity(Request **req);
	void										_chan_requests(Request& req);
	void										_killing_cli(Client& cli);

	std::string									name; // limited to 63 characters
	ServerSocket*								server_socket;

	struct pollfd*								_client_events;
	char 										read_buffer[30000 + 1];
	int											max_c;
	std::string 								client_buffer;	
	std::string 								client_welcoming;
	std::vector<Client* > 						all_clients;
	std::vector<Channel*>						all_chanels;
	bool										replied;
	std::map<std::string, std::string>			opers;


	
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