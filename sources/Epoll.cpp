/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:26:53 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 10:16:08 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Epoll.hpp"

Epoll::Epoll()
{
	_instance = epoll_create(1024);
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
