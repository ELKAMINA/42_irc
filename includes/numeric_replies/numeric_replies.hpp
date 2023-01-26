/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:33:19 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/23 17:58:43 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "Request.hpp"
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


#endif