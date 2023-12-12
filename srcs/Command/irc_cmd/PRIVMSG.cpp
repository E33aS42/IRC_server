/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:09:08 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 13:42:38 by julpelle         ###   ########.fr       */
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
			command.replyTo(&sender, receiver, -4, args);
	}
}

void	PRIVMSG(Command &command)	// Parameters: <ischan>{,<ischan>} <text to be sent>
{
	strVec    			args;
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
		args.push_back("PRIVMSG");
		return (command.reply(461, args));       
	}
	// ERR_NOTEXTTOSEND (412)
	if (args.size() == 1)
	{
		args.clear();
		args.push_back(command.getUser().getNickname());
		return (command.reply(412, args));       
	}
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
		args.pop_back();
		args.push_back(client.getNickname());
		if (it == channels->end())
			return command.reply(403, args);		// ERR_NOSUCHCHANNEL (403)
		else
			msg_channel(command, target, (*it).second->get_nicksChan(), ret);
	}
	else		// MESSAGE TO INDIVIDUAL :nick_sender!~b@62.210.34.8 PRIVMSG nick_receiver :msg
    {
        User	*receiver = command.getUser(target);
        if (receiver)
            command.replyTo(&client, receiver, -4, args);
        else
		{
			args.clear();
			args.push_back(command.getParameters()[0]);
			args.push_back(client.getNickname());
            return command.reply(401, args);    // ERR_NOSUCHNICK (401)
		}
    }
    
		// msg_indiv(command, target, ret);  // :sender!~a@62.210.34.8 PRIVMSG receiver :hi
        // :recv!~b@127.0.0.1  PRIVMSG recv :hi

	//  MESSAGE TO CHANNEL
	// if (target[0] == '#')       
	// {
	// 	channels = client.getServer()->get_channels();
	// 	chanMap_it it = channels->find(target);
	// 	if (it != channels->end())
	// 	{
	// 		(*it).second->sendToAll(ret, client, command);
		
	// 		// ERR_CANNOTSENDTOCHAN (404)			?????
	// 	}
	// 	else
	// 		return command.reply(403, args);		// ERR_NOSUCHCHANNEL (403)
	// }
	// else											// MESSAGE TO INDIVIDUAL
	// {
		// strVec  rpl;
		// User	*usr = command.getUser(target);
		
		// if (usr)
		// {
		// 	rpl.push_back(target);
		// 	rpl.push_back(ret);
		// 	std::cout << "rpl: " << rpl[0] << " - " << rpl[1] << std::endl;
		// 	command.replyTo(&client, usr, -4, rpl);
		// }
		// else
		// 	return command.reply(401, args);    // ERR_NOSUCHNICK (401)
	// 	// RPL_AWAY (301)
	// }
}


// ERR_TOOMANYischanS (407)
// ERR_NORECIPIENT (411)
// !! ERR_NOTOPLEVEL (413)
// !! ERR_WILDTOPLEVEL (414)



/*

:nick0!~user0@62.210.34.177 PRIVMSG nick2 :hello
:nick2!~user2@62.210.34.177 PRIVMSG nick0 :hi


*/