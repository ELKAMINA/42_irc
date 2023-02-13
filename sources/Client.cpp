#include "Client.hpp"


Client::Client(): _clientFd(0), _nickName("UNDEFINED"), _userName("UNDEFINED"), _pass("UNDEFINED"),
_host("IRC with love"), _id()
{
	initModes();
	_away_msg = "";
	// _isInChan = 0;
}


Client::Client(int fd): _clientFd(fd), _nickName("UNDEFINED"), _userName("UNDEFINED"), _pass("UNDEFINED"),
_host("IRC with love"), _id()
{
	initModes();
	// _isInChan = 0;
}

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
		this->_mode = rhs._mode;
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

std::string Client::getRealName() const
{
	return this->_realName;
}

std::string Client::getmode() const
{
	std::map<char, bool>::const_iterator it;
	std::string ret = "";
	for (it = _mode.begin(); it != _mode.end(); it++){
		if (it->second == true)
			ret += it->first;
	}
	return ret;
}

bool Client::checkMode(char mode) const
{
	map<char, bool>::const_iterator it;
	it = _mode.find(mode);
	if (it != _mode.end())
		return it->second;
	return false;
}

std::string Client::getHost() const
{
	return this->_host;
}

std::string Client::getPwd() const
{
	return this->_pass;
}

size_t Client::getChanNbr() const
{
	return this->_chans.size();
}
void Client::setFdClient(int fd)
{
	_clientFd = fd;
}

void Client::setNickname(std::string name)
{
	this->_nickName = name;
}

void Client::setUsername(std::string name)
{
	this->_userName = name;
}

void Client::setRealname(std::string name)
{
	this->_realName = name;
}

void Client::setMode(char mode, bool state)
{
	this->_mode[mode] = state;
}

void Client::setPwd(std::string pwd)
{
	_pass = pwd;
}

std::string Client::setPrefix()
{
	
	std::ostringstream oss;
	oss << _nickName << "!" << _userName << "@" << _host;
	std::string var = oss.str();
	return (var);
}

void Client::initModes()
{
	this->_mode['i'] = false;
	this->_mode['a'] = false;
	this->_mode['w'] = false;
	this->_mode['r'] = false;
	this->_mode['o'] = false;
	this->_mode['O'] = false;
}

Client::~Client()
{
	this->_mode.clear();
	this->all_req.clear();
	this->_chans.clear();
}

void Client::setAwayMessage(std::string message)
{
	this->_away_msg = message;
}


std::string Client::getAwayMessage() const
{
	return this->_away_msg;
}

void Client::addChanToList(Channel * chan)
{
	this->_chans.insert(chan);
}

void Client::removeChanFromList(Channel * chan)
{
	this->_chans.erase(chan);
}

void Client::leaveAllChans()
{
	set<Channel *>::iterator it = _chans.begin();
	for (; it != _chans.end(); it++){
		(*it)->removeUser(this);
	}
}