/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:06:37 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/27 18:49:23 by jcervoni         ###   ########.fr       */
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
		void deleteOperator(Client &user, std::string message);
		void ban(Client& ope, Client& user, std::string message); // named KICK in RFC
		void inviteIn(Client& inviter, Client &invited);
		void authorizeVocal(Client &user);
		void mute(Client &user);

		/* MODES MANAGEMENT */
		int addMode(Request& request, std::vector<std::string>params);
		void modeBan(Client& target, std::string message=0);
		void modeInvite(Client& target, std::string message=0);
		void modeKey(Client& target, std::string message=0);
		void modeLimite(Request& request, std::pair<std::string, std::string> command);
		void modeOper(Client& target, std::string message=0);
		void modePrivate(Client& target, std::string message=0);
		void modeSecret(Client& target, std::string message=0);
		void modeVocal(Client& target, std::string message=0);

		/* COMMUNICATION*/
		// void sendMessageToMembers(Request &message, Client &from);

		/* CHAN INFO CHECKERS */
		bool isMember(Client &user);
		bool isOperator(std::string &user);
		bool isBanned(Client &user);
		bool canTalk(Client &user);

		/* CHAN MODE CHECKER */
		bool activeMode(char mode);
		/* COMMAND MANAGER */
		// void treatAndReturn(Request &request);
		
	private:

		char							_prefix;
		int								_onlineUsers;
		int								_maxUsers;
		std::string						_name;
		std::string						_key;
		std::string						_topic;
		std::vector<std::string>		_users;
		std::vector<std::string>		_operators; // separated from users or duplicated ?
		std::vector<std::string>		_vocal;
		std::vector<std::string>		_banned;
		std::vector<Client>&			_allUsers;
		std::map<char, bool>			_mods; //a définir

};

#endif
