#include "./testServer.hpp"
#include <cstring>

Socketing::testServer::testServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 1024, INADDR_ANY, 10)
{
	launch();
}


void	Socketing::testServer::accepter()
{
	struct sockaddr_in add = socket->get_address();
	int addrlen = sizeof(add);
	new_socket = accept(socket->get_sock(), (struct sockaddr *)&add, (socklen_t *)&addrlen);
	read(new_socket, this->buffer, 30000);
}


void	Socketing::testServer::handler()
{
	std::cout << buffer << std::endl;
}

void	Socketing::testServer::responder()
{
	char *hello = "Hello from Server";
	write(new_socket, hello, strlen(hello));
	close(new_socket);
}

void	Socketing::testServer::launch()
{
	while(true)
	{
		std::cout << "==========Waiting===========" << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "==========Done===========" << std::endl;
	}
}
