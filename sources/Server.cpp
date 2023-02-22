/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:41:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/22 17:41:41 by jcervoni         ###   ########.fr       */
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
	replied = false;
	std::pair<std::string, std::string> pair("oper", "pwdoper");
	opers.insert(pair);
	client_buffer = "";
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
	for (int i = 0; i < max_c; i++)
	{
		_client_events[i].events = POLLIN | POLLOUT;
		_client_events[i].fd = server_socket->get_sock();
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
					new_client();
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
	size_t readBytes = recv(cli->getFdClient(), read_buffer, 30000, 0);
	if (readBytes <= 0)
	{
		if (readBytes == 0)
			std::cout << "The client which fd is " << cli->getFdClient() << " sent an empty_req request " << std::endl;
		else
			perror("recv error");
		close(_client_events[*i].fd);
		_client_events[*i] = _client_events[_online_clients - 1];
		_online_clients--;
	}
	else
		handle_request(read_buffer, i, cli, readBytes);
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

void Server::handle_request(char *buf, int *i, Client *cli, int nci)
{
	size_t		pos;
	Request		*req;
	std::string input;
	const char	*client = NULL;

	buf[nci] = '\0';
	client_buffer += buf;
	std::cout << "Ce qu'envoie IRSSI : " << client_buffer << std::endl;
	while ((pos = client_buffer.find("\r\n")) != std::string::npos)
	{
		input = client_buffer.substr(0, pos + 1);
		client = input.c_str();
		req = new Request(client, cli);
		client = NULL;
		_treating_req(req, cli, i);
		client_buffer.erase(0, pos + 2);
	}
	client_buffer.clear();
	return ;
}

void Server::_treating_req(Request* req, Client* cli, int* i)
{
	replied = false;
	check_req_validity(&req);
	if (req->req_validity == valid_body || req->req_validity == valid_req)
		req->requestLexer(cli, this);
	if (req->req_validity == invalid_req)
		req->reply = errUnknownCommand("Unknown", req->_command);
	if (req->req_validity == invalid_body)
		req->reply = "Invalid message\n";
	if (req->req_validity == notEnough_params)
		req->reply = errNeedMoreParams(cli->getNickName(), req->_command);
	if (req->req_validity == incorrect_pwd)
		req->reply = errPasswMismatch(cli->getNickName(),cli->getNickName());
	if (req->req_validity == already_registered)
		req->reply = errAlreadyRegistered(cli->getNickName(),cli->getNickName());
	if (req->req_validity == omitted_cmd)
		req->reply = "Please enter the password or Nickname first\n";
	if (req->req_validity == invisible_man)
		req->reply = "To Invisible man, you can't send message!\n";
	// else if (req->req_validity == erroneous_nickname)
	// 	req->response = errErroneusNickname(cli, req);
	if (req->req_validity == nickname_exists)
		req->reply = errNicknameInUse(cli->getNickName(), req->entries[1]);
	if (req->req_validity == welcome_msg)
	{
		replied = false;
		req->reply = "001 " + cli->getNickName() + " :Welcome to the Internet Relay Network " + cli->setPrefix() + "\r\n";
		
	}
	if (req->req_validity == empty_req)
	{
	} /* DO nothing */
	if (replied == false && _client_events[*i].fd != req->_origin->getFdClient())
	{
		if (send(_client_events[*i].fd, req->response.c_str(), req->response.length(), 0) == -1)
			return (perror("Problem in sending from server ")); // a t on le droit ??
	}
	if (replied == false && _client_events[*i].fd == req->_origin->getFdClient())
	{
		if (req->reply != "UNDEFINED")
		{
			if (send(req->_origin->getFdClient(), req->reply.c_str(), strlen(req->reply.c_str()), 0) == -1)
				return (perror("Problem in sending from server "));
		}
	}
}

int Server::is_charset(char c)
{
	if (isalpha(c))
		return 0;
	else
		return 1;
}

void Server::check_req_validity(Request **r)
{
	Request *req = *r;
	std::vector<std::string>::iterator it;

	if (req->_raw_req.length() == 1 && (req->_raw_req[0] == '\n' || req->_raw_req[0] == '\r'))
	{
		req->req_validity = empty_req;
		return;
	}
	if (req->_raw_req[0] == ' ' || !req->_raw_req[0])
	{
		req->req_validity = invalid_req;
	}
	for (size_t i = 0; i < req->entries[0].size() - 1; i++)
	{
		if (isupper(req->entries[0][i]) == 0 && req->entries[0] != "kill")
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
	req->entries[req->entries.size() - 1] = req->removing_backslash(req->entries);
	req->_command = req->entries[0];
	it = req->entries.begin();
	req->entries.erase(it);
};

void	Server::_chan_requests(Request& req)
{
	if (req.response != "UNDEFINED")
	{
		size_t i = 0;
		req.response += "\n";
		std::vector<Client*>::iterator it;
		while (i < req.target.size())
		{
			it = req._findFd(req.target[i]->getFdClient(), this);
			if (send((*it)->getFdClient(), req.response.c_str(), req.response.length(), MSG_DONTWAIT) == -1)
					return (perror("Problem in sending from server "));
			i++;
		}
	}
	if (req.reply != "UNDEFINED")
	{
		req.reply += "\r\n";
		if (send(req._origin->getFdClient(), req.reply.c_str(), req.reply.length(), 0) == -1)
			return (perror("Problem in sending from server "));
	}
	replied = true;
}

void Server::_killing_cli(Client& cli)
{
	std::vector<Client*>::iterator ita;
	if (close(cli.getFdClient()) < 0)
		std::cout << "Socket couldn't be closed" << std::endl;
	std::vector<Channel*>::iterator it = all_chanels.begin();
	while (it != all_chanels.end())
	{
		if((*it)->isInChanList(&cli, (*it)->_users) == true)
		{
			(*it)->removeUser(&cli);
			if ((*it)->getOnlineCount() == 0)
			{
				all_chanels.erase(it);
			}	
			it++;
		}
	}
	ita = find(all_clients.begin(), all_clients.end(), &cli);
	all_clients.erase(ita);	
}