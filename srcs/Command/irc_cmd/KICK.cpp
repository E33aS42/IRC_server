/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:00 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 13:29:05 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

static void	msg_channel(Command &command, std::string chan, strSet target, std::string nick)
{
	strVec  	args;
	User    	&sender = command.getUser();

	for (strSet_it it = target.begin(); it != target.end(); it++)
	{
		User	*receiver = command.getUser((*it));
		
		args.push_back(chan);
		args.push_back(nick);
		// if (receiver && (*it) != sender.getNickname())
		command.replyTo(&sender, receiver, -6, args);
	}
}

void    	KICK(Command &command)			//   Parameters: <channel> <user> *( "," <user> ) [<comment>]
{
	strVec	args;
	Server	*serv;
	chanMap	*channels;
	User	&user = command.getUser();

	args = command.getParameters();
	if (args.size() < 2)
	{
		args.push_back(user.getNickname());
		args.push_back(command.getCommand());
		return (command.reply(461, args));	// ERR_NEEDMOREPARAMS (461) "<command> :Not enough parameters"
	}

	std::string chan = args[0];
	User		*tokick = command.getUser(args[1]);

	if (chan[0] != '#')
		return  (command.reply(479, args));	// Illegal channel name (479)
	
	serv = user.getServer();
	channels = serv->get_channels();
	chanMap_it it = channels->find(chan);
	if (it == channels->end())
		return command.reply(403, args);	// ERR_NOSUCHCHANNEL (403)

	strSet	nicks = (*it).second->get_nicksChan();
	strSet_it its = nicks.find(args[1]);
	if (its == nicks.end())
		return command.reply(441, args);	// ERR_USERNOTINCHANNEL (441)
	
	std::cout << std::endl;
		
	its = nicks.find(user.getNickname());
	if (its == nicks.end())
	{
		args.clear();
		args.push_back(chan);
		args.push_back(user.getNickname());
		return command.reply(442, args);	// ERR_NOTONCHANNEL (442)
	}
	if (!(user.getOper()))
		return command.reply(482, args);	// ERR_CHANOPRIVSNEEDED (482)
	else
	{
		(*it).second->kickUser(chan, tokick, command);
		msg_channel(command, chan, nicks, args[1]);
	}
	if (!(*it).second->get_usernb())
		command.getServer().del_chan((*it).second);

}



