/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:09:16 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 11:50:04 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

static void	msg_channel(Command &command, strSet target, strVec args, int code)
{
	User    	&sender = command.getUser();

	for (strSet_it it = target.begin(); it != target.end(); it++)
	{
		User	*receiver = command.getUser((*it));
		
		if (receiver && (*it) != sender.getNickname())
		  command.replyTo(&sender, receiver, code, args);
	}
}

void	QUIT(Command &command)	//  Parameters: [<reason>]
{
    strVec      args;
    std::string reason = "";
	Server	*serv;
    
    if (!(command.getTrailer().empty()))
		reason = command.getTrailer();
    
    args.push_back(reason);
    command.reply(-11, args);

    std::string quit_msg;

    quit_msg = "ERROR : Closing link " + command.getUser().getHostname() + "\r\n";
    send(command.getUser().getFd(), const_cast<char*>(quit_msg.c_str()), quit_msg.size(), 0);
    command.getUser().setBoolQuit(true);

    User	&user = command.getUser();
	  serv = user.getServer();	
	  strSet	nicks = serv->get_users_nick();
    msg_channel(command, nicks, args, -11);
}

// send to all:          :qwe!~a@62.210.34.248 QUIT :
