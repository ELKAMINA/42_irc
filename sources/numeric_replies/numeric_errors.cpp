/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_errors.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:34:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/28 09:41:41 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"

std::string	errNoSuchNick(std::string senderNick, std::string wrongNick)
{
	return ("401 " + senderNick + " " + wrongNick + " :No such nickname\n");
}

std::string	errNoSuchChannel(std::string wrongChan)
{
	return (":403 " + wrongChan + " :No such channel\n");
}

std::string	errCannotSendToChan(std::string nickName, std::string channel)
{
	return ("404 " + nickName + " #" + channel + " :Cannot send to channel\n");
}

std::string errTooManyTarget()
{
	return ("407 * :Too many targets\n");
}

std::string errUnknownCommand(std::string command)
{
	return ("421 * " + command + " :Unknown command\n");
}

std::string errNoNicknameGiven()
{
	return ("431 * :No nickname given\n");
}

std::string errErroneusNickname(std::string nickName)
{
	return (":432 " + nickName + " :Erroneous nickname\n");
}

std::string	errNicknameInUse(std::string nickName)
{
	return (":433 " + nickName + " :Nickname already in use\n");
} 

std::string errUserNotOnChannel(std::string nickName, std::string channel)
{
	return (nickName + " " + channel + " 441 * :They aren't on that channel\n");
}

std::string errNotOnChannel(std::string channel)
{
	return (channel + " 442  :You're not on that channel\n");
}

std::string errUserOnChannel(std::string nickName, std::string channel)
{
	return (nickName + " " + channel + " 443 * :is already on channel\n");
}

std::string errNotRegistered()
{
	return ("451 * :You have not registered\n");
}

std::string	errNeedMoreParams(std::string nickName, std::string command)
{
	return ("461 " + nickName + " " + command + " :Not enough parameters\n");
}

std::string	errAlreadyRegistered()
{
	return (":462 * :Unauthorized command (already registered)\n");
}

std::string	errPasswMismatch(std::string nickName)
{
	return ("464 " + nickName + " :Password incorrect\n");
}

std::string errChannelIsFull(std::string channel)
{
	return (channel + " 471 * :Cannot join channel (+l)\n");
}

std::string errInviteOnlyChan(std::string channel)
{
	return (channel + " 473 * :Cannot join channel (+i)\n");
}

std::string errBannedFromChan(std::string channel)
{
	return (channel + " 474 * :Cannot join channel (+b)\n");
}

std::string errBadChannelKey(std::string nickName, std::string channel)
{
	return ("475 " + nickName + " " + channel +  " :Cannot join channel (+k)\n");
}

std::string errChanPrivsNeeded(std::string nickName, std::string channel)
{
	return (nickName + " 482 " + channel + " :You're not channel operator\n");
}

std::string errUModeUnknownFlag()
{
	return (":501 * :Unknown MODE flag\n");
}

std::string errUsersDontMatch()
{
	return ("502 * :Cannot change mode for other users\n");
}

std::string		errNoOperHost(std::string message)
{
	return (" 491 * " + message);
}

std::string		errNoPrivileges(std::string message)
{
	return (":481 " + message);
}