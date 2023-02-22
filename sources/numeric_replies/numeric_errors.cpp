/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_errors.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:34:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/16 14:47:48 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"

string	errNoSuchNick(string senderNick, string wrongNick)
{
	(void)senderNick;
	string reply;
	reply = "401 " + senderNick + " " + wrongNick + " :No such nickname\n";
	return (reply);
}

string	errNoSuchChannel(string senderNick, string wrongChan)
{
	(void)senderNick;
	string reply;
	reply = "#" + wrongChan + " 403 * :No such channel\n";
	return (reply);
}

string	errCannotSendToChan(string nickName, string channel)
{
	(void)nickName;
	string reply;
	reply = "404 " + nickName + " #" + channel + " :Cannot send to channel\n";
	return (reply);
}

string errTooManyTarget(string nickName, string target)
{
	(void)nickName;
	(void)target;
	string reply;
	reply = "407 * :Too many targets\n";
	return (reply);
}

string errUnknownCommand(string nickName, string command)
{
	(void)nickName;
	(void)command;
	string reply;
	// reply = "zboub\n";
	reply = "421 * " + command + " :Unknown command\n";
	return (reply);
}

string errNoNicknameGiven(string nickName, string message)
{
	(void)nickName;
	(void)message;
	string reply;
	reply = "431 * :No nickname given\n";
	return (reply);
}

string	errNicknameInUse(string nickName, string message)
{
	(void)nickName;
	string reply;
	reply = message + " 433 * :Nickname is already in use\n";
	return (reply);
} 

string errUserNotOnChannel(string nickName, string channel)
{
	string reply;
	reply = nickName + " " + channel + " 441 * :They aren't on that channel\n";
	return (reply);
}

string errNotOnChannel(string nickName, string channel)
{
	(void)nickName;
	string reply;
	reply = channel + " 442 * :You're not on that channel\n";
	return (reply);
}

string errUserOnChannel(string nickName, string channel)
{
	string reply;
	reply = nickName + " " + channel + " 443 * :is already on channel\n";
	return (reply);
}

string errNotRegistered(string nickName, string message)
{
	(void)nickName;
	(void)message;
	string reply;
	reply = "451 * :You have not registered\n";
	return (reply);
}

string	errNeedMoreParams(string nickName, string command)
{
	(void)nickName;
	string reply;
	reply = "461 " + nickName + " " + command + " :Not enough parameters\n";
	return (reply);
}

string	errAlreadyRegistered(string nickName, string message)
{
	(void)nickName;
	(void)message;
	string reply;
	reply = "462 * :You Unauthorized command (already registered)\n";
	return (reply);
}

string	errPasswMismatch(string nickName, string message)
{
	(void)nickName;
	(void)message;
	string reply;
	reply = "464 " + nickName + ":Password incorrect\n";
	return (reply);
}

string errChannelIsFull(string nickName, string channel)
{
	(void)nickName;
	string reply;
	reply = channel + " 471 * :Cannot join channel (+l)\n";
	return (reply);
}

string errInviteOnlyChan(string nickName, string channel)
{
	(void)nickName;
	string reply;
	reply = channel + " 473 * :Cannot join channel (+i)\n";
	return (reply);
}

string errBannedFromChan(string nickName, string channel)
{
	(void)nickName;
	string reply;
	reply = channel + " 474 * :Cannot join channel (+b)\n";
	return (reply);
}

string errBadChannelKey(string nickName, string channel)
{
	string reply;
	reply = "475 " + nickName + " " + channel +  " :Cannot join channel (+k)\n";
	return (reply);
}

string errChanPrivsNeeded(string nickName, string channel)
{
	// (void)nickName;
	string reply;
	reply = nickName + " 482 " + channel + " :You're not channel operator\n";
	return (reply);
}

string errUModeUnknownFlag(string nickName, string channel)
{
	(void)nickName;
	(void)channel;
	string reply;
	reply = "501 * :Unknown MODE flag";
	return (reply);
}

string errUsersDontMatch(string nickName, string message)
{
	(void)nickName;
	(void)message;
	string reply;
	reply = "502 * :Cannot change mode for other users\n";
	return (reply);
}

string		errNoOperHost(string message, string me)
{
	(void)me;
	string reply;
	reply =  " 491 * " + message;
	return (reply);
}

string		errNoPrivileges(string message, string me)
{
	(void)me;
	string reply;
	reply =  "481 " + message;
	return (reply);
}