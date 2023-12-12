/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:09:26 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 14:58:08 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

void        USER(Command &command)
{
    strVec      args;

	if (command.getUser().getBoolUsername())
    {
        args.push_back(command.getUser().getNickname());
		return command.reply(462, args);                // ERR_ALREADYREGISTERED (462)
    }
    if (command.getParameters().size() < 4)
    {
        args.push_back(command.getUser().getNickname());
        args.push_back(command.getCommand());
        return command.reply(461, args);                // ERR_NEEDMOREPARAMS (461)
    }

	args = command.getParameters();
    command.getUser().setUsername(args[0]);
    command.getUser().setMode(args[1]);
    command.getUser().setRealname(command.getTrailer());
    command.getUser().setBoolUsername(true);
}