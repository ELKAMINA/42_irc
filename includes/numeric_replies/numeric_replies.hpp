/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:33:19 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/30 11:54:49 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# include "Client.hpp"
# include "Request.hpp"
// # include "Channel.hpp"
# include <sstream>

class Client;
class Request;

void	            errAlreadyInUse(std::string serverName, std::string nickName);
void	            errNoSuchNick(std::string nickName);
void	            errNoSuchChannel(std::string channelName);
void	            errCannotSendToChan(std::string channelName);
std::string			errNeedMoreParams(Client *cli, Request *req);
std::string			errPasswMismatch(Client *cli, Request *req); // Server client need to be disconected from the server after this
std::string			errAlreadyRegistered(Client *cli, Request *req);
std::string	        errNicknameInUse(Client *cli, Request *req);
std::string	        errErroneusNickname(Client *cli, Request *req);
std::string	        errNoNicknameGiven(Client *cli, Request *req);  
std::string         rpl_welcome(std::string str, std::string req);
std::string         rpl_umodeis(std::string str, std::string req);
std::string         rpl_topic(std::string channel, std::string topic);
std::string         rpl_notopic(std::string channel, std::string topic=0);
std::string         rpl_channelmodeis(std::string channel, std::string mode);
std::string         rpl_namereply(std::string message, std::string option=0);
std::string         rpl_endofnames(std::string message, std::string option=0);
std::string         rpl_inviting(std::string channel, std::string nickname=0);
std::string         rpl_away(std::string channel, std::string away=0);
std::string         rpl_list(std::string message, std::string away=0);
std::string	        rpl_listend(std::string message = 0, std::string op = 0);







#endif