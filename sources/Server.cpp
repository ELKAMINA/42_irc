/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:41:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/13 10:23:11 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"
#include <unistd.h>

int gstatus = 0;

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
	std::pair<std::string, std::string> pair("oper", "pwdoper");
	_opers.insert(pair);
	bif = "";
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
	_client_events[0].events = POLLIN | POLLOUT;
	_client_events[0].fd = server_socket->get_sock(); /* On the file descriptor data.fd */
}

int Server::routine()
{
	while (1)
	{
		// std::cout << "=============== Waiting on poll() ==============" << std::endl;
		std::cout << " je passe ici " << std::endl;
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
				continue;
			// if (_client_events[i].revents != POLLIN) /* revent is not POLLIN so dont know what it is*/
			// {
			// 	perror("Not Pollin");
			// 	return 1;
			// }
			if (_client_events[i].fd == server_socket->get_sock()) /*each new client connecting on socket retrieve the server socket fd*/
			{
				std::cout << "server socket " << server_socket->get_sock() << std::endl;
				std::cout << "Client fd " << _client_events[i].fd << std::endl;
				new_client();
				Client *cli = new Client(_client_events[_online_clients].fd);
				// std::cout << " clients[online_client] " << _client_events[_online_clients].fd << std::endl;
				std::cout << "i =  " << i << " online_client" << _online_clients << std::endl;
				_online_clients++;
				_all_clients.push_back(cli);
				// read_client_req(cli, &i);
			}
			else
			{
				// std::cout << "lolilol " << std::endl;
				if (_client_events[i].events & POLLIN) /*If the fd already exists and its an entry */
				{
					std::vector<Client *>::iterator it = _all_clients.begin();
					while (it != _all_clients.end())
					{
						// std::cout << "here " << (*it)->getFdClient() << " " << _client_events[i].fd << std::endl;
						if ((*it)->getFdClient() == _client_events[i].fd)
						{
							std::cout << "fd client " << (*it)->getFdClient() << std::endl;
							read_client_req(*it, &i);

						}
						it++;
					}
				}
			}
		}
	}
	// std::cout << "juuuure " << std::endl;
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
			std::cout << "The client which fd is " << cli->getFdClient() << " sent an empty_req request " << std::endl;
		else
		{
			perror("Baaaad");
			close(_client_events[*i].fd);
			std::cout << " TOTOTOTO  " << std::endl;
			// potential cause of irssi fail
			// if nothing received, we need to delete the user
			_client_events[*i] = _client_events[_online_clients - 1];
			_online_clients--;
		}
	}
	else
	{
		std::cout << " heheheh  " << std::endl;
		// contld(read_buffer, n_ci);
		handle_request(read_buffer, i, cli, n_ci);
	}
	memset(&read_buffer, 0, 30000); /* Pour reset les saisies Clients*/
}

bool Server::contld(char* buf, int nci)
{
	// std::cout << "buf 2222 " << buf << strlen(buf) << std::endl;
	int j = 0;
	while (j < nci)
	{
		if (buf[j] == '\n')
			return true;
		j++;
	}
	return false;
}

void Server::handle_request(char *buf, int *i, Client *cli, int nci)
{
	/* Creating the request and the client associated */
	// std::cout << "TOTO" << nci << " -- ";
	// if (contld(buf, nci) == false)
	// {
	// 	bif += buf;
	// 	return ;
	// }
	(void)nci;
	bif += buf;
	// memset(&buf, 0, strlen(buf));
	buf = &bif[0];
	std::cout << "buf  " << buf << std::endl;
	// std::cout << "buf[5]" << buf[4] << std::endl;
	size_t pos;
	std::string input;
	const char *client = NULL;
	// std::vector<std::string> 
	Request *req;
	while ((pos = bif.find("\r\n")) != std::string::npos)
	{
		// std::cout << "pos " << pos << std::endl;
		std::cout << "bif ==> " << bif << std::endl;
		input = bif.substr(0, pos + 1); // recup de la cde ligne par ligne à la connexion
		client = input.c_str();
		req = new Request(client, cli);
		_treating_req(req, cli, i);
		bif.erase(0, pos + 2);
	}
	std::cout << " req response " << req->reply << std::endl;
	bif.clear();
}

