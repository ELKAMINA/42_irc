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
	char * token = strtok(buffer, " ");
	while( token != NULL ) {
		entries.push_back(token);
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
	msg = "";
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
		// std::cout << "Nick " << (*it).first->getNickName() <<  "dest " << dest << std::endl;
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
		cli->setMode(mde, true); /* true ajouté par amina*/
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
				// std::cout << "ici 2" << std::endl;
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
			Channel *tmp = existing_chan(entries[0], serv);
			if (!tmp)
			{
				reply = errNoSuchChannel(cli->getNickName(), "No such Channel");
				serv->_test = true;
			}
			else
			{
				if (msg == "")
				{
					msg.clear();
					size_t i = jo_nb_chan;
					while(i < entries.size())
					{
						msg += entries[i];
						msg += ' ';
						i++;
					}
				}
				tmp->cmd_lexer(*this);
			}
			serv->_chan_requests(cli, this, tmp);
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
	// entries = finding_comas(entries[1], serv);
	// std::cout << "new entries " << entries[0] << std::endl;
	beginning_with_diez(entries);
	std::vector<std::string>::iterator it = entries.end() - 1;
	it->erase(it->length() - 1, 1); //Removing the \n from the last index
	// std::cout << "Nb of channels " << jo_nb_chan << std::endl;
	if (jo_nb_chan != 0)
	{
		size_t k = jo_nb_chan;
		size_t i = 0;
		// std::vector<std::string>::iterator it = entries.begin();
		while (i < k)
		{
			entries[i].erase(0,1); // removing the character '#'

			i++;
		}
	}
	if (entries.size() > jo_nb_chan)
		jo_nb_keys = entries.size() - jo_nb_chan;
	if (jo_nb_chan > 1)
		multiChan(cli, serv);
	if ((jo_nb_chan == 1 && jo_nb_keys == 0 ) || (jo_nb_chan == 1 && jo_nb_keys == 1))
	{
		// std::cout << "one chan is OK " << std::endl;
		oneChan(cli, serv);
	}
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
	Channel *tmp;
	tmp = existing_chan(entries[0], serv);
	this->status = ongoing;
	if(jo_nb_keys > jo_nb_chan)
		reply = "BIIIIIIG ERROR";
	// std::cout << "keyyyyy " << entries[0] << entries[0].size() << std::endl;
	if (tmp != NULL) /* Channel existe */
	{
		// std::cout << "entries 0 " << entries[0] <<  " oneChan tmp = " << tmp->getName() << std::endl;
		if (tmp->getKey() != "" && entries.size() == 1)
		{
			reply = "PWWDD needed\n";/* A CHANNNNNGER */
			serv->_test = true;
		}
		else if (tmp->getKey() == "" && entries.size() > 1)
		{
			reply = "PWWDD NOT needed\n"; /* A CHANNNNNGER */
			serv->_test = true;
		}
		else if( entries.size() > jo_nb_chan)
		{
			std::string pass_to_verify = (entries[1]);
			if (pass_to_verify == tmp->getKey())
			{
				status = ongoing;
				tmp->cmd_lexer(*this);
			}
			else
			{
				reply = errPasswMismatch("Wrong Pwd for the Channel", "Wrong WRONG");
				serv->_test = true;
			}
		}
		else
		{
			status = ongoing;
			tmp->cmd_lexer(*this);
		}
		serv->_chan_requests(cli, this, tmp);
	}
	else
	{
		// std::cout << "je rentre ici " << tmp << std::endl;
		Channel *to_add = new Channel((serv->_all_clients), entries[0], *cli);
		if (entries.size() > jo_nb_chan) /* cela veut dire quil ya des mdp pr les chans*/
			to_add->setKey(entries[1]);
		// std::cout << "je rentre ici " << to_add->getKey() << std::endl;
		serv->_all_chanels.push_back(to_add);
		to_add->cmd_lexer(*this);
		serv->_chan_requests(cli, this, to_add);
	}	 
}

