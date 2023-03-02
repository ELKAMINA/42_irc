/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:08:29 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 13:29:57 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# include <string>

/* REPLIES */
std::string		rpl_welcome(std::string user_prefix);
std::string		rpl_umodeis(std::string user_prefix);
std::string		rpl_topic(std::string user_prefix, std::string channel, std::string topic);
std::string		rpl_notopic(std::string user_prefix, std::string channel);
std::string		rpl_channelmodeis(std::string channel, std::string mode);
std::string		rpl_namereply(std::string message);
std::string		rpl_endofnames(std::string user_prefix, std::string message);
std::string		rpl_inviting(std::string nickName, std::string channel);
std::string		rpl_away(std::string nickname, std::string away);
std::string		rpl_unaway(std::string nickname, std::string away);
std::string		rpl_list(std::string message, std::string topic);
std::string		rpl_listend();
std::string		rpl_youreoper(std::string message);
/* ERRORS */
std::string		errNoSuchNick(std::string nickName, std::string message);
std::string		errNoSuchChannel(std::string senderNick);
std::string		errCannotSendToChan(std::string nickName, std::string channel);
std::string		errTooManyTarget();
std::string		errUnknownCommand(std::string command);
std::string		errNoNicknameGiven();
std::string		errErroneusNickname(std::string nickName);
std::string		errNicknameInUse(std::string nickName);
std::string		errUserNotOnChannel(std::string nickName, std::string channel);
std::string		errNotOnChannel(std::string channel);
std::string		errUserOnChannel(std::string nickName, std::string channel);
std::string		errNotRegistered();
std::string		errNeedMoreParams(std::string nickName, std::string command);
std::string		errAlreadyRegistered();
std::string		errPasswMismatch(std::string nickName);
std::string		errChannelIsFull(std::string channel);
std::string		errInviteOnlyChan(std::string channel);
std::string		errBannedFromChan(std::string channel);
std::string		errBadChannelKey(std::string nickName, std::string channel);
std::string		errChanPrivsNeeded(std::string nickName, std::string channel);
std::string		errUModeUnknownFlag();
std::string		errUsersDontMatch();
std::string		errNoOperHost(std::string message);
std::string		errNoPrivileges(std::string message);

#endif