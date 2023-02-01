/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:06:37 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/01 12:57:31 by jcervoni         ###   ########.fr       */
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
# include "numeric_replies.hpp"

using namespace std;

class Request;
class Client;

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


		/* MODES MANAGEMENT */
		void changeChanMode(Request& request, pair<string, string> command);
		void changeUserMode(Request& request, pair<string, string> command,vector<string>& target);
		int addMode(Request& request, vector<string>params);
		void modeBan(Request& request, pair<string, string> command);
		void modeLimite(Request& request, pair<string, string> command);

		/* COMMUNICATION*/
		// void sendMessageToMembers(Request &message, Client &from);

		/* COMMANDS */
		void cmd_lexer(Request& request);
		void join(Request& request);
		void invite(Request& request);
		
		/* CHAN INFO CHECKERS */
		bool isInChanList(string const &user, vector<string>& list);

		/* CHAN MODE CHECKER */
		bool activeMode(char mode);
		void initModes();
		/* COMMAND MANAGER */
		// void treatAndReturn(Request &request);

	/* ACCESSORS */
		string getName() const;
		string getTopic() const;
			
	private:

		char				_prefix;
		int					_onlineUsers;
		int					_maxUsers;
		string				_name;
		string				_key;
		string				_topic;
		vector<string>		_users;
		vector<string>		_operators; // separated from users or duplicated ?
		vector<string>		_vocal;
		vector<string>		_banned;
		vector<string>		_invited;
		vector<Client>&		_allUsers;
		map<char, bool>		_mods; //a définir

};

#endif
