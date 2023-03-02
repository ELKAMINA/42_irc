/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_connection_manager.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:48:12 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/04 08:18:11 by jcervoni         ###   ########.fr       */
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
				std::cerr<<"about to create a new client"<<std::endl;
				if (new_client() == -1)
					return (perror("accept"), -1);
			}
			else
			{
				for (std::vector<Client>::iterator it = all_clients.begin();it != all_clients.end(); it++){
					if (it->getFdClient() == client_events[i].fd)
					{
						read_client_req(it, i);
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

	std::cerr<<"new_client"<<std::endl;
	sock = accept(_socket,(struct sockaddr *)&clientAddr, &client_len);
	if (sock < 0)
		return -1;
	client_events[_online_clients].events = POLLIN;
	client_events[_online_clients].fd = sock;
	Client tmp = Client(sock);
	all_clients.push_back(Client(tmp));
	std::cerr<<"new client, name = "<<tmp.getName()<<std::endl;
	_online_clients++;
	return 0;
}

void Server::read_client_req(std::vector<Client>::iterator client, int i)
{
	char _buffer[1000];
	bzero(_buffer, 1000);
	int nci = recv((*client).getFdClient(), _buffer, 1000, 0);
	readBytes += nci;
	if (nci <= 0)
	{
		if (readBytes == 0)
			std::cout << client->getFdClient() << " sent an empty_req request " << std::endl;
		else
			perror("recv error");
		close(client_events[i].fd);
		client_events[i] = client_events[_online_clients - 1];
		_online_clients--;
		memset(&read_buffer, 1000, readBytes);
		readBytes = 0;
		memset(&_buffer, 1000, nci);
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
		handle_request(read_buffer, client, readBytes, i);
	}
	memset(&read_buffer, 0, readBytes);
	bzero(&_buffer,1000);
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
}

void Server::removeClient(std::vector<Client>::iterator to_remove)
{
	std::vector<std::string>::iterator it;
	std::vector<Channel>::iterator target;

	for (it = to_remove->chans.begin(); it != to_remove->chans.end(); it++)
	{
		target = find_obj(*it, all_channels);
		target->removeUser(to_remove->getName());
		if (target->getOnlineCount() == 0)
			all_channels.erase(target);
	}
	for (int i = 0; i < _online_clients; i++){
		if (client_events[i].fd == to_remove->getFdClient())
		{
			close(client_events[i].fd);
			client_events[i] = client_events[0];
			_online_clients--;
			break ;
		}
	}
	all_clients.erase(to_remove);
}
// a terminer apres chan
//
//
// void Server::close_and_remove_user(Client& cli)
// {
// 	std::vector<Client>::iterator to_kill;
// 	std::vector<Channel>::iterator it = all_channels.begin();
	
// 	if (close(cli.getFdClient()) < 0)
// 		std::cout << "Socket couldn't be closed" << std::endl;
// 	while (it != all_channels.end())
// 	{
// 		if(it->isInChanList(&cli, it->_users) == true)
// 		{
// 			it->removeUser(&cli);
// 			if (it->getOnlineCount() == 0)
// 			{
// 				all_channels.erase(it);
// 			}	
// 			it++;
// 		}
// 	}
// 	to_kill = find(all_clients.begin(), all_clients.end(), &cli);
// 	all_clients.erase(to_kill);	
// }