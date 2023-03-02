/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:05:03 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 11:06:49 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cstdlib>
// #include <signal.h>
#include "Server.hpp"
#include "sig.hpp"

int main(int ac, char *av[])
{
	if (ac != 3)
		return (std::cout << "<exec> <port> <password> format expected" << std::endl, 1);
	int port = atoi(av[1]);
	std::string pass(av[2]);
	std::string name = "Our IRC";
	Server* myServ = new Server(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10, name, pass);
	std::cout << "port is " << port << ", name is " << myServ->get_name() << " and pass is " << myServ->get_pass() << std::endl;
	myServ->start_server();
	signal(SIGINT, handle_sig);
	myServ->routine();
	delete(myServ);
	return 0;
}