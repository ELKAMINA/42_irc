/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:33:19 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/31 17:55:14 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# include "Client.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include <sstream>

using namespace std;

string	            errNoSuchNick(string nickName=0, string message=0);
string	            errNoSuchChannel(string senderNick=0, string message=0);
string	            errCannotSendToChan(string nickName=0, string channel);
string				errTooManyTarget(string nickName=0, string target=0);
string				errUnknownCommand(string nickName=0, string command);
string				errNoNicknameGiven(string nickName=0, string message=0);
string				errNicknameInUse(string nickName=0, string message);
string				errUserNotOnChannel(string nickName, string channel);
string				errNotOnChannel(string nickName=0, string channel);
string				errUserOnChannel(string nickName, string channel);
string				errNotRegistered(string nickName=0, string message=0);
string				errNeedMoreParams(string nickName=0, string command);
string				errAlreadyRegistered(string nickName=0, string message=0);
string				errPasswMismatch(string nickName=0, string message=0);
string				errChannelIsFull(string nickName=0, string channel);
string				errInviteOnlyChan(string nickName=0, string channel);
string				errBannedFromChan(string nickName=0, string channel);
string				errBadChannelKey(string nickName=0, string channel);
string				errChanPrivsNeeded(string nickName=0, string channel);
string				errUsersDontMatch(string nickName=0, string message=0);

#endif