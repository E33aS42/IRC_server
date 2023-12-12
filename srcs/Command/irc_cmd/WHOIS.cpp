/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHOIS.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:09:34 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:49:45 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

void	WHOIS(Command &command)	//  Parameters: [<target>] <nick>
{
	strVec	args;
	User	&user = command.getUser();

	args = command.getParameters();
	if (args.empty())
	{
		args.push_back(user.getNickname());
		args.push_back(command.getCommand());
		return (command.reply(461, args));	// ERR_NEEDMOREPARAMS (461) "<command> :Not enough parameters"
	}

	std::string	nick = args[0];
	
	/* check if nickname exists */
	if (!(command.getUser(nick)))
	{
		args.push_back(user.getNickname());
		return command.reply(401, args);			// ERR_NOSUCHNICK (433)
	}

	// std::string nick, std::string username, std::string hostname, std::string realname
	std::string	username = user.getUsername();
	std::string	hostname = user.getHostname();
	std::string	realname = user.getRealname();

	args.push_back(username);
	args.push_back(hostname);
	args.push_back(realname);

	user.message_reply(user.getFd(), user.getNickname(), CODE_RPL_WHOISUSER + std::string(" ") + RPL_WHOISUSER(args));

	chanMap			chans = user.getChannels();
	if (!(chans.empty()))							// RPL_WHOISCHANNELS (319)
	{
		strVec	args2;
		
		args2.push_back(user.getNickname());
		
		for (chanMap_it it = chans.begin(); it != chans.end(); it++)
			args2.push_back((*it).first);
		command.reply(319, args2);
	}
	
	command.reply(318, args);						// RPL_ENDOFWHOIS (318)
		
	
}
