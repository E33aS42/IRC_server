/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:07:50 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 13:48:06 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <typeinfo>
# include "ircCommands.hpp"

static void	msg_channel(Command &command, std::string chan, strSet target)
{
	strVec  args;
	User    &sender = command.getUser();

	for (strSet_it it = target.begin(); it != target.end(); it++)
	{
		User	*receiver = command.getUser((*it));
		
		args.push_back(chan);
		// if (receiver && (*it) != sender.getNickname())
		command.replyTo(&sender, receiver, -2, args);
	}
}

void    	JOIN(Command &command)			//   Parameters: <channel>{,<channel>} [<key>{,<key>}]
{
	strVec	args;
	Server	*serv;
	chanMap	*channels;
	User	&user = command.getUser();
	size_t	startchan = 0;
    size_t 	endchan = 0;

	args = command.getParameters();
	if (args.empty())
	{
		args.push_back(user.getNickname());
		args.push_back(command.getCommand());
		return (command.reply(461, args));	// ERR_NEEDMOREPARAMS (461) "<command> :Not enough parameters"
	}

	std::string chan = args[0];
    while (endchan < args[0].size())
    {
        startchan = endchan;
        endchan = args[0].find(',', startchan);
        chan = args[0].substr(startchan, endchan - startchan);
        if (endchan < args[0].size())
            endchan++;
		if (chan[0] != '#')
		{
			command.reply(479, args); 		// :kinetic.oftc.net 479 nickname bad_chan_name :Illegal channel name;
			continue;
		}
		
		serv = user.getServer();
		channels = serv->get_channels();

		if (channels->empty() || channels->find(chan) == channels->end())
		{
			if (command.getServer().isServFull())
			{
				args.clear();
				args.push_back(chan);
				command.reply(405, args);	// ERR_TOOMANYCHANNELS (405)
				continue;
			}	
			Channel*	newChan = new Channel(chan, command.getUser().getServer());
			serv->add_chan(newChan);
			serv->addChan(chan);
		}

		std::pair<const std::string, Channel *> &mypair = *channels->find(chan);
		if (mypair.second->isChanFull())
		{
			command.reply(471, args);		// ERR_CHANNELISFULL (471)
			continue;
		}

		// check if user is already in chan, if yes continue ;
		chanMap			chans = user.getChannels();
		if (!(chans.empty()) && chans.find(chan) != chans.end())
		{
			// std::cout << "chan found" << std::endl;
			continue;
		}
	
		// add user to chan
		mypair.second->addUser(&(command.getUser()), command);
		mypair.second->addNick(user.getNickname());
		strSet	nicks = mypair.second->get_nicksChan();

		// send info join message to channels members
		msg_channel(command, chan, nicks);

		strVec	args3;
		args3.push_back(user.getNickname());
		args3.push_back(chan);
		for (strSet_it it = nicks.begin(); it != nicks.end(); it++)	
			args3.push_back(*it);
		command.reply(353, args3);					// RPL_NAMREPLY (353)

		strVec	args4;
		args4.push_back(user.getNickname());
		args4.push_back(chan);
		command.reply(366, args4);					// RPL_ENDOFNAMES (366)
	}
}