void Request::multiChan(Client* cli,Server *serv)
{
	(void)serv;
	(void)cli;
	Channel* tmp;
	// entries[0].erase(0, 1); // RÉCUPÉRATION UNIQUEMENT DU NOM DU CHANEL
	// std::vector<std::string>::iterator it = entries.begin();
	// std::cout << "MULTICHAN => " << "nb of keys " << jo_nb_keys << " && " << " Nb of chan " << jo_nb_chan << std::endl;
	if(jo_nb_keys > jo_nb_chan)
	{
		reply = "BIIIIIIG ERROR";
		serv->_test = false;
		return ;
	}
	size_t i = 0;
	size_t k = jo_nb_chan;
	while (i < k)
	{
		// (*it).erase(0,1);/* Taking off the # */
		// std::cout << "multichan = entries i => " << entries[i] << std::endl;
		tmp = existing_chan(entries[i], serv);
		// std::cout << "chan name " << tmp << std::endl;
		if (tmp == NULL)
		{
			Channel *to_add;
				// to_add->cmd_lexer(*this);
			if (jo_nb_keys != 0) /* cela veut dire quil ya des mdp pr les chans*/
			{
				// std::cout << "mdp " << (entries[i + jo_nb_chan]) << std::endl;
				to_add = new Channel((serv->_all_clients), entries[i], ((entries[i + jo_nb_chan])), *cli);
				jo_nb_keys--;
				// i++;
			}
			else 
			{
				// std::cout << " pas de mdp " << std::endl;
				to_add = new Channel((serv->_all_clients), entries[i], *cli);
			}
			serv->_all_chanels.push_back(to_add);
			status =  ongoing;
			to_add->cmd_lexer(*this);
			serv->_chan_requests(cli, this, to_add);
			// std::cout << "jarrive a la fin " << (*(serv->_all_chanels.begin() + i))->getName() << std::endl;
		}
		else
		{
			if (tmp->getKey() != "")
			{
				if (jo_nb_keys != 0)
				{
					std::string pass_to_verify = (entries[i + jo_nb_chan]);
					if (pass_to_verify == tmp->getKey())
					{
						jo_nb_keys--;
						status = ongoing;
						tmp->cmd_lexer(*this);
					}
					else
					{
						reply = errPasswMismatch("Wrong Pwd for the Channel", "Wrong WRONG");
						serv->_test = true;
					}
				}
				else
				{
					reply = "Key is needed \n";
					serv->_test = true;
				}
			}
			else if (tmp->getKey() == "")
			{
				// std::cout << "WALAAAAAAAH " << std::endl;
				if (jo_nb_keys != 0)
				{
					reply = "NO key is needed man for this channel";
					serv->_test = true;					
				}
				status = ongoing;
				tmp->cmd_lexer(*this);
			}
			serv->_chan_requests(cli, this, tmp);
			this->target.clear();
		}
		i++;
	}
	
}

int Request::beginning_with_diez(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.begin();
	while (it != entries.end())
	{
		if ((*it)[0] != '#' && (*it)[0] != '&')
			return 0;
		it++;
		jo_nb_chan++; /* Counting nb of diez in the req to check it with the nb of keys*/
	}
	return 1;
}

void Request::counting_keys(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.begin() + (jo_nb_chan - 1);
	while (it != entries.end())
	{
		it++;
		jo_nb_keys++; /* Counting nb of diez in the req to check it with the nb of keys*/
	}
	return ;
}

void Request::resizing_chan(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.begin();
	while (it != entries.end())
	{
		(*it).erase(0,1);
		// std::cout << " Channelllsss " << *it << std::endl;
		it++;
	}
}

void Request::removing_backslash(std::vector<std::string> entries)
{
	std::vector<std::string>::iterator it = entries.end() - 1;
	it->erase(it->length() - 1,1);
	// std::cout << "it " << (*it) << (*it).size() << std::endl;
}

