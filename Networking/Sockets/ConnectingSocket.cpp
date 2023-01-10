#include "ASocketinglibc-sockets.hpp"

Socketing::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long interface) : SimpleSocket(domain, service, protocol, port, interface)

{
/* assigning a transport address to the socket (a port number in IP networking) =  binding an address.
an interface = for instance : if connections are made with Wi-fi and  Ethernet, the interfaces are Wi-fi and Ethernet
*/
	set_connection(connect_to_network(get_sock(), get_address()));

	test_connection(get_connection());
}

int Socketing::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in add)
{

/* The connect() function shall attempt to make a connection on a socket. The function takes the following arguments: socket / address / address_le.
If the socket has not already been bound to a local address, connect() shall bind it to an address which, unless the socket's address family is AF_UNIX, is an unused local address.*/

	return connect(sock, (struct sockaddr *)&add, sizeof(add));

}

/* Listening = where the socket will be connected to the network at a certain port and will wait for incoming connections */

