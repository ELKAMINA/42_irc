/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:41:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/01 20:05:59 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"
#include <unistd.h>

Server::Server(int domain, int service, int protocol, int port, u_long interface, int max_co, std::string name, std::string pass) : _domain(domain), _service(service), _protocol(protocol), _port(port), _interface(interface), _max_co(max_co), _name(name), _pass(pass)
{
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
	_test = false;
	// nb_client_events = 1;
}

Server::Server(const Server &rhs)
{
	*this = rhs;
}

Server::~Server()
{
	delete (_server_events);
	delete[] (_client_events);
}

Server &Server::operator=(const Server &rhs)
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

const int &Server::get_domain() const
{
	return _domain;
}

const int &Server::get_service() const
{
	return _service;
}

const int &Server::get_protocol() const
{
	return _protocol;
}

const int &Server::get_port() const
{
	return _port;
}

const u_long &Server::get_interface() const
{
	return _interface;
}

const std::string &Server::get_name() const
{
	return _name;
}

const std::string &Server::get_pass() const
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
		// std::cout << "=============== Waiting on poll() ==============" << std::endl;
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
		for (int i = 0; i < _online_clients; i++) /* Depending on how many events poll waited to happen */
		{
			/*r_events is an attribute of pollfd structure that is filled by the kernel depending on what type of events we're waiting for*/
			if (_client_events[i].revents == 0) /*revents = 0 means that client_events[i].fd is negative which mean that is not an open file so there isnt any event for now */
			{
				// std::cout << "here " << std::endl;
				continue;
			}
			if (_client_events[i].revents != POLLIN) /* revent is not POLLIN so dont know what it is*/
			{
				perror("Not Pollin");
				return 1;
			}
			if (_client_events[i].fd == server_socket->get_sock()) /*each new client connecting on socket retrieve the server socket fd*/
			{
				// std::cout << "server socket " << server_socket->get_sock() << std::endl;
				new_client();
				Client *cli = new Client(_client_events[_online_clients].fd);
				// std::cout << " clients[online_client] " << _client_events[_online_clients].fd << std::endl;
				_all_clients.push_back(cli);
				_online_clients++;
			}
			else
			{
				if (_client_events[i].events & POLLIN) /*If the fd already exists and its an entry */
				{

					std::vector<Client *>::iterator it = _all_clients.begin();
					while (it != _all_clients.end())
					{
						// std::cout << (*it)->getFdClient() << _client_events[i].fd << std::endl;
						if ((*it)->getFdClient() == _client_events[i].fd)
							read_client_req(*it, &i);
						it++;
					}
				}
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
	if (sock < 0)
	{
		perror("accept");
		return;
	}
	_client_events[_online_clients].events = POLLIN;
	_client_events[_online_clients].fd = sock; /*We need to assign to the new client a new fd for the socket it refers to and add it the clients events tab*/
	// std::cout << " sock " << sock << "  online clients " << _online_clients << std::endl;
	// _online_clients++; /* incrementing the nb of connections */
	std::string homepage = welcoming_newClients();
	// std::cout << " sock " << sock << homepage.length() << std::endl;
	if (send(sock, homepage.c_str(), 1067, 0) == -1)
		perror("Big time for welcoming_ Bravo");
	// char[50000] = homepage.c_str();
	// memset((homepage.c_str()), 0, 50000);
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

void Server::read_client_req(Client *cli, int *i)
{
	n_ci = recv(cli->getFdClient(), read_buffer, 30000, 0);
	if (n_ci <= 0)
	{
		if (n_ci == 0)
			std::cout << "The client which fd is " << cli->getFdClient() << " sent an empty request " << std::endl;
		else
			perror("Baaaad");
		close(_client_events[*i].fd);
		// if nothing received, we need to delete the user
		_client_events[*i] = _client_events[_online_clients - 1];
		_online_clients--;
	}
	else
	{

		// std::cout << read_buffer << std::endl;
		handle_request(read_buffer, i, cli);
	}
	memset(&read_buffer, 0, 30000); /* Pour reset les saisies Clients*/
}

void Server::handle_request(char *buf, int *i, Client *cli)
{
	/* Creating the request and the client associated */
	std::vector<Request *> all_req_per_client;
	Request *req = new Request(buf, cli);
	_test  =false;
	global.id_requests++;
	req->_id = global.id_requests;
	// cli->setPwd(_pass);

	check_req_validity(&req);
	if (req->req_validity == valid_body || req->req_validity == valid_req)
	{
		_parsing(cli, req, all_req_per_client);
	}
	if (req->req_validity == invalid_req)
		req->response = "Invalid entry\n";
	else if (req->req_validity == invalid_body)
		req->response = "Invalid message\n";
	else if (req->req_validity == notEnough_params)
		req->response = errNeedMoreParams(cli->getNickName(), req->_command);
	else if (req->req_validity == incorrect_pwd)
		req->response = errPasswMismatch(cli->getNickName(),cli->getNickName());
	else if (req->req_validity == already_registered)
		req->response = errAlreadyRegistered(cli->getNickName(),cli->getNickName());
	else if (req->req_validity == omitted_cmd)
		req->response = "Please enter the password or Nickname first\n";
	// else if (req->req_validity == erroneous_nickname)
	// 	req->response = errErroneusNickname(cli, req);
	else if (req->req_validity == nickname_exists)
		req->response = errNicknameInUse(cli->getNickName(), req->entries[1]);
	else if (req->req_validity == welcome_msg)
	{
		std::ostringstream oss;
		if (cli->getNickName().empty())
			cli->setNickname("*");
		oss << ":" << this->get_name() << " "
			<< "001 " << cli->getNickName() << " " << cli->setPrefix() << "\n";
		std::string var = oss.str();
		req->response = var;
	}
	else if (req->req_validity == empty)
	{
	} /* DO nothing */
	if (_test == false)
	{
		if (send(_client_events[*i].fd, req->response.c_str(), req->response.length(), 0) == -1)
			return (perror("Problem in sending from server ")); // a t on le droit ??
	}
	// std::cout << " req response " << req.response << std::endl;
}

int Server::is_charset(char c)
{
	if (isalpha(c))
		return 0; // true
	else
		return 1;
}

void Server::check_req_validity(Request **r)
{
	Request *req = *r;

	if (req->_raw_req.length() == 1 && req->_raw_req[0] == '\n') /* Empty entry */
	{
		req->req_validity = empty;
		return;
	}
	if (req->_raw_req[0] == ' ' || !req->_raw_req[0])
		req->req_validity = invalid_req;
	for (size_t i = 0; i < req->entries[0].size() - 1; i++)
	{
		if (isupper(req->entries[0][i]) == 0)
		{
			req->req_validity = invalid_req;
			return;
		}
	}
	for (size_t i = 0; i < req->_raw_req.size(); i++)
	{
		if ((req->_raw_req[i] == ':' && req->_raw_req[i - 1] != ' ') || (req->_raw_req[i] == ':' && req->_raw_req[i - 1] == ' ' && req->_raw_req[i + 1] == ' '))
		{
			req->req_validity = invalid_body;
			return;
		}
	}
	if (req->entries.size() == 1)
		req->entries[0].resize(req->entries[0].size() - 1); /* Take off the \n*/
	req->_command = req->entries[0];
	std::vector<std::string>::iterator it = req->entries.begin();
	req->entries.erase(it);
	// std::cout << "req entries 0 " << req->entries[0] << " size " << req->entries[0].size() << std::endl;
	// std::cout << "size of req entries 0 " << req->entries[0].size() << std::endl;
}

void Server::_parsing(Client *cli, Request *req, std::vector<Request *> _all_req_per_client)
{
	_all_req_per_client.push_back(req);
	std::pair<Client *, std::vector<Request *> >pairing = std::make_pair(cli, _all_req_per_client);
	/* Verifier si c'est le même client */
	_req_per_id.insert(pairing); // insert Client associated to the client

	/* PASS COMMAND */
	if (req->_command.compare("PASS") == 0)
		req->_pass(cli, this);
	if (req->_command.compare("NICK") == 0)
		req->_nick(cli, this);
	if (req->_command.compare("USER") == 0)
		req->_user(cli, this);
	if (req->_command.compare("PRIVMSG") == 0)
		req->_privmsg(cli, this);
	if (req->_command.compare("JOIN") == 0)
		req->_join(cli, this);
}

void	Server::_chan_requests(Client *cli, Request *req, Channel* chan)
{
	(void)chan;
	(void)cli;
	if (req->reply != "UNDEFINED")
	{
		// std::cout << "replyyyyyy " << req->reply << std::endl;
		if (send(req->_origin->getFdClient(), req->reply.c_str(), req->reply.length(), 0) == -1)
			return (perror("Problem in sending from server ")); // a t on le droit ??
	}
	size_t i = 0;
	std::cout << "target siiiiize " << req->target.size() << std::endl;
	while (i < req->target.size())
	{
		// if (req->req_validity == joining_chan)
		// {
		// req->response = "Ok u joined\n";
		// std::cout 
		// }
		Client* tmp = req->find(req->target[i], this);
		if	(tmp != NULL)	
		{
			if (send(tmp->getFdClient(), req->response.c_str(), req->response.length(), 0) == -1)
				return (perror("Problem in sending from server ")); // a t on le droit ?
			_test = true;
		}
		i++;
	}
}

