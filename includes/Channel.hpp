/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:06:37 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/29 11:11:31 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <iostream>
# include <string>
# include <algorithm>
# include <map>
# include "Colors.hpp"
# include "ServerSocket.hpp"
# include "Request.hpp"
# include "Client.hpp"

using namespace std;

class Channel
{
	public:

	/* CONSTRUCTORS */
		Channel( vector<Client>& allUsers, string channelName, Client& owner );
		Channel( vector<Client>& allUsers, string channelName, string channelKey, Client& owner );
		Channel( const Channel& rhs );
		~Channel();

	/* OPERATORS OVERLOAD */
		Channel &operator=( const Channel& rhs );
	
	/* METHODS */

		/* RIGHTS & STATUS */
		void addUser(Client &user);
		void deleteUser(Client &user);
		// void addOperator(Client &user);
		// void deleteOperator(Client &user, string message);
		void ban(Client& ope, Client& user, string message); // named KICK in RFC
		void inviteIn(Client& inviter, Client &invited);
		// void authorizeVocal(Client &user);
		// void mute(Client &user);

		/* MODES MANAGEMENT */
		void changeChanMode(Request& request, pair<string, string> command);
		void changeUserMode(Request& request, pair<string, string> command,vector<string>& target);
		int addMode(Request& request, vector<string>params);
		void modeBan(Request& request, pair<string, string> command);
		void modeLimite(Request& request, pair<string, string> command);

		/* COMMUNICATION*/
		// void sendMessageToMembers(Request &message, Client &from);

		/* CHAN INFO CHECKERS */
		bool isMember(Client &user);
		bool isOperator(string &user);
		bool isBanned(Client &user);
		bool canTalk(Client &user);

		/* CHAN MODE CHECKER */
		bool activeMode(char mode);
		void initModes();
		/* COMMAND MANAGER */
		// void treatAndReturn(Request &request);
		
	private:

		char							_prefix;
		int								_onlineUsers;
		int								_maxUsers;
		string						_name;
		string						_key;
		string						_topic;
		vector<string>		_users;
		vector<string>		_operators; // separated from users or duplicated ?
		vector<string>		_vocal;
		vector<string>		_banned;
		vector<Client>&			_allUsers;
		map<char, bool>			_mods; //a définir

};

#endif
