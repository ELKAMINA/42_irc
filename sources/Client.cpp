#include "Client.hpp"


Client::Client(): _clientFd(0), _nickName("UNDEFINED"), _userName("UNDEFINED"), _pass("UNDEFINED"), _host("IRC with love"), _id(){};


Client::Client(int fd): _clientFd(fd), _nickName("UNDEFINED"), _userName("UNDEFINED"), _pass("UNDEFINED"), _host("IRC with love"), _id(){};

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

std::string Client::getPwd() const
{
	return this->_pass;
}

void Client::setFdClient(int fd)
{
	_clientFd = fd;
}

void Client::setNickname(std::string name)
{
	this->_nickName = name;
}

void Client::setPwd(std::string pwd)
{
	_pass = pwd;
}

std::string Client::setPrefix()
{
	
	std::ostringstream oss;
	oss << _nickName << "!" << _nickName << "@" << _host;
	std::string var = oss.str();
	return (var);
}

Client::~Client() {};
