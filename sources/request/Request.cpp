#include "Request.hpp"

Request::Request(const char* buffer, Client* cli) : _origin(cli)
{
	/* S'il faut gerer egalement les tabluations,ce code fait tres bien l'affaire. Il recupere les mots dans une phrase */
		// std::string input = buffer;
		// std::stringstream ss(input);
		// std::string word;
		// while(ss >> word) {
		// 	entries.push_back(word);
		// }
	/* ********************************************* */
	initLexer();
	_raw_req = buffer;
	char * token = strtok(const_cast<char *>(buffer) , " ");
	while( token != NULL ) {
		entries.push_back(token);
		// std::cout << "token " << token << std::endl;
		token = strtok(NULL, " ");
	}
	req_validity = valid_req;
	_cmd_types = UNKNOWN;
	reply = "UNDEFINED";
	jo_nb_chan = 0;
	jo_nb_keys = 0;
	message = "";
	commas_c = true;
	commas_e = true;
	// _origin = cli;
}


Request::Request( const Request& x ) : _origin(x._origin)
{
	*this = x;
}


Request & Request::operator=( const Request& rhs )
{
	entries = rhs.entries;
	return *this;
};


Request::~Request()
{
	this->entries.clear();
	// this->eph.clear();
	this->target.clear();
	this->_request_cmds.clear();
}


void Request::first_arg_for_entries(std::vector<std::string> entries)
{
	std::string new_token;
	size_t sharp = 0;
	if (entries[0][0] != '\0')
	{
		size_t entry_size = entries[0].size();
		std::string eph = entries[0];
		size_t count = 0; /* Combien on a consomme de eph*/
		while (eph.size() != 0)
		{
			while ((sharp = eph.find(',')) != std::string::npos)
			{
				new_token = eph.substr(0, sharp);
				_channels.push_back(new_token);
				eph.erase(0, sharp + 1);
				count += new_token.size() + 1;
				commas_c = false;
			}
			if ((sharp = eph.find(',')) == std::string::npos)
			{
				// std::cout << " la ?????? " << std::endl;
				if (count < entry_size)
				{
					_channels.push_back(eph);
					count += eph.size();
					break ;
				}
			}
		}
	}
}

void Request::second_arg_for_entries(std::vector<std::string> entries)
{
	std::string new_token;
	size_t sharp = 0;
	std::string eph = entries[1];
	size_t entry_size = entries[1].size();
	size_t count = 0; /* Combien on a consomme de eph*/
	while (eph.size() != 0)
	{
		while ((sharp = eph.find(',')) != std::string::npos)
		{
			new_token = eph.substr(0, sharp);
			_else.push_back(new_token);
			eph.erase(0, sharp + 1);
			count += new_token.size() + 1;
			commas_e = false;
		}
		if ((sharp = eph.find(',')) == std::string::npos)
		{
			if (count < entry_size)
			{
				_else.push_back(eph);
				count += eph.size();
				break ;
			}
		}
	}
}

std::string Request::getEntries(size_t i) const 
{
	return entries[i];
}

void Request::initLexer()
{
	_request_cmds.push_back(&Request::_pass);
	_request_cmds.push_back(&Request::_nick);
	_request_cmds.push_back(&Request::_user);
	_request_cmds.push_back(&Request::_privmsg);
	_request_cmds.push_back(&Request::_notice);
	_request_cmds.push_back(&Request::_join);
	_request_cmds.push_back(&Request::_part);
	_request_cmds.push_back(&Request::_kick);
	_request_cmds.push_back(&Request::_topic);
	_request_cmds.push_back(&Request::_mode);
	_request_cmds.push_back(&Request::_away);
	_request_cmds.push_back(&Request::_list);
	_request_cmds.push_back(&Request::_names);
	_request_cmds.push_back(&Request::_cap);
	_request_cmds.push_back(&Request::_invite);
	_request_cmds.push_back(&Request::_oper);
	_request_cmds.push_back(&Request::_wallops);
	_request_cmds.push_back(&Request::_kill);
}

void Request::requestLexer(Client* cli, Server* serv)
{
	string cmds[] = {"PASS", "NICK", "USER", "PRIVMSG", "NOTICE", "JOIN",
					"PART", "KICK", "TOPIC", "MODE", "AWAY", "LIST", "NAMES", "CAP", "INVITE", "OPER", "WALLOPS", "KILL"};
	size_t i = 0;
	for (; i < _request_cmds.size(); i++){
		if (this->_command == cmds[i])
		{
			(this->*(_request_cmds[i]))(cli, serv);
			break ;
		}
	}
	if (i == _request_cmds.size())
		req_validity = invalid_req;
}

