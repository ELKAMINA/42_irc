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

std::string	errNoNicknameGiven(Client *cli, Request *req )
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "431 * " << ":No nickname given\n";
	std::string var = oss.str();
	return (var);
}

std::string	errErroneusNickname(Client *cli, Request *req )
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "432 * " << cli->getNickName() << " :Erroneous nikckname\n";
	std::string var = oss.str();
	return (var);
}

std::string	errNicknameInUse(Client *cli, Request *req )
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "433 * " << cli->getNickName() << " :Nickname is already in use\n";
	std::string var = oss.str();
	return (var);
}

std::string	errNeedMoreParams(Client *cli, Request *req )
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "461 * " << req->_command << " :Not enough parameters\n";
	std::string var = oss.str();
	return (var);
}

std::string	errAlreadyRegistered(Client *cli, Request *req )
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	(void)cli;
	(void)req; /* le temps de comprendre a quoi correspond <client>*/
	std::ostringstream oss;
	oss << "462 * " << "Unauthorized command\n";
	std::string var = oss.str();
	return (var);
}

std::string	errPasswMismatch(Client *cli, Request *req ) // Modifier "unregistered client par le vrai client user"
{
	// std::cout << "" << cli->getNickName() << req->_command << " :Not enough parameters" << std::endl;
	
	(void)cli; /* le temps de comprendre a quoi correspond <client>*/
	(void)req;
	std::ostringstream oss;
	oss << "464 * " << " :Password incorrect\n";
	std::string var = oss.str();
	return (var);
}

std::string	rpl_welcome(std::string prefix, std::string req ) // Modifier "unregistered client par le vrai client user"
{
	(void)req;
	std::ostringstream oss;
	oss << "Welcome to the Internet Relay Network " << prefix << "\n";
	std::string var = oss.str();
	return (var);
}

std::string	rpl_umodeis(std::string prefix, std::string req ) // Modifier "unregistered client par le vrai client user"
{
	(void)req;
	std::ostringstream oss;
	oss << prefix << "\n";
	std::string var = oss.str();
	return (var);
}

std::string	rpl_topic(std::string channel, std::string topic ) // Modifier "unregistered client par le vrai client user"
{
	// (void)topic;
	std::ostringstream oss;
	oss << channel << ":" << topic << "\n";
	std::string var = oss.str();
	return (var);
}

std::string	rpl_notopic(std::string channel, std::string topic ) // Modifier "unregistered client par le vrai client user"
{
	(void)topic;
	std::ostringstream oss;
	oss << channel << ":No topic is set" << "\n";
	std::string var = oss.str();
	return (var);
}

std::string	rpl_channelmodeis(std::string channel, std::string mode ) // Modifier "unregistered client par le vrai client user"
{ 
	/* <channel><mode><modeparams> */
	std::ostringstream oss;
	oss << channel << " " << mode << "\n";
	std::string var = oss.str();
	return (var);
}

std::string	rpl_namereply(std::string message, std::string op ) // Modifier "unregistered client par le vrai client user"
{
	(void)op;
	std::ostringstream oss;
	oss << message;
	std::string var = oss.str();
	return (var);
}

std::string	rpl_endofnames(std::string channel, std::string op ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : user per channels prend en compte les channels privés et secrets*/
	(void)op;
	std::ostringstream oss;
	oss << channel << " " << "End of NAMES list\n";
	std::string var = oss.str();
	return (var);
}

std::string	rpl_inviting(std::string channel, std::string nickname ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <channel> <nick>*/
	std::ostringstream oss;
	oss << channel << " " << nickname;
	std::string var = oss.str();
	return (var);
}

std::string	rpl_away(std::string nickname, std::string away ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <nick>:<away> */
	std::ostringstream oss;
	oss << nickname << " " << away;
	std::string var = oss.str();
	return (var);
}

std::string	rpl_list(std::string message, std::string op ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <channel> <#visible>:<topic> */
	(void)op;
	std::ostringstream oss;
	oss << message;
	std::string var = oss.str();
	return (var);
}

std::string	rpl_listend(std::string message , std::string op ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <channel> <#visible>:<topic> */
	(void)op;
	(void)message;
	std::ostringstream oss;
	oss << "End of list\n";
	std::string var = oss.str();
	return (var);
}