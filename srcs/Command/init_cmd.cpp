/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:21:56 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:43:41 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

class User;

void	User::_initCmd(void)
{
	if ( _cmdMap.empty())
	{
		_cmdMap["JOIN"]		=	JOIN;
		_cmdMap["KICK"]		=	KICK;
		_cmdMap["MODE"]		=	MODE;
		_cmdMap["MOTD"]		=	MOTD;
		_cmdMap["NAMES"]	=	NAMES;
		_cmdMap["NICK"]		=	NICK;
		_cmdMap["NOTICE"]	=	NOTICE;
		_cmdMap["OPER"]		=	OPER;
		_cmdMap["PART"]		=	PART;
		_cmdMap["PASS"]		=	PASS;
		_cmdMap["PING"]		=	PING;
		_cmdMap["PONG"]		=	PONG;
		_cmdMap["PRIVMSG"]	=	PRIVMSG;
		_cmdMap["QUIT"]		=	QUIT;
		_cmdMap["TOPIC"]	=	TOPIC;
		_cmdMap["USER"]		=	USER;
		_cmdMap["WHOIS"]	=	WHOIS;
		
	}
}

CmdMap	User::_cmdMap;