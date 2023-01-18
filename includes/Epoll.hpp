/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:23:17 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 10:15:50 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EPOLL_HPP
# define EPOLL_HPP

# include <sys/epoll.h>

/* 

We eventually need an Epoll class for easily manage epoll calls like wait, creat,
add, mod , epoll_ctl and manage client sockets/fds

we also need to check flags like EPOLLIN EPOLLOUT (aka read/write) EPOLLET etc
*/

class Epoll
{
public:

	Epoll();
	Epoll(const Epoll& rhs);

	~Epoll();

	Epoll& operator=(const Epoll& rhs);

	/* METHODS */

	// ajout de client/server -> EPOLL_ADD / epoll_create(int nb) ?
	// suppression de client/server si fini ?
	// wait for event -> epoll_wait()
private:

	int _instance; // structure de fd surveillés par epoll -> look further
/*
	update: l'itération sur tout les fd de l'instance est faite en interne par
	epoll_wait qui renvoie dans le tableau epoll_event *events (passé en paramètre)
	les fd qui ont subit un changement (event)
	séparer en 2 catégories (client/server) ?

	// stockage des sockets/fds //
	map permet de stocker des fd uniques et de les parcourir avec find, et les créer si besoin
	std::map<undefined, undefined>_server_Socket; -> stock les socket/fds clients pour communiquer
	std::map<undefined, undefined>_client_socket; -> stock le/les socket(s) server
*/

};
#endif