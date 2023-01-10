#include "ASocketinglibc-sockets.hpp"

Socketing::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bg) : BindingSocket(domain, service, protocol, port, interface)
/* We chose the Binding Socket class because it's the server that has to create the socket to listen */
{
	this->backlog = bg;
	start_listening();
	test_connection(listening);
}

void Socketing::ListeningSocket::start_listening()
{
	listening = listen(get_connection(), backlog);	
}

