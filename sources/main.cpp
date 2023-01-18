/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:33:03 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/17 10:18:14 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main()
{
	Server myServ;
	int ret = myServ.start_server();
	if (ret == -1)
		return (std::cout << "Error creating a socket" << std::endl, 1);
	else
		std::cout << "socket created" << std::endl;
	if (myServ.bind_port() == -1)
		return (std::cout << "Error while binding" << std::endl, 1);
	else
		std::cout << "Successfully bound" << std::endl;
	if (listen(ret, 8080) == -1)
		return (std::cout << "can't listen buddy" << std::endl, 1);
	else
		std::cout << "listening..." << std::endl;
	return 0;
}