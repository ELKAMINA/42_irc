#include "./Networking/Sockets/ASocketinglibc-sockets.hpp"


int main()
{
	std::cout << "Starting server .... " << std::endl;
	std::cout << "Binding Socket ...." << std::endl;
	Socketing::BindingSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
	std::cout << "Listening Socket ...." << std::endl;
	Socketing::ListeningSocket ls = Socketing::ListeningSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
	(void)ls;
	std::cout << "Success" << std::endl;

}