/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Marvin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:40 by jcervoni          #+#    #+#             */
/*   Updated: 2023/03/05 23:10:09 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARVIN_HPP
# define MARVIN_HPP

# include "Request.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include <string>
# include <ctime>
# include <fstream>
# include <cstdlib>

using namespace std;
class Request;
class Server;


class Marvin
{
public:
	typedef void	(Marvin::*cmd)(Request&, Server*);

	Marvin();
	~Marvin();

	void	introduce(Request& request, Server* serv);
	void	giveQuote(Request& request, Server* serv);
	void	giveTime(Request& request, Server* serv);
	void	affHelp(Request& request, Server* serv);
	void	wakeServ(Request& request, Server* serv);
	void	cmd_lexer(Request& request, Server* serv);
	
private:

	void	initQuotes();

	vector<cmd>			_cmds;
	vector<string>		_cmd_name;
	vector<string>		_quotes;
};
#endif