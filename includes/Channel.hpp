/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:06:37 by jcervoni          #+#    #+#             */
/*   Updated: 2023/02/13 19:25:20 by jcervoni         ###   ########.fr       */
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
// # include "numeric_replies.hpp"

using namespace std;

class Request;
class Client;
class Server;


class Channel
{
	public:
	typedef void	(Channel::*cmds)(Request&, Server* serv);

	/* CONSTRUCTORS */
		Channel( vector<Client*>& allUsers, string channelName, Client& owner );
		Channel( vector<Client*>& allUsers, string channelName, string channelKey, Client& owner );
		Channel( const Channel& rhs );
		~Channel();

	/* OPERATORS OVERLOAD */
		Channel &operator=( const Channel& rhs );
	
	/* METHODS */

		void initModes();
		void initLexer();
		
		/* MODES MANAGEMENT */
		void changeUserMode(Request& request, pair<string, string> command,vector<Client*>& target);
		void changeChanMode(Request& request, pair<string, string> command);
		void modeLimite(Request& request, pair<string, string> command);
		int addMode(Request& request, vector<string>params);
		// void modeBan(Request& request, pair<string, string> command);

		/* COMMANDS */
		void errInCmd(Request& request, string err);
		void reply_joining(Request& request, Server* serv);
		void removeUser(Client * client);
		void cmd_lexer(Request& request, Server* serv);
		void privmsg(Request& request, Server* serv);
		void invite(Request& request, Server* serv);
		void topic(Request& request, Server* serv);
		void names(Request& request, Server* serv);
		void join(Request& request, Server* serv);
		void part(Request& request, Server* serv);
		void mode(Request& request, Server* serv);
		void kick(Request& request, Server* serv);
		
		/* CHAN INFO CHECKERS */
		bool	isInChanList(Client const *user, vector<Client*>& list);
		bool	isInServ(string const& user, vector<Client *>&users);
		Client*	found(string nickname, vector<Client*>&list);
		bool	clientAcceSs(Client& cli);
		/* CHAN MODE CHECKER */
		
		bool activeMode(char mode);


	/* ACCESSORS */
		int			getOnlineCount() const;
		string		getTopic() const;
		string		getModes() const;
		string		getName() const;
		std::string	getKey() const;
			
		vector<Client *>	_users;
	private:

		int					_onlineUsers;
		int					_maxUsers;
		char				_prefix;
		string				_topic;
		string				_name;
		string				_key;

		vector<Client *>	_operators; // separated from users or duplicated ?
		vector<Client *>	_invited;
		vector<Client *>	_vocal;
		vector<Client *>	_banned;

		vector<Client *>&	_allUsers;
		map<char, bool>		_mods;
		vector<cmds>		_cmds;

};

#endif
