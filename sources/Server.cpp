/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:41:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/19 17:31:24 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <unistd.h>

Server::Server(int domain, int service, int protocol, int port, u_long interface, int max_co, std::string name, std::string pass) :
_domain(domain), _service(service), _protocol(protocol), _port(port), _interface(interface), _max_co(max_co), _name(name), _pass(pass)
{
	// this->_server_events = new pollfd;
	_online_clients = 0;
	this->_client_events = new pollfd[max_co];
	for (int i = 0; i < max_co; i++)
	{
		_client_events[i].events = 0;
		_client_events[i].revents = 0;
		_client_events[i].fd = 0;
	}
	_online_clients++;
	global.buf[0] = '\0';
	global.fd = 0;
	global.id_requests = 0;
	global.n = 0;
	global.state = 0;
	// nb_client_events = 1;

}

Server::Server(const Server& rhs)
{
	*this = rhs;
}

Server::~Server()
{
	delete(_server_events);
	delete[](_client_events);
}

Server& Server::operator=(const Server& rhs)
{
	if (this != &rhs)
	{
		this->_address = rhs._address;
		this->_domain = rhs._domain;
		this->_service = rhs._service;
		this->_protocol = rhs._protocol;
		this->_port = rhs._port;
		this->_interface = rhs._interface;
		this->_max_co = rhs._max_co;
	}
	return *this;
}


/* GETTERS */

struct sockaddr_in Server::get_address() const
{
	return _address;
}

// const int& Server::get_socket() const
// {
// 	return _socket;
// }

const int& Server::get_domain() const
{
	return _domain;
}

const int& Server::get_service() const
{
	return _service;
}

const int& Server::get_protocol() const
{
	return _protocol;
}

const int& Server::get_port()const
{
	return _port;
}

const u_long& Server::get_interface() const
{
	return _interface;
}

const std::string& Server::get_name() const
{
	return _name;
}

const std::string& Server::get_pass() const
{
	return _pass;
}

void Server::start_server()
{
	this->server_socket = new ServerSocket(this->_domain, this->_service, this->_protocol,
	this->_port, this->_interface, this->_max_co);
	_client_events[0].events = POLLIN;
	_client_events[0].fd = server_socket->get_sock(); /* On the file descriptor data.fd */
}

int Server::routine()
{
	while (1)
	{
		std::cout << "=============== Waiting on poll() ==============" << std::endl;
		std::cout << std::endl;

		int active_co = poll(_client_events, _online_clients, -1); // equivalent epoll_wait: attend qu'un fd devienne dispo
		if (active_co < 0)
		{
			perror("poll creation ");
			return 1;		
		}
		if (active_co == 0)
		{
			perror("poll timeout");
			return 1;		
		}
		for	(int i = 0; i < _online_clients; i++) /* Depending on how many events poll waited to happen */
		{
			/*r_events is an attribute of pollfd structure that is filled by the kernel depending on what type of events we're waiting for*/
			if (_client_events[i].revents == 0) /*revents = 0 means that client_events[i].fd is negative which mean that is not an open file so there isnt any event for now */
				continue;
			if (_client_events[i].revents != POLLIN) /* revent is not POLLIN so dont know what it is*/
			{
				perror("Not Pollin");
				return 1;

			}			
			if	(_client_events[i].fd == server_socket->get_sock()) /*each new client connecting on socket retrieve the server socket fd*/
				new_client();
			else
			{
				if (_client_events[i].events & POLLIN) /*If the fd already exists and its an entry */
					read_client_req(&i);
				// else if(_client_events[i].events & POLLOUT) /*If the fd already exists and its an output*/
				// 	write_to_client(_client_events[i]);
			}						
		}
	}
	close(server_socket->get_sock());
}

void Server::new_client()
{
	int sock = 0;
	std::cout << "=============== Listening socket is readable ==============" << std::endl;
	std::cout << std::endl;

	sock = accept(server_socket->get_sock(), NULL, NULL);
	if(sock < 0)
	{
		perror("accept");
		return ;
	} 
	_client_events[_online_clients].events = POLLIN;
	_client_events[_online_clients].fd =  sock; /*We need to assign to the new client a new fd for the socket it refers to and add it the clients events tab*/
	_online_clients++; /* incrementing the nb of connections */
	std::string homepage = welcoming_newClients();
	if	(send(sock, homepage.c_str(), homepage.length(), 0) == -1)
		perror("Big time for welcoming_ Bravo");
}

std::string Server::welcoming_newClients()
{
	client_welcoming.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	client_welcoming.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	client_welcoming.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	client_welcoming.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	client_welcoming.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	client_welcoming.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
	client_welcoming.append(BLUE);
	client_welcoming.append("Please write PASS then password, NICK then nickname, USER then 5 params to login :)\n");
	client_welcoming.append(RESET);
	return (client_welcoming);
}

void Server::read_client_req(int *i)
{
	n_ci = recv(_client_events[*i].fd, read_buffer, 30000, 0);
	if (n_ci <= 0)
	{
		if	(n_ci == 0)
			std::cout << "The client which fd is " << _client_events[*i].fd << " sent an empty request " << std::endl;
		else
			perror("Baaaad");
		close(_client_events[*i].fd);
		// if nothing received, we need to delete the user 
		_client_events[*i] = _client_events[_online_clients - 1];
		_online_clients--;
	}
	else
	{

		std::cout << read_buffer << std::endl;	
		handle_request(read_buffer, i);
		// if (strcmp(read_buffer, "PASS"))
		// {
		// 	std::cout << "OKKKK on connait " << std::endl;
		// 	std::string ok = "OK man, you can enter";
		// 	send(_client_events[*i].fd, ok.c_str(), ok.size(), 0);
		// }
		// else
		// {
		// 	std::cout << "deso je connais pas " << std::endl;
		// 	std::string ko = "Not good man!";
		// 	send(_client_events[*i].fd, ko.c_str(), ko.size(), 0);
		// }
		// memset(&read_buffer, 0, 30000);
	}
}



void Server::handle_request(char *buf, int* i)
{
	
	Request req(buf);
	std::vector<std::string>::iterator it = req.entries.begin();
	global.id_requests++;
	(void)i;
	parsing_request(&req);
	// (void)it;
	/*	 Verif que l'on recupere bien toute la string 	*/
	while(it != req.entries.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	/* *********************************************** */
}

void Server::parsing_request(Request *req)
{
	req->_id = global.id_requests;

	
}