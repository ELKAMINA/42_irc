#include "../includes/Client.hpp"


Client::Client(): _clientfd(0), _Nick(), _User(), _Pass(), _Host("IRC with love"), _id(){};


Client::Client(int fd): _clientfd(fd), _Nick(), _User(), _Pass(), _Host("IRC with love"), _id(){};

Client::Client( const Client& x ): _Host(x._Host) { *this = x; };


Client & Client::operator=( const Client& rhs )
{
	if (this == &rhs)
		return (*this);
	this->_clientfd = rhs._clientfd;

	return (*this);
};

int Client::getFdClient()
{
	return _clientfd;
}

void Client::setFdClient(int fd)
{
	_clientfd = fd;
}

Client::~Client() {};
