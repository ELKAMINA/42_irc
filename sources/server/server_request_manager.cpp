/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_request_manager.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:08:50 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 21:24:35 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::handle_request(char *buf, std::map<std::string, Client>::iterator client, int readBytes, int i)
{
	size_t		pos;
	std::string input;
	std::string client_buffer = "";
	std::map<std::string, Client>::iterator it;

	buf[readBytes] = '\0';
	client_buffer += buf;
	std::cout << "Ce qu'envoie IRSSI : " << client_buffer << std::endl;
	while ((pos = client_buffer.find("\r\n")) != std::string::npos)
	{
		input = client_buffer.substr(0, pos + 1);
		Request req = Request(input.c_str(), client->second.getName());
		if (treating_req(req) == 1)
		{
			close(client_events[i].fd);
			client_events[i] = client_events[_online_clients - 1];
			_online_clients--;
			it = all_clients.find(req.origin);
			all_clients.erase(it);
			break ;
		}
		client_buffer.erase(0, pos + 2);
	}
	client_buffer.clear();
	return ;
}

int Server::treating_req(Request& req)
{
	if (req.check_validity() != 1)
	{
		req.format_entries();
		return (req.requestLexer(this));
	}
	return 0;
}

void Server::chan_requests(Request& req)
{
	size_t i = 0;
	std::map<std::string, Client>::iterator it;
	std::map<std::string, Client>::iterator it_sender;

	it_sender = all_clients.find(req.origin);
	std::cerr<<"origin is "<<req.origin<<std::endl;
	std::cerr<<"sender is "<<it_sender->first<<std::endl;
	if (req.response != "UNDEFINED")
	{
		req.response += "\n";
		while (i < req.target.size())
		{
			it = all_clients.find(req.target[i]);
			if (send(it->second.getFdClient(), req.response.c_str(), req.response.length(), MSG_DONTWAIT) == -1)
			{
				std::cerr<<"ça foire dans response"<<std::endl;
				return (perror("Send"));
			}
			i++;
		}
	}
	if (req.reply != "UNDEFINED")
	{
		req.reply += "\r\n";
		if (send(it_sender->second.getFdClient(), req.reply.c_str(), req.reply.length(), 0) == -1)
		{
			std::cerr<<"ca foire dans reply"<<std::endl;
			std::cerr<<"tryin to send at "<<it_sender->second.getFdClient()<<std::endl;
			return (perror("Send"));
		}
	}
}