/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:46:03 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/10 16:35:48 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <string>
#include <vector>

std::vector<std::string>::iterator used_nickname(std::string name, std::vector<std::string>&list)
{
	std::vector<std::string>::iterator it = list.begin();
	for (size_t i = 0; i < list.size(); i++){
		if (name == list[i])
			return it;
	}
	return list.end();
}

int wrong_nickname(std::string nickname)
{
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if	(((isalnum(nickname[i]) == 0) && nickname[i]  != '-' && nickname[i]  != '_') || nickname.size() > 9)
			return 1;
	}
	return (0);
}

bool ctld(std::string& buf, int readBytes)
{
	int j = 0;
	if (buf != "")
	{
		for (size_t i = 0; i < buf.size(); i++){
			if (j == readBytes)
				break;
			if (buf[j] == '\n')
				return true;
			j++;
		}
	}
	return false;
}

