/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:33:03 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/19 16:28:51 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Server.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include "Server.hpp"


int main(int ac, char *av[])
{
	if (ac != 3)
		return (std::cout << "<exec> <port> <password> format expected" << std::endl, 1);
	int port = atoi(av[1]);
	std::string pass(av[2]);
	std::string name = "Our IRC";
	Server* myServ = new Server(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10, name, pass);
	std::cout << "port is " << port << ", name is " << myServ->get_name() << " and pass is " << myServ->get_pass() << std::endl;
	myServ->start_server(); // initalise la socket server en ecoute
	myServ->routine();

	delete(myServ);
	return 0;
}


// int timeout = 1000;
// 	int nfds = 0;

// 	/* ***** Initialising epoll and its structures ***** */

// 	bool cond = true;
// 	epfd = epoll_create(3); // On crée une instance epoll, sa valeur de retour est un fd dans le systeme.
// 	char read_buffer[30000 + 1];
// 	std::string response;
// 	response += "HTTP/1.1 200 OK\n";
// 	response += "Content-Type: text/html\r\n";
// 	response += "Content-Length: 13\n\n";
// 	response += "Hello World !\r\n\r\n";
// 	struct epoll_event ev, events[5];			  /*events is an array of the nber of events we're waiting for*/
// 	ev.events = EPOLLIN;						  /* we are waiting for input events*/
// 	ev.data.fd = get_server_socket()->get_sock(); /* we listing on new_socket on the address/port we defined */
// 	if (epfd == -1)
// 		std::cout << "Failed to create epoll shit " << std::endl;
	// epoll_ctl(epfd, EPOLL_CTL_ADD, get_server_socket()->get_sock(), &ev); /* to tell the kernel, the file descriptor we're interested in updates about */

// 	// size_t bytes_read = 0;

// 	/*  Step 1 : verifiy if new connection is available */
// 	(void)read_buffer;
// 	std::cout << "NFDS == " << nfds << std::endl;
// 	while (cond)
// 	{
// 		errno = 0;
// 		std::cout << "==========Polling ... ===========" << std::endl;
// 		int nfds = epoll_wait(epfd, events, 20, timeout); /* waiting for updates about the list of files we're interested in */
// 		if (nfds < 0)
// 		{
// 			std::cerr << "error: epoll_wait() failed";
// 			exit(1);
// 		}
// 		else if (nfds == 0)
// 			std::cout << "\r" << GREEN << " waiting for connection" << SET << std::endl;
// 		for (int j = 0; j < nfds; j++)
// 		{
// 			int server = 0;
// 			if ((server == existing_socket(events[j].data.fd)) > 0) /* if socket already exist, rerpocess the request*/
// 			{
// 				if (new_socket == accept(server, NULL, NULL))
// 				{
// 					if (errno != EWOULDBLOCK)
// 					{
// 						std::cerr << "error: accept() failed" << std::endl;
// 						exit(1);
// 					}
// 				}
// 				std::cout << "\r"
// 						  << "Client connected on server: " << events[j].data.fd << std::endl;
// 				fcntl(new_socket, F_SETFL, O_NONBLOCK); // make the socket non blocking and return EWOUDBLOCK and EAGAIN
// 				ev.data.fd = new_socket;
// 				ev.events = EPOLLIN;
// 				epoll_ctl(epfd, EPOLL_CTL_ADD, new_socket, &ev);
// 			}
// 			else if (events[j].events & EPOLLIN)
// 			{
// 				int ret = 0;

// 				// Receive the request
// 				if ((ret = recv(events[j].data.fd, &read_buffer, strlen(read_buffer), 0)) < 0)
// 				{
// 					std::cout << " je suis ici " << events[j].data.fd << std::endl;
// 					std::cerr << "error: recv() failed" << strerror(errno) << std::endl;
// 					exit(1);
// 				}
// 				else
// 				{
// 					read_buffer[ret] = '\0';
// 					std::cout << read_buffer << std::endl;
// 					ev.events = EPOLLOUT;
// 					ev.data.fd = events[j].data.fd;
// 					epoll_ctl(epfd, EPOLL_CTL_MOD, events[j].data.fd, &ev);
// 				}
// 				break;
// 			}
// 			else if (events[j].events & EPOLLOUT)
// 			{
// 				if (send(events[j].data.fd, response.c_str(), response.size(), 0) < 0)
// 				{
// 					std::cerr << "error: send() failed" << std::endl;
// 					exit(1);
// 				}
// 				ev.events = EPOLLIN;
// 				ev.data.fd = events[j].data.fd;
// 				// if not keep-alive
// 				close(events[j].data.fd);
// 				epoll_ctl(epfd, EPOLL_CTL_MOD, events[j].data.fd, &ev);
// 				break;
// 			}
// 		}

// 		// std::cout << " C'est fiiiin " << std::endl;
// 	}
// }