/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:48:06 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/30 11:54:59 by jcervoni         ###   ########.fr       */
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

std::string	errNoNicknameGiven(Client *cli, Request *req)
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "431 * " << ":No nickname given\n";
	std::string var = oss.str();
	return (var);
}

std::string	errErroneusNickname(Client *cli, Request *req)
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "432 * " << cli->getNickName() << " :Erroneous nikckname\n";
	std::string var = oss.str();
	return (var);
}

std::string	errNicknameInUse(Client *cli, Request *req)
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "433 * " << cli->getNickName() << " :Nickname is already in use\n";
	std::string var = oss.str();
	return (var);
}

std::string	errNeedMoreParams(Client *cli, Request *req)
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "461 * " << req->_command << " :Not enough parameters\n";
	std::string var = oss.str();
	return (var);
}

std::string	errAlreadyRegistered(Client *cli, Request *req)
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "462 * " << "Unauthorized command\n";
	std::string var = oss.str();
	return (var);
}

std::string	errPasswMismatch(Client *cli, Request *req) // Modifier "unregistered client par le vrai client user"
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	
	(void)cli; /* le temps de comprendre a quoi correspond <client>*/
	(void)req;
	std::ostringstream oss;
	oss << "464 * " << " :Password incorrect\n";
	std::string var = oss.str();
	return (var);
}