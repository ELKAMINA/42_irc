/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_errors.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:34:39 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/31 17:50:58 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_replies.hpp"

string	errNoSuchNick(string senderNick=0, string wrongNick)
{
	string reply;
	reply = wrongNick + " 401 * :No such nick/chan\n";
	return (reply);
}

string	errNoSuchChannel(string senderNick=0, string wrongChan=0)
{
	string reply;
	reply = wrongChan + " 403 * :No such channel\n";
	return (reply);
}

string	errCannotSendToChan(string nickName=0, string channel)
{
	string reply;
	reply = "404 * " + channel + " :Cannot send to channel\n";
	return (reply);
}

string errTooManyTarget(string nickName=0, string target=0)
{
	string reply;
	reply = "407 * :Too many targets\n";
	return (reply);
}

string errUnknownCommand(string nickName=0, string command)
{
	string reply;
	reply = "421 * " + command + " :Unknown command\n";
	return (reply);
}

string errNoNicknameGiven(string nickName=0, string message=0)
{
	string reply;
	reply = "431 * :No nickname given\n";
	return (reply);
}

string	errNicknameInUse(string nickName=0, string message)
{
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

string errNotOnChannel(string nickName=0, string channel)
{
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

string errNotRegistered(string nickName=0, string message=0)
{
	string reply;
	reply = "451 * :You have not registered\n";
	return (reply);
}

string	errNeedMoreParams(string nickName=0, string command)
{
	string reply;
	reply = "461 * " + command + " :Not enough parameters\n";
	return (reply);
}

string	errAlreadyRegistered(string nickName=0, string message=0)
{
	string reply;
	reply = "462 * :You Unauthorized command (already registered)\n";
	return (reply);
}

string	errPasswMismatch(string nickName=0, string message=0)
{
	string reply;
	reply = "464 * :Password incorrect\n";
	return (reply);
}

string errChannelIsFull(string nickName=0, string channel)
{
	string reply;
	reply = channel + " 471 * :Cannot join channel (+l)\n";
	return (reply);
}

string errInviteOnlyChan(string nickName=0, string channel)
{
	string reply;
	reply = channel + " 473 * :Cannot join channel (+i)\n";
	return (reply);
}

string errBannedFromChan(string nickName=0, string channel)
{
	string reply;
	reply = channel + " 474 * :Cannot join channel (+b)\n";
	return (reply);
}

string errBadChannelKey(string nickName=0, string channel)
{
	string reply;
	reply = channel + " 475 * :Cannot join channel (+k)\n";
	return (reply);
}

string errChanPrivsNeeded(string nickName=0, string channel)
{
	string reply;
	reply = channel + " 482 * :You're not channel operator\n";
	return (reply);
}

string errUsersDontMatch(string nickName=0, string message=0)
{
	string reply;
	reply = "502 * :Cannot change mode for other users\n";
	return (reply);
}
