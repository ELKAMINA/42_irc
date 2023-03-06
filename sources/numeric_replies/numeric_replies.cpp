/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:48:06 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 19:34:26 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"

std::string	rpl_welcome(std::string user_prefix)
{
	return("Welcome to the Internet Relay Network " + user_prefix + "\n");
}

std::string	rpl_umodeis(std::string user_prefix)
{
	return(user_prefix);
}

std::string	rpl_notopic(std::string user_prefix, std::string channel)
{
	return ("331 " + user_prefix + " " + channel + " :No topic is set" + "\r\n");
}

std::string	rpl_topic(std::string user_prefix, std::string channel, std::string topic)
{
	return ("332 " + user_prefix + " #" + channel + " " + topic + "\n");
}


std::string	rpl_channelmodeis(std::string channel, std::string mode)
{ 
	return ("324 " + channel + " " + mode + '\n');
}

std::string	rpl_namereply(std::string message)
{
	return (message);
}

std::string	rpl_endofnames(std::string user_prefix, std::string channel)
{
	return ("366 " + user_prefix + " " + "#" + channel + " :End of /NAMES list");
}

std::string	rpl_inviting(std::string nickName, std::string channel) 
{
	(void)nickName;
	return (channel);
}

std::string	rpl_away(std::string nickname, std::string message) 
{
	return (nickname + " :" + message);
}

std::string	rpl_unaway(std::string nickname, std::string message) 
{
	return (nickname + " :" + message + '\n');
}

std::string	rpl_list(std::string channel, std::string topic) 
{
	return ("#" + channel + " :" + topic + '\n');
}

std::string	rpl_listend() 
{
	return(":End of list\n");
}

std::string	rpl_youreoper(std::string message) 
{
	return (message);
}