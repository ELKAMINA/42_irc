/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:26:24 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/09 18:24:43 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <map>
# include <vector>
# include <iostream>
# include <string>
# include <cstring>
# include "Server.hpp"
# include "Channel.hpp"
# include "Client.hpp"
# include "numeric_replies.hpp"


enum commas
{
	commas,
	non_commas,
};


class Client;
class Server;


class Request
{
	typedef int	(Request::*requ_cmds)(Server*);
	public:
		std::string						raw_input;
		std::vector<std::string>		entries;
		std::vector<std::string>		channels;
		std::vector<std::string>		params;
		std::string						command;
		std::vector<Client>::iterator	origin;
		std::string						response;
		std::string						reply;
		std::string						message;
		std::vector<std::string>		target;
		size_t							nb_chan;
		size_t							nb_keys;
		std::string						user_to_kick;

	public:
		Request		(const char* buf, std::vector<Client>::iterator cli);
		~Request	();
		Request		( const Request &x );
		Request & 	operator = ( const Request &rhs );

		/* Getters */
		std::string getEntries(size_t i) const;

		/* Methods */
		int requestLexer(Server* serv);
		void initLexer();

		/* Utils */
		void		format_entries();
		int			check_validity() const;
		void		all_chan_names(Server* serv);
		int			count_chan_nbr(std::vector<std::string> entries);

		/* Utils for commands*/
		void 		resizing_chan(std::vector<std::string> entries);
		void		counting_keys(std::vector<std::string> entries);
		std::string	removing_backslash(std::vector<std::string> entries);
		void		removing_sharp(std::vector<std::string>& entries);
		void		oneChan(Server *serv);
		void		multiChan(Server *serv);
		void		mode_for_chans(Server* serv);
		void		mode_for_clis(Server* serv);
		int			mode_validity(void);
		std::string	retrieve_cli_modes(Client& tmp);
		int			check_lists();
		int			verifications();
		int			transformations(bool oneChan, bool oneParam);
		size_t		count_params();
		void		req_get_comments(std::vector<std::string>& entries, size_t i);
		void		killing_process(std::vector<Client>::iterator to_kill, Server* serv);
		bool		split_entries(std::string entry, std::vector<std::string>&target);

		/* Server Commands */
		int		pass(Server *serv);
		int		nick(Server *serv);
		int		user(Server *serv);
		int		privmsg(Server *serv);
		int		away(Server *serv);
		int		list(Server* serv);
		int		names(Server* serv);
		int		cap(Server* serv);
		int		oper(Server* serv);
		int		kill(Server* serv);
		int		ping(Server* serv);
		int		whois(Server* serv);
		int		who(Server* serv);
		int 	quit(Server *serv);
		int		restart(Server *serv);
		int		marvin(Server* serv);

		/* Channel commands */
		int		join(Server *serv);
		int		part(Server *serv);
		int		kick(Server *serv);
		int		kickingEach(Server *serv);
		int		topic(Server *serv);
		int		mode(Server *serv);
		int		invite(Server *serv);
	private:

		std::vector<requ_cmds>	_request_cmds;

};


#endif