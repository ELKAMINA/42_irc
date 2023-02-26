/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:33:03 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/26 22:17:27 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Server.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include "Server.hpp"
#include "sig.hpp"

int status = ongoing;

int main(int ac, char *av[])
{
	if (ac != 3)
		return (std::cout << "<exec> <port> <password> format expected" << std::endl, 1);
	int port = atoi(av[1]);
	std::string pass(av[2]);
	std::string name = "Our IRC";
	Server* myServ = new Server(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10, name, pass);
	std::cout << "port is " << port << ", name is " << myServ->get_name() << " and pass is " << myServ->get_pass() << std::endl;
	if (myServ->start_server() == -1)
	{
		delete (myServ);
		return 1;
	}
	signal(SIGINT, handle_sig);
	while (status != shutdown)
	{
		if (status == ongoing)
			myServ->routine();
		if (status == restart)
		{
			myServ->all_chanels.clear();
			myServ->all_clients.clear();
			myServ->opers.clear();
			status = ongoing;
		}
		else
		{
			myServ->disconnectAll();
			// close(myServ->get_socket());
			myServ->all_chanels.clear();
			myServ->all_clients.clear();
			myServ->opers.clear();
			std::cout << "Server is shuting down\n";
		}

	}
	close(myServ->server_socket->get_sock());
	delete(myServ);
	return 0;
}
