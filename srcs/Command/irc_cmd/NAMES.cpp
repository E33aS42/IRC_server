/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:09:06 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:36:45 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// optional

# include "ircCommands.hpp"

static std::string		get_names_from_chan(Server *serv, Channel *channel)
{
	strSet      nicks = channel->get_nicksChan();
	std::string	list = "";
	for (strSet_it it = nicks.begin(); it != nicks.end(); it++)
	{
		if(serv->getUser_fromNick(*it)->getBoolI() == false)
		{
			list += *it;
			list += " ";
		}
	}
	std::cout << "list: " << list << std::endl;
	return list;
}

static std::string		get_names_from_server(strSet nicks)
{
	std::string	list = "";
	for (strSet_it it = nicks.begin(); it != nicks.end(); it++)
	{
		list += *it;
		list += " ";
	}
	return list;
}

void    				NAMES(Command &command) // Parameters: <channel>{,<channel>}
{
	strVec		args;
	User		&user = command.getUser();
	Server		*serv = user.getServer();
	chanMap		*channels = serv->get_channels();
	std::string chan = "";
	std::string	nicks = "";
	strSet		serv_nicks = serv->get_users_nick();
	
	if (!(channels->empty()))
	{	for(chanMap_it it = channels->begin(); it != channels->end(); it++)
		{
			if (user.getBoolI() == false)
			{
				args.push_back(user.getNickname());
				chan = (*it).first;
				nicks = get_names_from_chan(&command.getServer(), (*it).second);
				args.push_back(chan);
				args.push_back(nicks);
				command.reply(-12, args);				// RPL_NAMREPLYbis (353)
				args.clear();
			}
		}
	}
	
	if (user.getBoolI() == false)
		args.push_back(user.getNickname());
	nicks = get_names_from_server(serv_nicks);
	args.push_back(nicks);
	if (args.size() != 0 && !args.empty())
		command.reply(-13, args);						// RPL_NAMREPLYbis2 (353)

	args.clear();
	args.push_back(chan);
	args.push_back("*");
	command.reply(366, args);						// RPL_ENDOFNAMES (366)
}
