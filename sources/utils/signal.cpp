/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:03:18 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/06 18:48:51 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerStatus.hpp"
#include "sig.hpp"

void handle_sig(int sig)
{
    (void)sig;
    std::cout << "\r";
    status = 2;
}