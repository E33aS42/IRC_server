/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:43 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 13:37:35 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

static void	msg_channel(Command &command, strSet target, strVec args, int code)
{
	User    	&sender = command.getUser();

	for (strSet_it it = target.begin(); it != target.end(); it++)
	{
		User	*receiver = command.getUser((*it));
		
		command.replyTo(&sender, receiver, code, args);
	}
}

void    	PART(Command &command)//   Parameters: <channel>{,<channel>} [<reason>]
{
    strVec      args;
    chanMap     *channels;
    chanMap     usrChan = command.getUser().getChannels();
    size_t      startchan = 0;
    size_t      endchan = 0;

    args = command.getParameters();
    if (args.size() < 1)
    {
        // std::cout << "not enough parameters !" << std::endl; // debug
        args.push_back(command.getUser().getNickname());
        args.push_back("PART");
        return (command.reply(461, args)); // ERR_NEEDMOREPARAMS (461) "<command> :Not enough parameters"
    }
    std::string chan = args[0];
    while (endchan < args[0].size())
    {
        startchan = endchan;
        endchan = args[0].find(',', startchan);
        chan = args[0].substr(startchan, endchan - startchan);
        if (endchan < args[0].size())
            endchan++;
        if (command.getServer().get_channb() ==  0 || command.getServer().get_channels()->find(chan) == command.getServer().get_channels()->end())
        {
            args.push_back(command.getUser().getNickname());
            command.reply(403, args); // ERR_NOSUCHCHANNEL (403)
            continue;
        }
        if ((usrChan.find(chan) == usrChan.end()))
        {
            args.push_back(command.getUser().getNickname());
            args.push_back(chan);
            command.reply(442, args); // ERR_NOTONCHANNEL (442)
            continue;   
        }
        User	&user = command.getUser();
        channels = user.getServer()->get_channels();
        std::pair<const std::string, Channel *> &mypair = *channels->find(chan);
        chanMap_it it = channels->find(chan);
        strSet	nicks = (*it).second->get_nicksChan();
        (*it).second->delUser(&user);

        if (args.size() > 1)
            msg_channel(command, nicks, args, -7);
        else
            msg_channel(command, nicks, args, -3);

        if (!mypair.second->get_usernb())
            command.getServer().del_chan(mypair.second);
    }
}

