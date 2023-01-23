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

void	errAlreadyInUse(std::string serverName, std::string nickName);
void	errNoSuchNick(std::string nickName);
void	errNoSuchChannel(std::string channelName);
void	errCannotSendToChan(std::string channelName);

#endif