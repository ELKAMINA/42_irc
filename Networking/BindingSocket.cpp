#include "BindingSocket.hpp"

Socketing::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) : SimpleSocket(domain, service, protocol, port, interface);

{
/* assigning a transport address to the socket (a port number in IP networking) =  binding an address.
an interface = for instance : if connections are made with Wi-fi and  Ethernet, the interfaces are Wi-fi and Ethernet
*/
	set_connection(connect_to_network(get_sock(), get_address()));

	test_connection(get_connection());
}











int Socketing::BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{

	return bind(sock, (struct sockaddr *)&address, sizeof(address));

	/* For BIND function : 

		> The first parameter, socket, is the socket that was created with the socket system call.
	
		> For the second parameter, the structure sockaddr.
	
	*/
}
