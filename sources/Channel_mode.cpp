/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:17:09 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/26 12:19:26 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void Channel::modeBan(Client& target, std::string message=0)
{

}

void Channel::modeInvite(Client& target, std::string message=0)
{
	
}

void Channel::modeKey(Client& target, std::string message=0)
{
	
}

void Channel::modeLimite(Client& target, std::string message=0)
{
	
}

void Channel::modeOper(Client& target, std::string message=0)
{
	
}

void Channel::modePrivate(Client& target, std::string message=0)
{
	
}

void Channel::modeSecret(Client& target, std::string message=0)
{
	
}

void Channel::modeVocal(Client& target, std::string message=0)
{
	
}

void Channel::addMode(Client& user, char mode, std::string key=0)
{
	char modes[] = {'b', 'i', 'k', 'l', 'o', 'p', 's', 't', 'v'};
	if (isOperator(user))
	{
		if (!activeMode(mode))
		{

		}
	}
}
