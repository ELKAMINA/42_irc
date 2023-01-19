/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:26:53 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/19 11:12:16 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Epoll.hpp"

Epoll::Epoll()
{
	_instance = epoll_create(1024);
	_events.events = EPOLLIN;
}

Epoll::Epoll(const Epoll& rhs)
{
	*this = rhs;
}

Epoll::~Epoll()
{

}

Epoll& Epoll::operator=(const Epoll& rhs)
{

}

int Epoll::wait()
{
	this->_nfds = epoll_wait(this->_instance, &(this->_events), 20, 5000);
}