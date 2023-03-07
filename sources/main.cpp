/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:05:03 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/07 11:25:35 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cstdlib>
#include "Server.hpp"
#include "sig.hpp"

int main(int ac, char *av[])
{
	if (ac != 3)
		return (std::cout << "<ircserv> <port> <password> format expected" << std::endl, 1);
	int port = atoi(av[1]);
	if (port < 1024 || port > 65536)
		return (std::cout << "\033[1;31mwrong port\033[m" << std::endl, 1);
	std::string pass(av[2]);
	std::string name = "Our IRC";
	Server* myServ = new Server(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 42, name, pass);
	if (myServ->start_server() == -1)
	{
		delete(myServ);
		return 1;
	}
	signal(SIGINT, handle_sig);
	myServ->routine();
	delete(myServ);
	return 0;
}