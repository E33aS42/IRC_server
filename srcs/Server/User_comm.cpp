/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User_comm.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:54 by esommier          #+#    #+#             */
/*   Updated: 2022/11/17 13:24:44 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"

User*	Server::getUser_fromNick(std::string nick) 
{
	for (userMap_it it = _user_map.begin(); it != _user_map.end(); it++)
	{
		if (((*it).second)->getNickname() == nick)
			return(*it).second;
	}

	return NULL;
}

void	Server::delUser_fromNick(std::string nick) 
{
	for (userMap_it it = _user_map.begin(); it != _user_map.end(); it++)
	{
		if (((*it).second)->getNickname() == nick)
		{
			delete((*it).second);
			_user_map.erase(it);
			break ;
		}
	}
}

void	Server::delUser_fromChan(chanMap *channels, std::string nick, User &user) 
{
	strSet		nickChan;
	chanSet		delChan;
	
	for (chanMap_it it = channels->begin(); it != channels->end(); it++)
	{
		nickChan = (*it).second->get_nicksChan();
		if (nickChan.find(nick) != nickChan.end())
		{
			nickChan.erase(nick);
			(*it).second->set_nicksChan(nickChan);
			(*it).second->delUser(&user);
			if (!(*it).second->get_usernb())
				delChan.insert((*it).second);
		}
	}

	for (chanSet_it it = delChan.begin(); it != delChan.end(); it++)
		del_chan((*it));
	delChan.clear();
}
