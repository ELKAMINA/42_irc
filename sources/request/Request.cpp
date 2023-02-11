#include "Request.hpp"

Request::Request(char* buffer, Client* cli) : _origin(cli)
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
	char * token = strtok(buffer, " ");
	while( token != NULL ) {
		entries.push_back(token);
		std::cout << "token " << token << std::endl;
		token = strtok(NULL, " ");
	}
	std::string new_token;
	size_t pos = 0;
	for(size_t i = 0; i < entries.size(); i++)
	{
		// std::cout << " AVANT " <<  "entriiies i " << entries[i] << std::endl;
		while((pos = entries[i].find(',')) != std::string::npos)
		{
		// std::cout << " APRES " << "entriiies i " << entries[i] << std::endl;

			new_token = entries[i].substr(0, pos);
			// std::cout << "new_token " << new_token << std::endl; //chan1
			entries[i].erase(0, pos + 1);
			std::vector<std::string>::iterator it = entries.begin();
			entries.insert(it + i, new_token);
			// std::cout << "apres insertion i = " << i << entries[i] << entries.size() << std::endl; //chan1
			i++;
		}
	}
	std::vector<std::string>::iterator it = entries.begin();
	while (it != entries.end())
	{
		// std::cout << "entriiies i " << *it << std::endl;
		it++;
	}
	req_validity = valid_req;
	_cmd_types = UNKNOWN;
	reply = "UNDEFINED";
	jo_nb_chan = 0;
	jo_nb_keys = 0;
	message = "";
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
	this->eph.clear();
	this->target.clear();
	this->_request_cmds.clear();
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
	_request_cmds.push_back(&Request::_oper);
}

void Request::requestLexer(Client* cli, Server* serv)
{
	string cmds[] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN",
					"PART", "KICK", "TOPIC", "MODE", "AWAY", "LIST", "OPER"};
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

