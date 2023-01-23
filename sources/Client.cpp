#include "Client.hpp"


Client::Client(): _clientFd(0), _nickName(), _userName(), _pass(), _host("IRC with love"), _id(){};


Client::Client(int fd): _clientFd(fd), _nickName(), _userName(), _pass(), _host("IRC with love"), _id(){};

Client::Client( const Client& x ): _host(x._host) { *this = x; };


Client & Client::operator=( const Client& rhs )
{
	if (this != &rhs)
	{
		this->_clientFd = rhs._clientFd;
		this->_nickName = rhs._nickName;
		this->_userName = rhs._userName;
		this->_pass = rhs._pass;
		this->_id = rhs._id;
	}
	return *this;
};

int Client::getFdClient()
{
	return _clientFd;
}

std::string Client::getNickName() const
{
	return this->_nickName;
}

std::string Client::getUserName() const
{
	return this->_userName;
}

void Client::setFdClient(int fd)
{
	_clientFd = fd;
}

Client::~Client() {};
