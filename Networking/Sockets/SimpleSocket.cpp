#include "SimpleSocket.hpp"

Socketing::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
{
/* assigning a transport address to the socket (a port number in IP networking) =  binding an address.
an interface = for instance : if connections are made with Wi-fi and  Ethernet, the interfaces are Wi-fi and Ethernet
*/
	/* address family or domain */
	address.sin_family = domain;

	/* naming a socket =  assigning a transport address to the socket (a port number in IP networking)*/
	address.sin_port = htons(port);

	address.sin_addr.s_addr = htonl(interface); /*the interface on which the socket will run (it's the IP Adress) */

	sock = socket(domain, service, protocol); // socket system call/ creating a socket 
	test_connection(sock);

	/* Establishing network connection */
	// connection = connect_to_network(sock, address);
	/*
	- domain : communication domain in which the socket should be created.

	- service : type of service. This is selected according to the properties required by the application.

	- protocol: indicate a specific protocol to use in supporting the sockets operation.
	*/
	// test_connection(connection);
}

void Socketing::SimpleSocket::test_connection(int item_to_test)
{
	if(item_to_test < 0 )
	{
		perror("Failed to connect");
		exit(EXIT_FAILURE);
	}
	// std::cout << item_to_test << std::endl;
}

sockaddr_in Socketing::SimpleSocket::get_address()
{
	// --show-leak-kinds=allstd::cout << "HOHO " << address.sin_family << std::endl;
	return address;
}

int Socketing::SimpleSocket::get_sock()
{
	return this->sock;
}

int Socketing::SimpleSocket::get_connection()
{
	return this->connection;
}

void Socketing::SimpleSocket::set_connection(int newC)
{
	this->connection = newC;
}

