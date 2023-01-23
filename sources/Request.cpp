#include "../includes/Request.hpp"


Request::Request(char* buffer)
{
	char * token = strtok(buffer, " ");
	// std::cout << "token " << token << std::endl;
   // loop through the string to extract all other tokens
	while( token != NULL ) {
		entries.push_back(token);
		token = strtok(NULL, " ");
	}
   
}

Request::Request( const Request& x )
{
	*this = x;
}


Request & Request::operator=( const Request& rhs )
{
	entries = rhs.entries;
	_entry_isWrong = rhs._entry_isWrong;
	return *this;
};


Request::~Request() {};