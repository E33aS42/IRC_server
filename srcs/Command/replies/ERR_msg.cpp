/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_msg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:12:55 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 12:30:17 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

std::string ERR_NOSUCHNICK(strVec args) 								// 401
{ 
	std::string nick = args[1];
	std::string wrong_nick = args[0];
    return nick + " " + wrong_nick + " :No such nick/channel"; 
}
std::string ERR_NOSUCHCHANNEL(strVec args)								// 403
{ 
	std::string channel = args[0];
	std::string nickname = args[1];
    return nickname + " " + channel + " :No such channel"; 
}
std::string ERR_CANNOTSENDTOCHAN(strVec args) 				    		// 404
{ 
	std::string channel = args[0];
    return channel + " :Cannot send to channel"; 
}
std::string ERR_TOOMANYCHANNELS(strVec args) 							// 405
{ return args[0] + " :You have joined too many channels"; }
std::string ERR_TOOMANYTARGETS(strVec args)								// 407
{ 
	std::string target = args[0];
	return target + " :Duplicate recipients. No message delivered"; 
}
std::string ERR_NOORIGIN() 												// 409
{ 	return " :No origin specified"; }
std::string ERR_NORECIPIENT(strVec args) 								// 411
{ 
	std::string command = args[0];
	return " :No recipient given (" + command + ")"; 
}
std::string ERR_NOTEXTTOSEND(strVec args) 								// 412
{ 	return args[0] + " :No text to send"; }
std::string ERR_UNKNOWNCOMMAND(strVec args)								// 421
{	
	std::string	cmd = args[0];
	return cmd + " :Unknown command"; 
}
std::string ERR_NOMOTD() 												// 422
{ 	return " :MOTD File is missing"; }
std::string	ERR_NONICKNAMEGIVEN(strVec args) 							// 431
{
	std::string nickname;
	if (args.size() != 0)
		nickname = args[0];
	else
		nickname = std::string(" ");
	return nickname + " :No nickname given"; }
std::string	ERR_ERRONEUSNICKNAME(strVec args)							// 432
{ 
	std::string nick = args[0];
	return nick + " :Erroneus nickname";
} 
std::string	ERR_NICKNAMEINUSE(strVec args) 								// 433
{ 
	std::string nick = args[0];
	return nick + " :Nickname is already in use"; 
}
std::string ERR_USERNOTINCHANNEL(strVec args) 							// 441
{ 
	std::string nick = args[0];
	std::string channel = args[1];
	return nick + " " + channel + " :They aren't on that channel"; 
}
std::string ERR_NOTONCHANNEL(strVec args) 								// 442
{ 
	std::string channel = args[0];
	std::string nick = args[1];
	return nick + " " + channel + " :You're not on that channel"; 
}
std::string ERR_USERONCHANNEL(strVec args) 								// 443
{
	std::string	user = args[0];
	std::string channel = args[1];
	return user + " " + channel + " :is already on channel"; 
}
std::string ERR_NEEDMOREPARAMS(strVec args) 							// 461
{ 
	std::string nickname = args[0];
	std::string	command = args[1];
	return nickname + " " + command + " :Not enough parameters"; 
}	
std::string ERR_ALREADYREGISTERED(strVec args) 							// 462
{
	std::string nickname = args[0];
	return nickname + " :You may not reregister";
}	
std::string ERR_PASSWDMISMATCH(strVec args) 							// 464
{ return args[0] + " :Password incorrect"; }	
std::string ERR_CHANNELISFULL(strVec args) 								// 471
{ 
	std::string channel = args[0];
	return channel + " :Cannot join channel (+l)"; 
}
std::string ERR_INVITEONLYCHAN(strVec args) 							// 473
{ 
	std::string channel = args[0];
	return channel + " :Cannot join channel (+i)"; 
}
std::string ERR_BADCHANNAME(strVec args)								// 479
{
	std::string channel = args[0];
	return channel + " :Illegal channel name";
}
std::string ERR_NOPRIVILEGES() 											// 481
{ return " :Permission Denied- You're not an IRC operator"; }
std::string ERR_CHANOPRIVSNEEDED(strVec args) 							// 482
{ 
	std::string channel = args[0];
	return channel + " :You're not channel operator"; 
}
std::string ERR_NOOPERHOST(strVec args) 								// 491
{ return args[0] + " :No O-lines for your host"; }		

std::string ERR_UMODEUNKNOWNFLAG(strVec args) 							// 501
{ 
	std::string command = args[0];
	return command + " :Unknown flag"; 
}		

std::string ERR_USERSDONTMATCH(strVec args) 							// 502
{ 
	std::string command = args[0];
	return command + " :Users don't match";
}	
