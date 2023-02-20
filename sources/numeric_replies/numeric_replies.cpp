/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:48:06 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/08 13:17:08 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"

// all prints on std streams will be replaced by a message object which will
// be sent to client

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
	oss << prefix;
	std::string var = oss.str();
	return (var);
}

std::string	rpl_notopic(Request& req, std::string channel, std::string topic ) // Modifier "unregistered client par le vrai client user"
{
	(void)topic;
	std::string message = "331 " + req._origin->setPrefix() + " " + channel + " :No topic is set" + "\r\n";
	return (message);
}

std::string	rpl_topic(Request& req, std::string channel, std::string topic )
{
	(void)req;
	std::string message = "332 " + channel + " :" + topic + "\r\n";
	return (message);
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

std::string	rpl_endofnames(Request& req, std::string channel, std::string op ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : user per channels prend en compte les channels privés et secrets*/
	(void)op;
	string reply;
	reply = "366 " + req._origin->setPrefix() + " " + "#" + channel + " :End of /NAMES list";
	return (reply);
}

std::string	rpl_inviting(std::string nickName, std::string channel) // Modifier "unregistered client par le vrai client user"
{
	string reply;
	reply = "#" + channel + " " + nickName + '\n';
	return (reply);
}

std::string	rpl_away(std::string nickname, std::string message ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <nick>:<away> */
	string reply;
	reply = nickname + " :" + message + '\n';
	return (reply);
}

std::string	rpl_unaway(std::string nickname, std::string message ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <nick>:<away> */
	string reply;
	reply = nickname + " :" + message + '\n';
	return (reply);
}

std::string	rpl_list(std::string channel, std::string topic ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <channel> <#visible>:<topic> */
	string reply;
	reply = "#" + channel + " :" + topic + '\n';
	return (reply);
}

std::string	rpl_listend(std::string message , std::string op ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <channel> <#visible>:<topic> */
	(void)op;
	(void)message;
	string reply;
	reply = ":End of list\n";
	return (reply);
}

std::string	rpl_youreoper(std::string message , std::string op ) // Modifier "unregistered client par le vrai client user"
{
	/* Résultat attendu : <channel> <#visible>:<topic> */
	(void)op;
	// (void)message;
	return (message);
}