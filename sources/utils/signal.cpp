/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:03:18 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/02 11:06:53 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerStatus.hpp"
#include "sig.hpp"
// #include <iostream>

void handle_sig(int sig)
{
    (void)sig;
    std::cout << "\r";
    status = 2;
}