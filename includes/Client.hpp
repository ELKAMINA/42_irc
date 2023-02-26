#pragma once

# include "Colors.hpp"
# include <vector>
# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include "Socket.hpp"
# include <map>
# include <set>
// # include "Channels.hpp"
# include "Request.hpp"
# include "./numeric_replies/numeric_replies.hpp"

class Request;
class Channel;

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
		Client & operator= ( const Client & rhs );
		int				getFdClient();
		void			setFdClient(int fd);
		std::string 	getNickName() const;
		std::string 	getUserName() const;
		std::string 	getRealName() const;
		std::string		getmode() const;
		std::string 	getPwd() const;
		std::string		getHost() const;
		size_t			getChanNbr() const;

	/* SETTERS */
		std::string			setPrefix();
		void				setPwd(std::string passwd);
		void				setNickname(std::string name);
		void				setUsername(std::string name);
		void				setRealname(std::string name);
		void				setMode(char mode, bool state);
		void				setAwayMessage(std::string message);
		std::string			getAwayMessage() const;

	/* METHODS */
		void			errInCmd(Request& request, string err);
		bool			checkMode(char mode) const;
		void			addChanToList(Channel * chan);
		void			removeChanFromList(Channel * chan);
		void			leaveAllChans();
		// void receiveMessage(Message& message);

		bool			loggedIn;
		int				callToMode;
		set<Channel *>				chans;

	private:

		void						initModes();
		int				            _clientFd;
		std::string					_nickName; //rfc: MAX 9 caracteres
		std::string					_userName;
		std::string					_realName;
        std::string					_pass;
		const std::string			_host;
		std::string					_away_msg;
		std::string					_id;
		std::map<char, bool>		_mode;
		std::map<int, Request>		all_req;



};

