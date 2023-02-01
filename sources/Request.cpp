#include "../includes/Request.hpp"


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

	_raw_req = buffer;
	// _origin = cli;
	char * token = strtok(buffer, " ");
   // loop through the string to extract all other tokens
	while( token != NULL ) {
		entries.push_back(token);
		token = strtok(NULL, " ");
	}
	req_validity = valid_req;
	_cmd_types = UNKNOWN;
	reply = "UNDEFINED";
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


Request::~Request() {};

std::string Request::getEntries(size_t i) const 
{
	return entries[i];
}

void Request::_pass(Client *cli, Server *serv)
{
	(void)cli;
	(void)serv;
	// std::cout << "siiiize " << serv->get_pass() << std::endl;
	// std::cout << entries[1] << entries[1].size() << std::endl;
	if((entries.size() + 1) > 2 || (entries.size() + 1) < 2)
	{
		req_validity = notEnough_params;
		return ;
	}
	else if(cli->getNickName() != "UNDEFINED")
	{
		req_validity = already_registered;
		return ;
	}
	else if ((entries.size() + 1) == 2)
	{
		entries[0].resize(entries[0].size() - 1); // take off the \n
		if (entries[0] == serv->get_pass())
		{
			req_validity = valid_req; // A changer 
			cli->setPwd(serv->get_pass());
			return ;
		}
		else
		{
			req_validity = incorrect_pwd;
			return ;
		}
	}
}

void Request::_nick(Client *cli, Server *serv)
{
	(void)cli;
	(void)serv;
	// std::cout << cli->getPwd() <<  cli->getUserName() << std::endl;
	// std::cout << "entry " << entries[0] << " size " << entries[0].size() << std::endl;
	entries[0].resize(entries[0].size() - 1);
	if (entries.size() > 1 || entries.size() < 1)
	{
		req_validity = notEnough_params;
		return ;	
	}
	else if (cli->getPwd() == "UNDEFINED" && cli->getUserName() == "UNDEFINED" )
	{
		req_validity = omitted_cmd;
		return ;
	}
	else if (user_existence(entries[0], serv) == 0)
	{
		req_validity = nickname_exists;
		return ;
	}
	else if (wrong_nickname() == 0)
	{
		req_validity = erroneous_nickname;
		return ;
	}
	std::cout << "hereeee " << entries[0] << entries[0].size() << std::endl;
	cli->setNickname(entries[0]);
	// _nickname_cli = entries[0];
	// std::cout << " OK c'est good " << std::endl
}

int Request::user_existence(std::string dest, Server *serv)
{
	// std::map<Client*, std::vector<Request*> >::key_compare my_comp = serv->_req_per_id.key_comp();
	std::map<Client*, std::vector<Request*> >::iterator it = serv->_req_per_id.begin();

	size_t i = 0;
	while (i < serv->_req_per_id.size())
	{
		std::cout << "Nick " << (*it).first->getNickName() <<  "dest " << dest << std::endl;
		if	((*it).first->getNickName() == dest)
		{
			return 0;
		}	
		i++;
		it++;
	}
	return 1;
}

