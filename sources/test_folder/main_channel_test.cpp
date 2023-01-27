/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_channel_test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:04:00 by jcervoni          #+#    #+#             */
/*   Updated: 2023/01/27 17:30:41 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cstdlib>
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

using namespace std;
int main()
{
	vector<string>test;
	string name = "testicule";
	vector<Client>clients;
	Client mitch = Client(4);
	Channel* chanTest = new Channel(clients, name, mitch);
	test.push_back("#chan1");
	test.push_back("+skl");
	// test.push_back("Mitch");
	test.push_back("lalala");
	test.push_back("20");

	chanTest->addMode(test);
}