/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:31:13 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/08 11:16:29 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <iostream>
# include <string>
# include <algorithm>
# include <map>
// # include "Colors.hpp"
# include "Request.hpp"
# include "Client.hpp"
# include "utils.hpp"
# include "numeric_replies.hpp"
# include "utils.hpp"

using namespace std;

class Request;
class Client;
class Server;


class Channel
{
	public:
	typedef void	(Channel::*cmds)(Request&, Server* serv);

	/* CONSTRUCTORS */
		Channel(string channelName, string owner );
		Channel(string channelName, string channelKey, string owner );
		Channel( const Channel& rhs );
		~Channel();

	/* OPERATORS OVERLOAD */
		Channel &operator=( const Channel& rhs );
		bool	operator==(const Channel &rhs);
	
	/* METHODS */

		void initModes();
		void initLexer();
		
		/* MODES MANAGEMENT */
		void	changeUserMode(Request& request, pair<string, string> command, vector<string>& target, Server* serv);
		void	changeChanMode(Request& request, pair<string, string> command, Server *serv);
		void	modeLimite(Request& request, pair<string, string> command, Server* serv);
		void	modeKey(Request& request, pair<string, string> command, Server* serv);
		void	modeBan(Request& request, pair<string, string> command, Server* serv);
		int		addMode(Request& request, vector<string>params, Server* serv);

		/* COMMANDS */
		void updateUser(std::string current, std::string new_name);
		void replyJoining(Request& request, Server* serv);
		void ban(Request& request, Server* serv);
		void privmsg(Request& request, Server* serv);
		void invite(Request& request, Server* serv);
		void topic(Request& request, Server* serv);
		void names(Request& request, Server* serv);
		void join(Request& request, Server* serv);
		void part(Request& request, Server* serv);
		void mode(Request& request, Server* serv);
		void kick(Request& request, Server* serv);
		void removeUser(string user);
		
		/* CHAN INFO CHECKERS */
		std::vector<Client>::iterator	find_user(string target, vector<Client>& list);
		std::vector<string>::iterator existing_user(vector<string>& list, string name);
		bool	isInChanList(string user, vector<string>& list);
		
		bool	clientAccess(Client& cli);
		bool	activeMode(char mode);
		


	/* ACCESSORS */
		int			getOnlineCount() const;
		string		getTopic() const;
		string		getModes() const;
		string		getName() const;
		std::string	getKey() const;
			
		vector<string>	users;
	private:

		int					_onlineUsers;
		int					_maxUsers;
		char				_prefix;
		string				_topic;
		string				_name;
		string				_key;

		vector<string>		_operators;
		vector<string>		_invited;
		vector<string>		_vocal;
		vector<string>		_banned;
		map<char, bool>		_mods;
		vector<cmds>		_cmds;

};

#endif