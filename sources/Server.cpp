/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:41:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/26 17:44:26 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"
#include <unistd.h>

int gstatus = 0;

Server::Server(int domain, int service, int protocol, int port, u_long interface, int max_co, std::string name, std::string pass) : _domain(domain), _service(service), _protocol(protocol), _port(port), _interface(interface), _max_co(max_co), _name(name), _pass(pass)
{
	_online_clients = 0;
	this->_client_events = new pollfd[max_co];
	_online_clients++;
	std::pair<std::string, std::string> pair("oper", "pwdoper");
	opers.insert(pair);
}

Server::Server(const Server &rhs)
{
	*this = rhs;
}

Server::~Server()
{
	delete[] (_client_events);
	all_chanels.clear();
	all_clients.clear();
	opers.clear();
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
		this->all_chanels.clear();
		this->all_chanels = rhs.all_chanels;
		this->all_clients.clear();
		this->all_clients = rhs.all_clients;
		this->_name = rhs._name;
		this->_pass = rhs._pass;
		this->_online_clients = rhs._online_clients;
		this->server_socket->state = rhs.server_socket->state;
		this->_client_events = rhs._client_events;
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

int Server::start_server()
{
	this->server_socket = new Socket(this->_domain, this->_service, this->_protocol,
										   this->_port, this->_interface, this->_max_co);
	this->server_socket->start_server();
	if (server_socket->get_sock() == -1)
	{
		delete (this->server_socket);
		return -1;
	}
	_client_events[0].events = POLLIN | POLLOUT;
	_client_events[0].fd = server_socket->get_sock(); /* On the file descriptor data.fd */
	for (int i = 0; i < _max_co; i++)
	{
		_client_events[i].events = POLLIN | POLLOUT;
		_client_events[i].fd = server_socket->get_sock();
		_client_events[i].revents = POLLIN;
	}
	return 0;
}

int Server::routine()
{
	int active_co;

	while (1)
	{
		active_co = poll(_client_events, _online_clients, -1);
		if (active_co <= 0)
			return (perror("poll error"), 1);
		for (int i = 0; i < _online_clients; i++)
		{
			if (_client_events[i].revents != 0 && _client_events[i].revents & POLLIN)
			{
				if (_client_events[i].fd == server_socket->get_sock())
				{
					std::cout << "Online Clients " << _online_clients << std::endl;
					new_client();
				}
				else
				{
					for (std::vector<Client *>::iterator it = all_clients.begin();it != all_clients.end(); it++){
						if ((*it)->getFdClient() == _client_events[i].fd)
						{
							read_client_req(*it, &(i));
							break ;
						}
					}
				}
			}
		}
	}
}

void Server::new_client()
{
	struct sockaddr_in	clientAddr;
	socklen_t			client_len = sizeof(clientAddr);
	int					sock = 0;

	sock = accept(server_socket->get_sock(),(struct sockaddr *)&clientAddr, &client_len);
	if (sock < 0)
		return (perror("accept"));
	Client* cli = new Client(sock);
	_client_events[_online_clients].events = POLLIN;
	_client_events[_online_clients].fd = sock;
	all_clients.push_back(cli);
	_online_clients++;
}

void Server::read_client_req(Client *cli, int *i)
{
	char read_buffer[1000];
	size_t readBytes = recv(cli->getFdClient(), read_buffer, 1000, 0);
	if (readBytes <= 0)
	{
		if (readBytes == 0)
			std::cout << cli->getFdClient() << " sent an empty_req request " << std::endl;
		else
			perror("recv error");
		close(_client_events[*i].fd);
		_client_events[*i] = _client_events[_online_clients - 1];
		_online_clients--;
	}
	else
		handle_request(read_buffer, cli, readBytes, i);
	memset(&read_buffer, 0, readBytes);
}

bool Server::contld(char* buf, int nci)
{
	int j = 0;
	while (j < nci)
	{
		if (buf[j] == '\n')
			return true;
		j++;
	}
	return false;
}

void Server::handle_request(char *buf, Client *cli, int nci, int*i)
{
	size_t		pos;
	std::string input;
	std::string client_buffer = "";
	const char	*client = NULL;

	buf[nci] = '\0';
	client_buffer += buf;
	std::cout << "Ce qu'envoie IRSSI : " << client_buffer << std::endl;
	while ((pos = client_buffer.find("\r\n")) != std::string::npos)
	{
		input = client_buffer.substr(0, pos + 1);
		client = input.c_str();
		Request req = Request(client, cli);
		client = NULL;
		if (_treating_req(req, cli) == 1)
		{
			close(_client_events[*i].fd);
			_client_events[*i] = _client_events[_online_clients - 1];
			_online_clients--;
			std::vector<Client*>::iterator it = req._find(req._origin->getNickName(), this);
			all_clients.erase(it);
			break ;
		}
		client_buffer.erase(0, pos + 2);
	}
	client_buffer.clear();
	return ;
}

int Server::_treating_req(Request& req, Client* cli)
{
	if (req.check_validity() != 1)
	{
		req.format_entries();
		return (req.requestLexer(cli, this));
	}
	return 0;
}

void	Server::_chan_requests(Request& req)
{
	if (req.response != "UNDEFINED")
	{
		size_t i = 0;
		req.response += "\n";
		std::vector<Client*>::iterator it;
		while (i < req.target.size())
		{
			it = req._find(req.target[i]->getNickName(), this);
			if (send((*it)->getFdClient(), req.response.c_str(), req.response.length(), MSG_DONTWAIT) == -1)
					return (perror("Send"));
			i++;
		}
	}
	if (req.reply != "UNDEFINED")
	{
		req.reply += "\r\n";
		if (send(req._origin->getFdClient(), req.reply.c_str(), req.reply.length(), 0) == -1)
			return (perror("Send"));
	}
}

void Server::_killing_cli(Client& cli)
{
	std::vector<Client*>::iterator ita;
	std::set<Channel*>::iterator it = cli.chans.begin();
	while (it != cli.chans.end())
	{
		std::vector<Channel*>::iterator target = find(all_chanels.begin(), all_chanels.end(), *it);
		if((*target)->isInChanList(&cli, (*target)->_users) == true)
		{
			(*target)->removeUser(&cli);
			if ((*it)->getOnlineCount() == 0)
			{
				all_chanels.erase(target);
			}
		}
		it++;
	}
	ita = find(all_clients.begin(), all_clients.end(), &cli);
	for (int i = 0; i < _online_clients; i++){
		if (_client_events[i].fd == cli.getFdClient())
		{
			close(_client_events[i].fd);
			_client_events[i] = _client_events[0];
			_online_clients--;
			break ;
		}
	}
	all_clients.erase(ita);
}