/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:17:56 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/10 15:34:51 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "Server.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include "Client.hpp"


std::vector<std::string>::iterator used_nickname(std::string name, std::vector<std::string>&list);

template<typename T>
typename std::vector<T>::iterator find_obj(int fd, std::vector<T>& list)
{
	typename std::vector<T>::iterator it = list.begin();
	for (; it != list.end(); it++){
		if (fd == it->getFdClient())
			return it;
	}
	return list.end();
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
bool	ctld(std::string& buf, int readBytes);
// void	all_chan_names(Request& requ, Server* serv);
// int		count_chan_nbr(std::vector<std::string> entries);


#endif