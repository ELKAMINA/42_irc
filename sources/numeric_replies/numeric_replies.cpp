/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:48:06 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/23 18:00:55 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"

// all prints on std streams will be replaced by a message object which will
// be sent to client

void	errAlreadyInUse(std::string serverName, std::string nickName)
{
	std::cout << serverName << " 433 * " << nickName << " :Nickname already in use" << std::endl;
}

void	errNoSuchNick(std::string nickName)
{
	std::cout << "401 * "<< nickName << " :No such nick/chan" << std::endl;
}

void	errNoSuchChannel(std::string channelName)
{
	std::cout << "403 * " << channelName << " :No such channel" << std::endl;
}
void	errCannotSendToChan(std::string channelName)
{
	std::cout << "404 * " << channelName << " :Cannot send to channel" << std::endl;
}