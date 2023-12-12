/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:27 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:38:20 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

static void	msg_channel(Command &command, std::string chan, strSet target, std::string msg)
{
	strVec  args;
	User    &sender = command.getUser();

	for (strSet_it it = target.begin(); it != target.end(); it++)
	{
		User	*receiver = command.getUser((*it));
		
		args.push_back(chan);
		args.push_back(msg);
		if (!receiver)
			command.reply(401, args);    // ERR_NOSUCHNICK (401)
		else if (receiver && (*it) != sender.getNickname())
			command.replyTo(&sender, receiver, -8, args);
	}
}

void	NOTICE(Command &command)	// Parameters: <ischan>{,<ischan>} <text to be sent>
{
	strVec              args;
    std::string			trailer;
	std::string			target;
	std::string			ret = "";
	chanMap				*channels;

	args = command.getParameters();
	trailer = command.getTrailer();

	// ERR_NEEDMOREPARAMS (461)
	if (args.empty())
	{
		args.push_back(command.getUser().getNickname());
		args.push_back(command.getCommand());
        return (command.reply(461, args));
	}
	// ERR_NOTEXTTOSEND (412)
	if (args.size() == 1)
		return ;      

	target = args[0];

	// get message to send
	ret = args[1];
	if (!(trailer.empty()) && ret.empty())
	{
		args[1] = trailer;
		ret = trailer;
	}
    
	User    &client = command.getUser();
	
	//  MESSAGE TO CHANNEL      :nick_sender!~c@62.210.34.8 PRIVMSG #channel_name :msg
	if (target[0] == '#')       
	{
		channels = client.getServer()->get_channels();
		chanMap_it it = channels->find(target);
		if (it == channels->end())
			return ;
		else
			msg_channel(command, target, (*it).second->get_nicksChan(), ret);
	}
	else		// MESSAGE TO INDIVIDUAL :nick_sender!~b@62.210.34.8 PRIVMSG nick_receiver :msg
    {
        User	*receiver = command.getUser(target);
        if (receiver)
        {
            args.push_back(target);
            args.push_back(ret);
            command.replyTo(&client, receiver, -9, args);
        }
    }
}
