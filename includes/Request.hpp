#pragma once

# include <map>
# include <vector>
# include <iostream>
# include <string>
# include <cstring>
# include "Server.hpp"
# include "Colors.hpp"
# include "Socket.hpp"
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

typedef int	(Request::*requ_cmds)(Client*, Server*);

class Request
{
	public:
		std::string					raw_input;
		std::vector<std::string>	entries;
		std::vector<std::string>	_channels;
		std::vector<std::string>	_else;
		std::string					_command;
		Client*						_origin;
		std::string					response;
		std::string					reply;
		std::string					message;
		std::vector<Client*>		target;
		size_t						jo_nb_chan;
		size_t						jo_nb_keys;
		bool						commas_c;
		bool						commas_e;
		std::string					user_to_kick;

	public:
		Request		(const char* buf, Client* cli);
		~Request	();
		Request		( const Request &x );
		Request & 	operator = ( const Request &rhs );

		/* Getters */
		std::string getEntries(size_t i) const;

		/* Methods */
		int requestLexer(Client *cli, Server* serv);
		void initLexer();

		/* Utils */
		void		format_entries();
		int			check_validity() const;

		/* Utils for commands*/
		std::vector<Client* >::iterator	_find(std::string dest, Server *serv);
		int			wrong_nickname();
		Channel*	existing_chan(std::string chan_name, Server *serv);
		int			beginning_with_diez(std::vector<string> entries);
		void 		resizing_chan(std::vector<std::string> entries);
		void		counting_keys(std::vector<std::string> entries);
		std::string	removing_backslash(std::vector<std::string> entries);
		void		removing_sharp(std::vector<std::string>& entries);
		void		oneChan(Client* cli, Server *serv);
		void		multiChan(Client* cli, Server *serv);
		void		_mode_for_chans(Client* cli, Server* serv);
		void		_mode_for_clis(Client* cli, Server* serv);
		int			mode_validity(void);
		std::string	retrieve_cliModes(Client* tmp);
		void		names_noParams(Server* serv);
		void		names_params(Server* serv);
		void		chan_names(Server* serv);
		void		noChan_names(Server* serv);
		void		first_arg_for_entries(std::vector<std::string> entries);
		void		second_arg_for_entries(std::vector<std::string> entries);
		int			_check_lists();
		int			_verifications();
		int			_transformations();
		void		req_get_comments(std::vector<std::string>& entries, size_t i);
		void		req_killing_process(Client* tmp, Server* serv);

	private:
		/* Server Commands */
		int			_pass(Client* cli, Server *serv);
		int			_nick(Client* cli, Server *serv);
		int			_user(Client* cli, Server *serv);
		int			_privmsg(Client* cli, Server *serv);
		int			_away(Client* cli, Server *serv);
		int			_list(Client* cli, Server* serv);
		int			_names(Client* cli, Server* serv);
		int			_cap(Client* cli, Server* serv);
		int			_oper(Client* cli, Server* serv);
		int			_wallops(Client* cli, Server* serv);
		int			_kill(Client* cli, Server* serv);
		int			_ping(Client* cli, Server* serv);
		int			_whois(Client* cli, Server* serv);
		int 		_quit(Client *cli, Server *serv);
		int			_restart(Client *clie, Server *serv);

		/* Channel commands */
		int			_join(Client* cli, Server *serv);
		int			_part(Client* cli, Server *serv);
		int			_kick(Client* cli, Server *serv);
		int			_kickingEach(Client* cli, Server *serv);
		int			_topic(Client* cli, Server *serv);
		int			_mode(Client* cli, Server *serv);
		int			_invite(Client* cli, Server *serv);

		vector<requ_cmds>	_request_cmds;

};
