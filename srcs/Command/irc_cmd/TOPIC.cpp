/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:09:21 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 14:08:41 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

static void	msg_channel(Command &command, strVec args, strSet target)
{
	User    &sender = command.getUser();

	for (strSet_it it = target.begin(); it != target.end(); it++)
	{
		User	*receiver = command.getUser((*it));
		
		command.replyTo(&sender, receiver, -14, args);
	}
}

void	TOPIC(Command &command)	//  Parameters: <channel> [<topic>]
{
    Server	    *serv;
	chanMap	    *channels;
	User	    &user 	= command.getUser();

    strVec		args 	= command.getParameters();
	std::string topic 	= command.getTrailer();

	if (args.empty())
	{
        args.push_back(user.getNickname());
		args.push_back(command.getCommand());
		return (command.reply(461, args));	// ERR_NEEDMOREPARAMS (461) "<command> :Not enough parameters"
	}
    else
    {
		std::string chan = args[0];
		std::string nick = user.getNickname();
		strVec args2;
		args2.push_back(chan);
		args2.push_back(nick);
		serv = user.getServer();
		channels = serv->get_channels();
		chanMap_it it = channels->find(chan);
		if (it == channels->end())
			return command.reply(403, args2);	// ERR_NOSUCHCHANNEL (403)

		strSet	nicks = (*it).second->get_nicksChan();
		strSet_it its = nicks.find(nick);
		its = nicks.find(nick);
		if (its == nicks.end())
			return command.reply(442, args2);	// ERR_NOTONCHANNEL (442)
		args2.clear();
		
        if (args.size() == 1 && topic.empty()) // TOPIC <chan>
        {
            if ((*it).second->get_topic().empty())  // if no topic
			{
				args2.push_back(nick);
				args2.push_back(chan);
				return command.reply(331, args2);
			}
            else                                    // if topic
            {
                user.message_reply(user.getFd(), user.getHostname(), CODE_RPL_TOPIC + std::string (" ") + RPL_TOPIC(nick, chan, (*it).second->get_topic()));
                user.message_reply(user.getFd(), user.getHostname(), CODE_RPL_TOPICWHOTIME + std::string (" ") + RPL_TOPICWHOTIME(chan, user.getNickname()));
            }
            return ;
        }

        if (!(user.getOper()))
		    return command.reply(482, args);	// ERR_CHANOPRIVSNEEDED (482)
		
        if (args.size() >= 2 && args[1].size() > 0) // TOPIC <chan> <topic>
        {
            args2.clear();
            args2.push_back(chan);
            args2.push_back(args[1]);
            (*it).second->set_topic(args[1]);
            msg_channel(command, args2, nicks);
            return;
        }
		
		if ((args.size() == 1 || !(args[1].size())) && !(topic.empty()))
		{
            args2.clear();
            args2.push_back(chan);
            args2.push_back(topic);
            (*it).second->set_topic(topic);
            msg_channel(command, args2, nicks);
            return;
		}
    }
}
