/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:48 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:38:58 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

void        PASS(Command &command)	// Parameters: <password>
{
    strVec		args = command.getParameters();
    User		&user = command.getUser();

   
    /* Check if at least one parameter is given */
    if (args.empty())
    {
        args.push_back(user.getNickname());
        args.push_back(command.getCommand());
	    return (command.reply(461, args));                        // [ERR_NEEDMOREPARAMS](461)
    }

    /* Check if password sent matches server's one */
    if (command.getParams()->get_password() != clean_string(args[0]))
    {
        args.clear();
        args.push_back(user.getNickname());
        return (command.reply(464, args));                        // [ERR_PASSWDMISMATCH] (464)
    }

    /* Check if user already logged in server */
    if (user.getBoolAuthentification() == true)
    {
        args.clear();
        args.push_back(user.getNickname());
        return (command.reply(462, args));                        // [ERR_ALREADYREGISTERED] (462)
    }

    /* if none of the above error cases are trigered, set the pass bool to 1 to allow connection with a secured server*/
    user.setBoolPassword(true);

}
