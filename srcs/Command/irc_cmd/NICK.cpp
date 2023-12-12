/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:00:06 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 12:58:43 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

static int	check_string(std::string s)
{
	if (!(std::isalpha(*s.begin())))
		return (1);
	for(std::string::iterator it = ++s.begin(); it != s.end(); ++it) 
	{
		if (!(std::isalpha(*it)) && !(std::isdigit(*it)) && !(check_special(*it)))
			return (1);
	}
	return (0);
}

static void	msg_channel(Command &command, std::string nick, strSet target)
{
	strVec  args;
	User    &sender = command.getUser();

	for (strSet_it it = target.begin(); it != target.end(); it++)
	{
		User	*receiver = command.getUser((*it));
		
		args.push_back(nick);
		if (receiver && (*it) != sender.getNickname())
			command.replyTo(&sender, receiver, -1, args);
	}
}

void    	NICK(Command &command)					// Parameters: <nickname>
{ 
    User 		&user = command.getUser();
	Server		*serv = user.getServer();
	strVec		args;

	/* no parameter given */
	if(command.getParameters().size() == 0 && !user.getBoolNickname())
		return command.reply(431, args);			// ERR_NONICKNAMEGIVEN (431)
		
	args = command.getParameters();
	std::string nick;
	if (command.getParameters().size() != 0)
		nick = args[0];
	else
		nick = user.getNickname();

	/* check if nickname is longer than 30 characters, if it is, truncate it */
	if (nick.size() > 30)
		nick = nick.substr(0, 30);

	/* check if nickname contains any unallowed character*/
	if ((check_string(nick)))
		return command.reply(432, args);			// ERR_ERRONEUSNICKNAME (432)

	/* check if new nickname is same as old nickname -> do nothing */
	std::string	old_nick = user.getNickname();
	if (!(old_nick.empty()) && (nick == old_nick))
		return ;

	/* check if nickname is already taken on server */
	strSet	nicks = serv->get_users_nick();
	if (nicks.find(nick) != nicks.end())		//	if (command.getUser(nick))
		return command.reply(433, args);			// ERR_NICKNAMEINUSE (433)

	strSet		serv_nicks = serv->get_users_nick();
	/* delete old nickname if there is one */
	if (!(old_nick.empty()))						
	{
		user.setOldNickname(old_nick);
		// delete old nick on server
		serv_nicks.erase(old_nick);
		serv->set_users_nick(serv_nicks);
		
		// delete old nicks on channel and replace with new nick
		chanMap		*channels = serv->get_channels();
		if (!(channels->empty()))
		{	
			strSet      chan_nicks;
			for(chanMap_it it = channels->begin(); it != channels->end(); it++)
			{
				chan_nicks = (*it).second->get_nicksChan();
				if (chan_nicks.find(old_nick) != chan_nicks.end())
				{
					chan_nicks.erase(old_nick);
					chan_nicks.insert(nick);
					(*it).second->set_nicksChan(chan_nicks);
					msg_channel(command, nick, chan_nicks);
				}
			}
		}
	}
	
	/* fill user nickname with new_nick */
	user.setNickname(nick);
	user.setBoolNickname(true);
	
	/* update nickname records */
	command.getServer().add_userNick(nick);		//update server nicks
	user.setOldNick("");
	
	/* create nick custom reply */
	if (user.getBoolAuthentification())
		command.reply(-1, args);					
}
