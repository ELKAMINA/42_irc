/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:33:19 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/01 11:57:57 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# include "Client.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include <sstream>

using namespace std;
class Client;
class Request;
 
std::string         rpl_welcome(std::string str, std::string req = 0);
std::string         rpl_umodeis(std::string str, std::string req = 0);
std::string         rpl_topic(std::string channel, std::string topic);
std::string         rpl_notopic(std::string channel, std::string topic=0);
std::string         rpl_channelmodeis(std::string channel, std::string mode);
std::string         rpl_namereply(std::string message, std::string option=0);
std::string         rpl_endofnames(std::string message, std::string option=0);
std::string         rpl_inviting(std::string channel, std::string nickname=0);
std::string         rpl_away(std::string channel, std::string away=0);
std::string         rpl_list(std::string message, std::string away=0);
std::string	        rpl_listend(std::string message = 0, std::string op = 0);

// string	            errNoSuchNick(string nickName=0, string message=0);
// string	            errNoSuchChannel(string senderNick=0, string message=0);
// string	            errCannotSendToChan(string nickName=0, string channel);
// string				errTooManyTarget(string nickName=0, string target=0);
// string				errUnknownCommand(string nickName=0, string command);
// string				errNoNicknameGiven(string nickName=0, string message=0);
// string				errNicknameInUse(string nickName=0, string message);
// string				errUserNotOnChannel(string nickName, string channel);
// string				errNotOnChannel(string nickName=0, string channel);
// string				errUserOnChannel(string nickName, string channel);
// string				errNotRegistered(string nickName=0, string message=0);
// string				errNeedMoreParams(string nickName=0, string command);
// string				errAlreadyRegistered(string nickName=0, string message=0);
// string				errPasswMismatch(string nickName=0, string message=0);
// string				errChannelIsFull(string nickName=0, string channel);
// string				errInviteOnlyChan(string nickName=0, string channel);
// string				errBannedFromChan(string nickName=0, string channel);
// string				errBadChannelKey(string nickName=0, string channel);
// string				errChanPrivsNeeded(string nickName=0, string channel);
// string				errUsersDontMatch(string nickName=0, string message=0);

#endif