/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:01:27 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/18 13:57:26 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP
# include "Socket.hpp"

class ServerSocket : public Socket
{
public:

	ServerSocket(int domain, int service, int protocol, int port, u_long interface, int bg);
	ServerSocket(const ServerSocket& rhs);

	~ServerSocket();

	int connect_to_network(int sock, sockaddr_in add);
	void start_listening();
	
private:

	int 	_backlog;
	int		_listening;
};
#endif