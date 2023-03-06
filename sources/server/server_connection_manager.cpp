/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_connection_manager.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:48:12 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 19:26:46 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::init_pollfd_struct()
{
	client_events[0].events = POLLIN | POLLOUT;
	client_events[0].fd = _socket; 
	for (int i = 0; i < _max_co; i++)
	{
		client_events[i].events = POLLIN | POLLOUT;
		client_events[i].fd = _socket;
		client_events[i].revents = POLLIN;
	}
}

int Server::manage_connections()
{
	poll(client_events, _online_clients, -1);
	for (int i = 0; i < _online_clients; i++)
	{
		if (client_events[i].revents != 0 && client_events[i].revents & POLLIN)
		{
			if (client_events[i].fd == _socket)
			{
				if (new_client() == -1)
					continue ;
			}
			else
			{
				for (std::vector<Client>::iterator it = all_clients.begin();it != all_clients.end(); it++){
					if (it->getFdClient() == client_events[i].fd)
					{
						read_client_req(it->getFdClient(), i);
						break ;
					}
				}
			}
		}
	}
	return 0;
}

int Server::new_client()
{
	struct sockaddr_in	clientAddr;
	socklen_t			client_len = sizeof(clientAddr);
	int					sock = 0;

	sock = accept(_socket,(struct sockaddr *)&clientAddr, &client_len);
	if (sock <= 0)
		return -1;
	client_events[_online_clients].events = POLLIN;
	client_events[_online_clients].fd = sock;
	Client tmp = Client(sock);
	all_clients.push_back(Client(tmp));
	_online_clients++;
	return 0;
}

void Server::read_client_req(int fd_client, int i)
{
	char _buffer[1000];
	bzero(_buffer, 1000);
	int nci = recv(fd_client, _buffer, 1000, MSG_DONTWAIT);
	readBytes += nci;
	if (nci <= 0)
	{
		if (readBytes == 0)
		{
			// close(client_events[i].fd);
			// client_events[i] = client_events[_online_clients - 1];
			// _online_clients--;
			std::vector<Client>::iterator it_cli;
			std::vector<Client>::iterator it = find_obj(fd_client, all_clients);
			std::string rep = ":" + it->setPrefix() + " QUIT :" + '\n';
			removeClient(it);
			for (it_cli = all_clients.begin(); it_cli != all_clients.end(); it_cli++){
				if (send(it_cli->getFdClient(), rep.c_str(), rep.length(), 0) == -1)
					return (perror("Problem in sending from server "));
			}
			// all_clients.erase(it);
			readBytes = 0;
		}
	}
	else
	{
		if (ctld(_buffer, readBytes) == false)
		{
			strcat(read_buffer, _buffer);
			bzero(&_buffer,1000);
			return ;
		}
		_buffer[nci] = '\0';
		strcat(read_buffer, _buffer);
		handle_request(read_buffer, fd_client, readBytes, i);
	}
	bzero(&read_buffer,1000);
	readBytes = 0;
}

int status = 0;

int Server::routine()
{
	status = 0;
	init_pollfd_struct();
	while (status != 2)
	{
		if (status == 0)
			manage_connections();
		if (status == 1)
		{
			disconnectAll();
			std::cout<<"Server is restarting\n";
			all_clients.clear();
			all_channels.clear();
			opers.clear();
			init_pollfd_struct();
			status = 0;
		}
	}
	disconnectAll();
	all_clients.clear();
	all_channels.clear();
	opers.clear();
	close(_socket);
	std::cout<< "Server is shutting down\n";
	return 0;
}

void Server::disconnectAll()
{
	for (int i = 1; i < _online_clients; i++){
		close(client_events[i].fd);
	}
	all_clients.clear();
	all_channels.clear();
	opers.clear();
	_online_clients = 1;
}

void Server::removeClient(std::vector<Client>::iterator to_remove)
{
	std::vector<std::string>::iterator it;
	std::vector<Channel>::iterator target;
	for (it = to_remove->chans.begin(); it != to_remove->chans.end(); it++)
	{
		target = find_obj(*it, all_channels);
		if (target != all_channels.end())
		{
			target->removeUser(to_remove->getName());
			if (target->getOnlineCount() == 0)
				all_channels.erase(target);
		}
	}
	for (int i = 0; i < _online_clients; i++){
		if (client_events[i].fd == to_remove->getFdClient())
		{
			close(client_events[i].fd);
			client_events[i] = client_events[_online_clients - 1];
			_online_clients--;
			break ;
		}
	}
	all_clients.erase(to_remove);

}
