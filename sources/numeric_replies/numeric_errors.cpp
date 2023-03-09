/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_errors.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:34:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/09 12:53:23 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"

std::string	errNoSuchNick(std::string senderNick, std::string wrongNick)
{
	return ("401 " + senderNick + " " + wrongNick + " :No such nickname");
}

std::string	errNoSuchChannel(std::string wrongChan)
{
	return (":403 " + wrongChan + " :No such channel");
}

std::string	errCannotSendToChan(std::string nickName, std::string channel)
{
	return ("404 " + nickName + " #" + channel + " :Cannot send to channel");
}

std::string errTooManyTarget()
{
	return (":407 * :Too many targets");
}

std::string errUnknownCommand(std::string command)
{
	return (":421 * " + command + " :Unknown command");
}

std::string errNoNicknameGiven()
{
	return (":431 * :No nickname given");
}

std::string errErroneusNickname(std::string nickName)
{
	return (":432 " + nickName + " :Erroneous nickname");
}

std::string	errNicknameInUse(std::string nickName)
{
	return ("433 NICK :" + nickName);
} 

std::string errUserNotOnChannel(std::string nickName, std::string channel)
{
	return (nickName + " #" + channel + " 441 * :They aren't on that channel");
}

std::string errNotOnChannel(std::string channel)
{
	return ("442 #" + channel + " :You're not on that channel");
}

std::string errUserOnChannel(std::string nickName, std::string channel)
{
	return ("443 " + nickName + " #" + channel + " :is already on channel");
}

std::string errNotRegistered()
{
	return (":451 * :You have not registered");
}

std::string	errNeedMoreParams(std::string nickName, std::string command)
{
	return (":461 " + nickName + " " + command + " :Not enough parameters");
}

std::string	errAlreadyRegistered()
{
	return ("462 :Unauthorized command (already registered)");
}

std::string	errPasswMismatch(std::string nickName)
{
	return (":464 " + nickName + " :Password incorrect");
}

std::string errChannelIsFull(std::string channel)
{
	return (channel);
}

std::string errInviteOnlyChan(std::string channel)
{
	return (channel);
}

std::string errBannedFromChan(std::string channel)
{
	return (":474 #" + channel + " :Cannot join channel (+b)");
}

std::string errBadChannelKey(std::string nickName, std::string channel)
{
	return (":475 " + nickName + " #" + channel +  " :Cannot join channel (+k)");
}

std::string errChanPrivsNeeded(std::string nickName, std::string channel)
{
	(void)nickName;
	return ("482 #" + channel + " :You're not channel operator");
}

std::string errUModeUnknownFlag()
{
	return (":501 * :Unknown MODE flag");
}

std::string errUsersDontMatch()
{
	return (":502 * :Cannot change mode for other users");
}

std::string		errNoOperHost(std::string message)
{
	return (":491 * " + message);
}

std::string		errNoPrivileges(std::string message)
{
	return (":481 " + message);
}