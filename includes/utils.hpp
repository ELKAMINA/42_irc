/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:17:56 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 09:31:23 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "Server.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include "Client.hpp"

template<class T>
int existing_obj(std::string name, std::vector<T>&list)
{
	int pos = -1;
	for (size_t i = 0; i < list.size(); i++){
		if (name == list[i].getName())
			return (pos = i);
	}
	return pos;
}

template<class T>
int existing_obj(T elem, std::vector<T>&list)
{
	int pos = -1;
	for (size_t i = 0; i < list.size(); i++){
		if (elem == list[i])
			return (pos = i);
	}
	return pos;
}

template<typename T>
typename std::vector<T>::iterator find_obj(std::string name, std::vector<T>& list)
{
	typename std::vector<T>::iterator it = list.begin();
	for (; it != list.end(); it++){
		if (name == it->getName())
			return it;
	}
	return list.end();
}

int		wrong_nickname(std::string nickname);
bool	ctld(char* buf, int readBytes);
// void	all_chan_names(Request& requ, Server* serv);
// int		count_chan_nbr(std::vector<std::string> entries);


#endif