void Server::_treating_req(Request* req, Client* cli, int* i)
{
	std::vector<Request *> all_req_per_client;
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
		req->reply = errUnknownCommand("Unknown", req->_command);
	else if (req->req_validity == invalid_body)
		req->reply = "Invalid message\n";
	else if (req->req_validity == notEnough_params)
		req->reply = errNeedMoreParams(cli->getNickName(), req->_command);
	else if (req->req_validity == incorrect_pwd)
		req->reply = errPasswMismatch(cli->getNickName(),cli->getNickName());
	else if (req->req_validity == already_registered)
		req->reply = errAlreadyRegistered(cli->getNickName(),cli->getNickName());
	else if (req->req_validity == omitted_cmd)
		req->reply = "Please enter the password or Nickname first\n";
	else if (req->req_validity == invisible_man)
		req->reply = "To Invisible man, you can't send message!\n";
	// else if (req->req_validity == erroneous_nickname)
	// 	req->response = errErroneusNickname(cli, req);
	else if (req->req_validity == nickname_exists)
		req->reply = errNicknameInUse(cli->getNickName(), req->entries[1]);
	else if (req->req_validity == welcome_msg)
	{
		std::ostringstream oss;
		if (cli->getNickName().empty())
			cli->setNickname("*");
		oss << ":" << this->get_name() << " "
			<< "001 " << cli->getNickName() << " " << cli->setPrefix() << "\n";
		std::string var = oss.str();
		req->reply = var;
	}
	else if (req->req_validity == empty_req)
	{
	} /* DO nothing */
	if (_test == false && _client_events[*i].fd != req->_origin->getFdClient())
	{
		if (send(_client_events[*i].fd, req->response.c_str(), req->response.length(), 0) == -1)
			return (perror("Problem in sending from server ")); // a t on le droit ??
	}
	else if (_test == false && _client_events[*i].fd == req->_origin->getFdClient())
	{
		if (req->reply != "UNDEFINED")
			if (send(_client_events[*i].fd, req->reply.c_str(), req->reply.length(), 0) == -1)
				return (perror("Problem in sending from server "));
	}
	std::cout << " mOOOOOOOKKKKK " << std::endl;
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

	if (req->_raw_req.length() == 1 && (req->_raw_req[0] == '\n' || req->_raw_req[0] == '\r')) /* Empty_req entry */
	{
		std::cout << " tooto " << std::endl;
		req->req_validity = empty_req;
		return;
	}
	if (req->_raw_req[0] == ' ' || !req->_raw_req[0])
	{
		req->req_validity = invalid_req;
	}
	for (size_t i = 0; i < req->entries[0].size() - 1; i++)
	{
		if (isupper(req->entries[0][i]) == 0)
		{
			// std::cout << "ici 1 " << std::endl;
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
	req->entries[req->entries.size() - 1] = req->removing_backslash(req->entries);
	req->_command = req->entries[0];
	std::vector<std::string>::iterator it = req->entries.begin();
	// while (it != req->entries.end())
	// {
	// 	std::cout << "iiiitt " << (*it) << std::endl;
	// 	it++;
	// }
	req->entries.erase(it);
};

void Server::_parsing(Client *cli, Request *req, std::vector<Request *> _all_req_per_client)
{
	_all_req_per_client.push_back(req);
	std::pair<Client *, std::vector<Request *> >pairing = std::make_pair(cli, _all_req_per_client);
	/* Verifier si c'est le même client */
	_req_per_id.insert(pairing); // insert Client associated to the client
	req->requestLexer(cli, this);
}

void	Server::_chan_requests(Request *req)
{
	if (req->reply != "UNDEFINED")
	{
		if (send(req->_origin->getFdClient(), req->reply.c_str(), req->reply.length(), 0) == -1)
			return (perror("Problem in sending from server "));
	}
	size_t i = 0;
	// std::cout << "target siiiiize " << req->target.size() << std::endl;
	while (i < req->target.size())
	{
		if (send(req->target[i]->getFdClient(), req->response.c_str(), req->response.length(), 0) == -1)
				return (perror("Problem in sending from server ")); // a t on le droit ?
		i++;
	}
	_test = true;
}

void Server::_killing_cli(Client* cli)
{
	if (close(cli->getFdClient()) < 0)
		std::cout << "Socket couldn't be closed" << std::endl;
	if (cli->getChanNbr() > 0)
	{
		std::vector<Channel*>::iterator it = _all_chanels.begin();
		while (it != _all_chanels.end())
		{
			if ((*it)->isInChanList(cli, _all_clients) == true)
				
			it++;

			/* A voir avec Mitch car demande modif dans Channel pr rajouter fctions liées au remove du client */
		}
	}
}