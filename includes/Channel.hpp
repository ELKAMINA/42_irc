/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:06:37 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/24 11:22:36 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <iostream>
# include <string>
# include <map>
# include "Colors.hpp"
# include "ServerSocket.hpp"
# include "Request.hpp"
# include "Client.hpp"

class Channel
{
	public:

	/* CONSTRUCTORS */
		Channel( std::vector<Client>& allUsers, std::string channelName, Client& owner );
		Channel( std::vector<Client>& allUsers, std::string channelName, std::string channelKey, Client& owner );
		Channel( const Channel& rhs );
		~Channel();

	/* OPERATORS OVERLOAD */
		Channel &operator=( const Channel& rhs );
	
	/* METHODS */

		/* RIGHTS & STATUS */
		void addUser(Client &user);
		void deleteUser(Client &user);
		void addOperator(Client &user);
		void deleteOperator(Client &user, std::string fault);
		void ban(Client& ope, Client& user, std::string fault); // named KICK in RFC
		void inviteIn(Client& inviter, Client &invited);
		void authorizeVocal(Client &user);
		void mute(Client &user);

		/* COMMUNICATION*/
		void sendMessageToMembers(Message &message, Client &from);

		/* CHAN INFO CHECKERS */
		bool isMember(Client &user);
		bool isOperator(Client &user);
		bool isBanned(Client &user);
		bool canTalk(Client &user);
		
	private:

		char							_prefix;
		int								_onlineUsers;
		std::string						_name;
		std::string						_key;
		std::string						_topic;
		std::vector<std::string>		_users;
		std::vector<std::string>		_operators; // separated from users or duplicated ?
		std::vector<std::string>		_vocal;
		std::vector<std::string>		_banned;
		std::vector<Client>&			_allUsers;
		// vector<char>					_mods; a définir

};

#endif
