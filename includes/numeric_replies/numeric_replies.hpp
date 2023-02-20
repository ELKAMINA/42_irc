/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:33:19 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/05 09:55:10 by jcervoni         ###   ########.fr       */
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
 
std::string         rpl_welcome(std::string str, std::string req );
std::string         rpl_umodeis(std::string str, std::string req );
std::string         rpl_topic(Request& req, std::string channel, std::string topic);
std::string         rpl_notopic(Request& req, std::string channel, std::string topic);
std::string         rpl_channelmodeis(std::string channel, std::string mode);
std::string         rpl_namereply(std::string message, std::string option);
std::string         rpl_endofnames(Request& req, std::string message, std::string option);
std::string         rpl_inviting(std::string nickName, std::string channel);
std::string         rpl_away(std::string channel, std::string away);
std::string         rpl_unaway(std::string channel, std::string away);
std::string         rpl_list(std::string message, std::string away);
std::string	        rpl_listend(std::string message , std::string op );
std::string	        rpl_youreoper(std::string message , std::string op );

string	            errNoSuchNick(string nickName, string message);
string	            errNoSuchChannel(string senderNick, string message);
string	            errCannotSendToChan(string nickName, string channel);
string				errTooManyTarget(string nickName, string target);
string				errUnknownCommand(string nickName, string command);
string				errNoNicknameGiven(string nickName, string message);
string				errNicknameInUse(string nickName, string message);
string				errUserNotOnChannel(string nickName, string channel);
string				errNotOnChannel(string nickName, string channel);
string				errUserOnChannel(string nickName, string channel);
string				errNotRegistered(string nickName, string message);
string				errNeedMoreParams(string nickName, string command);
string				errAlreadyRegistered(string nickName, string message);
string				errPasswMismatch(string nickName, string message);
string				errChannelIsFull(string nickName, string channel);
string				errInviteOnlyChan(string nickName, string channel);
string				errBannedFromChan(string nickName, string channel);
string				errBadChannelKey(string nickName, string channel);
string				errChanPrivsNeeded(string nickName, string channel);
string				errUModeUnknownFlag(string nickName, string channel);
string				errUsersDontMatch(string nickName, string message);
string				errNoOperHost(string message, string me);
string				errNoPrivileges(string message, string me);

#endif