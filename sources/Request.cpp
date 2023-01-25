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
	// std::cout << "siiiize " << serv->get_pass() << std::endl;
	// std::cout << req->entries[1] << req->entries[1].size() << std::endl;
	if(req->entries.size() > 2 || req->entries.size() < 2)
	{
		req->req_validity = notEnough_params;
		return ;
	}
	else if (req->entries.size() == 2)
	{
		req->entries[1].resize(req->entries[1].size() - 1); // take off the \n
		if (req->entries[1] == serv->get_pass())
		{
			req->req_validity = valid_req; // A changer 
			return ;
		}
		else
		{
			req->req_validity = incorrect_pwd;
			return ;
		}
	}
}

void Request::_privmsg(Client *cli, Request *req, Server *serv)
{
	(void)cli;
	// std::cout << "siiiize " << serv->get_pass() << std::endl;
	// std::cout << req->entries[1] << req->entries[1].size() << std::endl;
	if(req->entries.size() < 3)
	{
		req->req_validity = notEnough_params;
		return ;
	}
	else if (req->entries.size() >= 3)
	{
		req->entries[1].resize(req->entries[1].size() - 1); // take off the \n
		if (req->entries[1] == serv->get_pass())
		{
			req->req_validity = valid_req; // A changer 
			return ;
		}
		else
		{
			req->req_validity = incorrect_pwd;
			return ;
		}
	}
}