#include "SimpleServer.hpp"

Socketing::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklog)
{
	this->socket = new Socketing::ListeningSocket(domain, service, protocol, port, interface, bcklog); /* */
	
}

ListeningSocket Socketing::SimpleServer::*get_server_socket()
{
	return socket;
}