int	Request::_part(Client *cli, Server *serv)
{
	if (entries.size() == 0)
	{
		req_validity = notEnough_params;
		return 1;
	}
	beginning_with_diez(entries);
	if (entries.size() > jo_nb_chan)
	{
		jo_nb_keys = entries.size() - jo_nb_chan;
		if (entries[jo_nb_chan][0] != ':' || (entries[jo_nb_chan][0] == ':' && (entries[jo_nb_chan][1] == ' ')))
		{
			reply = errUnknownCommand(cli->getNickName(), _command); /* on checke si larg apres les chan sil existe commence bien par : qui est le part message*/
			serv->_test = true;
		}
		else
		{
			std::vector<std::string>::iterator it = entries.end() - 1;
			it->erase(it->length() - 1, 1); //Removing the \n from the last index
			// std::cout << "Nb of channels " << jo_nb_chan << std::endl;
			if (jo_nb_chan != 0)
			{
				size_t k = jo_nb_chan;
				size_t i = 0;
				// std::vector<std::string>::iterator it = entries.begin();
				while (i < k)
				{
					entries[i].erase(0,1); // removing the character '#'
					i++;
				}
			}
			size_t i = jo_nb_chan;
			if (msg == "")
			{
				msg.clear();
				while(i < entries.size())
				{
					msg += entries[i];
					msg += ' ';
					i++;
				}
			}
		}
	}
	size_t i = 0;
	if (reply == "UNDEFINED")
	{
		// std::cout << "NUMBEEERS of chnanan " << jo_nb_chan << " msg = " << msg  << std::endl;
		while (i < jo_nb_chan)
		{
			Channel* tmp = existing_chan(entries[i], serv);
			if (!tmp)
			{
				reply = errNoSuchChannel(cli->getNickName(), "No such Channel");
				serv->_test = true;
			}
			else
			{
				status = ongoing;
				tmp->cmd_lexer(*this);
				/* recuperer la fct de MITCH pourvoir il ya cmb duser, si 0, supprimer le chan */
			}
			serv->_chan_requests(cli, this, tmp);
			i++;
		}
	}
	else
		serv->_chan_requests(cli, this, NULL);
	return 0;
}


int	Request::_kick(Client *cli, Server *serv)
{
	beginning_with_diez(entries);
	if (reply == "UNDEFINED")
	{
		size_t users_toKick = 0;
		if (entries.size() > jo_nb_chan)
		{
			std::vector<std::string>::iterator it = entries.begin() + jo_nb_chan;
			bool comment =  false;
			size_t nb = 0;
			while (it != entries.end())
			{
				if ((*it)[0] == ':')
				{
					if (isalnum((*it)[1]) == 0)
					{
						req_validity = invalid_req;
						serv->_test = false;
						return 1;
					}
					
					while (it != entries.end())
					{
						msg.clear();
						msg += *it;
						msg += ' ';
						it++;
						comment = true;
						nb++;
					}	
				}
				if (comment == false)
					it++;
			}
			users_toKick = entries.size() - jo_nb_chan - nb;
		}
		if ((jo_nb_chan == 1 && !users_toKick) || (jo_nb_chan > 1 && users_toKick != jo_nb_chan))
			reply = errNeedMoreParams(cli->getNickName(), _command);
		size_t i = 0;
		// std::cout << "NUMBEEERS of chnanan " << jo_nb_chan << " msg = " << msg  << std::endl;
		while (i < jo_nb_chan)
		{
			Channel* tmp = existing_chan(entries[i], serv);
			if (!tmp)
			{
				reply = errNoSuchChannel(cli->getNickName(), "No such Channel");
				serv->_test = true;
			}
			else
			{
				status = ongoing;
				tmp->cmd_lexer(*this);

			}
			serv->_chan_requests(cli, this, tmp);
			i++;
		}
	}
	else
		serv->_chan_requests(cli, this, NULL);
	return 0;
}

int	Request::_topic(Client *cli, Server *serv)
{
	beginning_with_diez(entries);
	if(jo_nb_chan == 1 && entries[1][0] == '#')
	{
		Channel *tmp = existing_chan(entries[1], serv);
		if (tmp)
			tmp->cmd_lexer(*this);
		else
		{
			reply = errNoSuchChannel(cli->getNickName(), "No such channel");
			serv->_test = true;
		}
		serv->_chan_requests(cli, this, tmp);
	}
	else
		req_validity = invalid_req;
	return 1;
}

int	Request::_mode(Client* cli, Server *serv)
{
	beginning_with_diez(entries);
	if(jo_nb_chan == 1 && entries[1][0] == '#' && entries.size() > 3)
	{
		Channel *tmp = existing_chan(entries[1], serv);
		if (tmp)
			tmp->cmd_lexer(*this);
		else
		{
			reply = errNoSuchChannel(cli->getNickName(), "No such channel");
			serv->_test = true;
		}
		serv->_chan_requests(cli, this, tmp);
	}
	else
		req_validity = invalid_req;
	return 1;
}
