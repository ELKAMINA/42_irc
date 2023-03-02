/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:46:03 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 10:03:34 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <string>
#include <vector>

int wrong_nickname(std::string nickname)
{
	
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if	((isalnum(nickname[i]) == 0) && nickname[i]  != '-')
			return 1;
	}
	return (nickname.size() <= 9);
}

