/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:34 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 12:50:24 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// optional


# include "ircCommands.hpp"

void    	OPER(Command &command)              //   Parameters: <name> <password>
{
    strVec	args;
    strSet  users;

    User	&user = command.getUser();
	args = command.getParameters();
    users = command.getServer().get_users_nick();

	if (args.size() < 2)
	{
        if (args.size() == 0)
            args.push_back(user.getNickname());
		args.push_back(command.getCommand());
		return (command.reply(461, args));	    // ERR_NEEDMOREPARAMS (461) "<command> :Not enough parameters"
	}
    else if (users.find(args[0]) == users.end())
    {
        args.clear();
        args.push_back(user.getNickname());
        return (command.reply(491, args));      // 
    }
    else if (args[0] != user.getNickname())
    {
        args.clear();
        args.push_back(user.getNickname());
        return (command.reply(502, args));
    }
    if (PASS_OPER != clean_string(args[1]))     // ERR_PASSWDMISMATCH (464)
    {
        args.push_back(user.getNickname());
        return (command.reply(464, args));
    }
    args.push_back(user.getNickname());
    if (!(user.getOper()))
    {
        command.reply(381, args);                   // RPL_YOUREOPER (381)
        user.setOper(true);
    }
    std::string input = "MODE " + user.getNickname() + " +o";
    user.setBoolO(true);
    
}