Client* Request::find(std::string dest, Server *serv)
{
	// std::map<Client*, std::vector<Request*> >::key_compare my_comp = serv->_req_per_id.key_comp();
	std::map<Client*, std::vector<Request*> >::iterator it = serv->_req_per_id.begin();

	// size_t i = 0;
	while (it != serv->_req_per_id.end())
	{
		if	((*it).first->getNickName() == dest)
		{
			// std::cout << "dest " << (*it).first->getNickName() << std::endl;
			return it->first;
		}
		it++;
	}
	return serv->_req_per_id.end()->first; // returning the end of the tree
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

void Request::_user(Client *cli, Server *serv)
{
	(void)cli;
	(void)serv;
	// std::cout << cli->getPwd() <<  cli->getUserName() << std::endl;
	if (entries.size() < 4 || entries.size() > 4)
	{
		req_validity = notEnough_params;
		return ;	
	}
	else if (cli->getPwd() == "UNDEFINED" && cli->getNickName() == "UNDEFINED" )
	{
		req_validity = omitted_cmd;
		return ;
	}
	else
	{
		// std::cout << "hey   " << std::endl;
		entries[0].resize(entries[0].size() - 1);
		int mde = atoi(entries[1].c_str());
		cli->setUsername(entries[0]);
		cli->setMode(mde);
		if (entries[3][0])
			entries[3].resize(entries[3].size() - 1);
		cli->setRealname(entries[3]);
		req_validity = welcome_msg;
		// std::cout << " OK c'est good " << std::endl;
	}

}

int Request::_privmsg(Client *cli, Server *serv)
{
	(void)cli;
	(void)serv;
	if(entries.size() < 2)
	{
		req_validity = notEnough_params;
		return 1;
	}
	else if (entries.size() >= 2)
	{
		if	(entries[0][0] != '&' && entries[0][0] != '#')
		{
			std::vector<std::string>::iterator it = entries.begin();
			std::string dest;
			dest =  entries[0];
			std::string message;
			entries.erase(it);
			if (find(dest, serv) != serv->_req_per_id.end()->first)
			{
				std::cout << "ici 2" << std::endl;
				if (entries.size() >= 2)
				{
					size_t i = 0;
					while (i < entries.size())
					{
						message.append(entries[i]);
						message.append(" ");
						i++;
					}
				}
				std::ostringstream oss;
				oss << ":" << cli->getNickName() << "!" << cli->getNickName() << "@" << cli->getRealName() << " PRIVMSG " << dest << " " << message;
				std::string var = oss.str();
				if (send(find(dest, serv)->getFdClient(), var.c_str(), var.length(), 0) == -1)
					return (-1);
			}
			return 0;
		}
		if (entries[0][0] == '&' && entries[0][0] == '#')
		{
			std::cout << "it's a chanel thing " << std::endl;
			return 2;
		}
	}
	return 5;
}

int	Request::_join(Client *cli, Server *serv)
{
	/* Find si chanel existe ou non 
	1. s'il existe alors ajouter le client au chanel
	2. s'il nexiste pas, creer un chanel et rajouter dans la liste des chanel existants et ajouter l'utilisateur à la liste de sutilisateurs du chanel.
	*/
	(void)serv;
	(void)cli;

	if (entries.size() < 1)
		std::cout << "error " << std::endl;
	if (entries.size() > 2)
		multiChan(cli, serv);
	if (entries.size() ==  1 && (entries[0][0] == '#' || entries[0][0] == '&'))
		oneChan(cli, serv);
	return 0;
}

Channel* Request::existing_chan(std::string name, Server *serv)
{
	std::vector<Channel *>::iterator it = serv->_all_chanels.begin();
	while(it != serv->_all_chanels.end())
	{
		if ((*it)->getName() == name)
			return *it;
		it++;
	}
	return NULL;
}

void Request::oneChan(Client* cli, Server *serv)
{
	(void)serv;
	// (void)cli;
	Channel *tmp;
	if (entries.size() ==  1 && (entries[0][0] != '#' && entries[0][0] != '&'))
		reply = "NOT A CHANNEL SORRYYYYY";
	entries[0].erase(0, 1); // RÉCUPÉRATION UNIQUEMENT DU NOM DU CHANEL
	tmp = existing_chan(entries[0], serv);
	this->status = ongoing;
	if (tmp != NULL) /* Channel existe */
	{
		tmp->cmd_lexer(*this);
		serv->_chan_requests(cli, this, tmp);
	}
	else
	{
		
		// std::cout << "je rentre ici " << serv->_all_chanels.size() << std::endl;
		Channel *to_add = new Channel((serv->_all_clients), entries[0], *cli);
		serv->_all_chanels.push_back(to_add);
		to_add->cmd_lexer(*this);
		std::cout << " jojo " << std::endl;
		serv->_chan_requests(cli, this, to_add);
	}
	/* PSEUDO CODE
	
	=> Chercher dans le vecteur Channel, si entries[0] existe deja 
		Si oui, 
			=> Ajouter l'utilisateur à la lsite des utilsateurs du chan
		Si non,
			=> new Channel 
			=> Ajouter l'utilisateur à la lsite des utilsateurs du chan
			=> Ajouter le channel dans le vecteur de Channel
	*/
	 
}

void Request::multiChan(Client* cli,Server *serv)
{
	(void)serv;
	(void)cli;
	entries[0].erase(0, 1); // RÉCUPÉRATION UNIQUEMENT DU NOM DU CHANEL
	std::cout << "OK user ajouté au chan " << std::endl;
}