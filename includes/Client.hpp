/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:12:48 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 19:45:59 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

// # include "Colors.hpp"
# include <vector>
# include <iostream>
# include <string>
# include <map>
# include <set>
# include "Channel.hpp"
# include "Request.hpp"
# include "numeric_replies.hpp"

class Request;
class Channel;
class Server;

enum valid_modes
{
	away = 'a',
	invisible = 'i',
	wallops = 'w',
	restricted = 'r',
	op = 'o',
	localOp = 'O',
};

class Client
{
	public:

	/* CONSTRUCTORS */
		Client();
		Client( int fd );
		Client( const Client & x );
		~Client();
		// int	_isInChan;
	
	/* OPERATOR OVERLOADS */
		Client&	operator= ( const Client & rhs );
		bool	operator==(const Client& rhs);
	
	/* ***************** */
	/* **** GETTERS **** */
	/* ***************** */
		int						getFdClient();
		std::string 			getPwd() const;
		std::string				getmode() const;
		size_t					getChanNbr() const;
		std::string 			getName() const;
		std::string 			getUserName() const;
		std::string 			getRealName() const;
		std::string				getAwayMessage() const;

	/* ***************** */
	/* **** SETTERS **** */
	/* ***************** */
		std::string				setPrefix();
		void					setFdClient(int fd);
		void					setPwd(std::string passwd);
		void					setNickname(std::string name);
		void					setUsername(std::string name);
		void					setRealname(std::string name);
		void					setMode(char mode, bool state);
		void					setAwayMessage(std::string message);

	/* METHODS */
		bool					checkMode(char mode) const;
		void					addChanToList(std::string chan);
		void					removeChanFromList(std::string chan);
		void					leaveAllChans(Server *serv);

		bool					loggedIn;
		int						callToMode;
		std::vector<std::string>		chans;

	private:

		void					_initModes();
		int						_clientFd;
		std::string				_nickName;
		std::string				_userName;
		std::string				_realName;
        std::string				_pass;
		std::string				_host;
		std::string				_away_msg;
		std::map<char, bool>	_mode;


};

#endif