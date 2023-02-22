#include "Request.hpp"

Request::Request(const char* buffer, Client* cli) : _origin(cli)
{
	initLexer();
	_raw_req = buffer;
	char * token = strtok(const_cast<char *>(buffer) , " ");
	while( token != NULL ) {
		entries.push_back(token);
		token = strtok(NULL, " ");
	}
	req_validity = valid_req;
	_cmd_types = UNKNOWN;
	reply = "UNDEFINED";
	response = "UNDEFINED";
	user_to_kick = "UNDEFINED";
	jo_nb_chan = 0;
	jo_nb_keys = 0;
	message = "";
	commas_c = true;
	commas_e = true;
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
	this->target.clear();
	this->_request_cmds.clear();
}


void Request::first_arg_for_entries(std::vector<std::string> entries)
{
	// std::cout << "ARRRRGGGGGS " << std::endl; 
	// std::vector<std::string>::iterator it = entries.begin();
	// while (it != entries.end())
	// {
	// 	std::cout << "Entriiies " << (*it) << std::endl;
	// 	it++;
	// }
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
				if (count < entry_size)
				{
					_channels.push_back(eph);
					count += eph.size();
					break ;
				}
			}
		}
	}
	// std::cout << "FIIIIIN ARRRRGGGGGS " << std::endl; 
	// std::vector<std::string>::iterator ita = _channels.begin();
	// while (ita != _channels.end())
	// {
	// 	std::cout << "Entriiies " << (*ita) << std::endl;
	// 	ita++;
	// }
}

void Request::second_arg_for_entries(std::vector<std::string> entries)
{
	// std::vector<std::string>::iterator ita = entries.begin();
	// while (ita != entries.end())
	// {
	// 	std::cout << "it " << (*ita) << std::endl;
	// 	ita++;
	// }
	std::string new_token;
	size_t sharp = 0;
	std::string eph = entries[1];
	// std::cout << "eph " << eph << " size = " << entries[1].size() << std::endl;
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
	_request_cmds.push_back(&Request::_ping);
	// _request_cmds.push_back(&Request::_notice);
}

void Request::requestLexer(Client* cli, Server* serv)
{
	string cmds[] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN",
					"PART", "KICK", "TOPIC", "MODE", "AWAY", "LIST", "NAMES", "CAP", "INVITE", "OPER", "WALLOPS", "KILL", "PING"};
	size_t i = 0;
	if (this->_command == "NOTICE")
	{
		(this->*(_request_cmds[3]))(cli, serv);		
		return ;
	}
	for (; i < _request_cmds.size(); i++){
		if (this->_command == cmds[i])
		{
				(this->*(_request_cmds[i]))(cli, serv);
				{
					// std::cout << "je rentre ici " << cmds[i] << "\n" << std::endl;
					break ;
				}
		}
	}
	if (i == _request_cmds.size())
		req_validity = invalid_req;
}

