/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:01:35 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 11:06:40 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIG_HPP
# define SIG_HPP

# include <signal.h>
# include <string>
# include <iostream>
# include <cstdlib>
# include "Server.hpp"
# include "ServerStatus.hpp"

void handle_sig(int sig);

#endif