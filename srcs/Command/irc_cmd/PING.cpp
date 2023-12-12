/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:57 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:39:01 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

void	PING(Command &command)	// Parameters: <token>
{
	strVec	args;

	args.push_back(command.getCommand());
	if (command.getParameters().size() == 0)
	{
		args.push_back(command.getUser().getNickname());
		return (command.reply(461, args));
	}
	args.push_back(command.getParameters()[0]);
	args.push_back(command.getUser().getHostname());
	return command.reply(-10, args);
}
