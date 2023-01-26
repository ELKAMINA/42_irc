#include "../includes/Request.hpp"


Request::Request(char* buffer)
{
	/* S'il faut gerer egalement les tabluations,ce code fait tres bien l'affaire. Il recupere les mots dans une phrase */
		// std::string input = buffer;
		// std::stringstream ss(input);
		// std::string word;
		// while(ss >> word) {
		// 	entries.push_back(word);
		// }
	/* ********************************************* */

	_raw_req = buffer;
	char * token = strtok(buffer, " ");
	// std::cout << "token " << token << std::endl;
   // loop through the string to extract all other tokens
	while( token != NULL ) {
		entries.push_back(token);
		token = strtok(NULL, " ");
	}
	req_validity = valid_req;
	_cmd_types = UNKNOWN;
}

Request::Request( const Request& x )
{
	*this = x;
}


Request & Request::operator=( const Request& rhs )
{
	entries = rhs.entries;
	return *this;
};


Request::~Request() {};

std::string Request::getEntries(size_t i) const 
{
	return entries[i];
}

void Request::_pass(Client *cli, Request *req, Server *serv)
{
	(void)cli;
	(void)serv;
	// std::cout << "siiiize " << serv->get_pass() << std::endl;
	// std::cout << req->entries[1] << req->entries[1].size() << std::endl;
	if((req->entries.size() + 1) > 2 || (req->entries.size() + 1) < 2)
	{
		req->req_validity = notEnough_params;
		return ;
	}
	else if(cli->getNickName() != "UNDEFINED")
	{
		req->req_validity = already_registered;
		return ;
	}
	else if ((req->entries.size() + 1) == 2)
	{
		req->entries[0].resize(req->entries[0].size() - 1); // take off the \n
		if (req->entries[0] == serv->get_pass())
		{
			req->req_validity = valid_req; // A changer 
			cli->setPwd(serv->get_pass());
			return ;
		}
		else
		{
			req->req_validity = incorrect_pwd;
			return ;
		}
	}
}

int Request::_privmsg(Client *cli, Request *req, Server *serv)
{
	(void)cli;
	(void)serv;
	if(req->entries.size() < 3)
	{
		req->req_validity = notEnough_params;
		return 1;
	}
	else if (req->entries.size() >= 3)
	{
		if	(entries[1][0] != '&' && entries[1][0] != '#')
		{
			target.push_back(entries[1]);
			return 0;
			// msg_to_user(cli, req, serv);
		}
		else
		{
			std::cout << "it's a chanel thing " << std::endl;
			return 2;
		}
			
	}
	return 5;
}

void Request::_nick(Client *cli, Request *req, Server *serv)
{
	(void)cli;
	(void)serv;
	(void)req;
	// std::cout << cli->getPwd() <<  cli->getUserName() << std::endl;
	if (req->entries.size() > 1 || req->entries.size() < 1)
	{
		req->req_validity = notEnough_params;
		return ;	
	}
	else if (cli->getPwd() == "UNDEFINED" && cli->getUserName() == "UNDEFINED" )
	{
		req->req_validity = omitted_cmd;
		return ;
	}
	else if (user_existence(entries[1], serv) == 0)
	{
		req->req_validity = nickname_exists;
		return ;
	}
	else if (wrong_nickname() == 0)
	{
		req->req_validity = erroneous_nickname;
		return ;
	}
	else
	{
		entries[0].resize(entries[0].size() - 1);
		cli->setNickname(entries[0]);
		req->_nickname_cli = entries[0];
		// std::cout << " OK c'est good " << std::endl;
	}

}

int Request::user_existence(std::string dest, Server *serv)
{
	// std::map<Client*, std::vector<Request*> >::key_compare my_comp = serv->_req_per_id.key_comp();
	std::map<Client*, std::vector<Request*> >::iterator it = serv->_req_per_id.begin();

	size_t i = 0;
	while (i < serv->_req_per_id.size())
	{
		if	((*it).first->getNickName() == dest)
			return 0;
		i++;
	}
	return 1;
}

int Request::wrong_nickname()
{
	for (size_t i = 0; i < entries[0].size() - 1; i++)
	{
		// std::cout << " char = " << entries[0][i] << " alnum = " << isalnum(entries[0][i]) << std::endl;
		if	((isalnum(entries[0][i]) == 0 || entries[0].size() > 9) && entries[0][i]  != '-')
			return 0;
	}
	return 1;
}

void Request::_user(Client *cli, Request *req, Server *serv)
{
	(void)cli;
	(void)serv;
	(void)req;
	// std::cout << cli->getPwd() <<  cli->getUserName() << std::endl;
	if (req->entries.size() < 4 || req->entries.size() > 4)
	{
		req->req_validity = notEnough_params;
		return ;	
	}
	else if (cli->getPwd() == "UNDEFINED" && cli->getNickName() == "UNDEFINED" )
	{
		req->req_validity = omitted_cmd;
		return ;
	}
	else
	{
		std::cout << "hey   " << std::endl;
		entries[0].resize(entries[0].size() - 1);
		int mde = atoi(entries[1].c_str());
		cli->setUsername(entries[0]);
		cli->setMode(mde);
		cli->setRealname(entries[3]);
		req->req_validity = welcome_msg;
		// std::cout << " OK c'est good " << std::endl;
	}

}