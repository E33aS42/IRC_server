/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_replies.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:24:10 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:42:02 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"


std::string server_replies(int code, strVec args)
{

	switch(code)
	{
		case -1:
			return (RPL_SETNICK(args));
		case -2:
			return (RPL_HASJOIN(args));
		case -3:
			return (RPL_HASLEFT(args));
		case -4:
			return (RPL_MSGTOONE(args));
		case -5:
			return (RPL_MSGTOCHAN(args));
		case -6:
			return (RPL_KICKUSER(args));
		case -7:
			return (RPL_LEFTCHAN(args));
		case -8:
			return (RPL_NOTICETOONE(args));	
		case -9:
			return (RPL_NOTICETOCHAN(args));
		case -10:
			return (RPL_PING(args));
		case -11:
			return (RPL_QUIT(args));
		case -12:
			return (RPL_NAMREPLYbis(args));
		case -13:
			return (RPL_NAMREPLYbis2(args));
		case -14:
			return (RPL_TOPIC(args));

		case 311:
			return (RPL_WHOISUSER(args));
		// case 312:
		// 	return (client + RPL_WHOISSERVER(arg1, arg2, arg3));
		// case 313:
		// 	return (client + RPL_WHOISOPERATOR(arg1));
		case 318:
			return (RPL_ENDOFWHOIS(args));
		case 319:
			return (RPL_WHOISCHANNELS(args));
		// case 323:
		// 	return (client + RPL_NOTOPIC(arg1));
		case 331:
			return (RPL_NOTOPIC(args));
		// case 332:
		// 	return (client + RPL_TOPIC(arg1, arg2));
		case 353:
			return (RPL_NAMREPLY(args));
		case 366:
			return (RPL_ENDOFNAMES(args));
		// case 372:
		// 	return (client + RPL_MOTD(args));
		// case 375:
		// 	return (client + RPL_MOTDSTART(args));
		// case 376:
		// 	return (client + RPL_ENDOFMOTD());
		// case 378:
		// 	return (client + RPL_WHOISHOST(args));
		// case 379:
		// 	return (client + RPL_WHOISMODES(args));
		case 381:
			return (RPL_YOUREOPER(args));
		case 401:
			return (ERR_NOSUCHNICK(args));
		case 403:
			return (ERR_NOSUCHCHANNEL(args));
        case 404:
			return (ERR_CANNOTSENDTOCHAN(args));
		case 405:
			return (ERR_TOOMANYCHANNELS(args)); 
        case 407:
			return (ERR_TOOMANYTARGETS(args));
        case 409:
			return (ERR_NOORIGIN());
        case 411:
			return (ERR_NORECIPIENT(args));
        case 412:
			return (ERR_NOTEXTTOSEND(args));
		case 421:
			return (ERR_UNKNOWNCOMMAND(args));
        case 422:
			return (ERR_NOMOTD());
        case 431:
			return (ERR_NONICKNAMEGIVEN(args));
        case 432:
			return (ERR_ERRONEUSNICKNAME(args));
        case 433:
			return (ERR_NICKNAMEINUSE(args));
        case 441:
			return (ERR_USERNOTINCHANNEL(args));
        case 442:
			return (ERR_NOTONCHANNEL(args));
        case 443:
			return (ERR_USERONCHANNEL(args));
        case 461:
			return (ERR_NEEDMOREPARAMS(args));
        case 462:
			return (ERR_ALREADYREGISTERED(args));
        case 464:
			return (ERR_PASSWDMISMATCH(args));
        case 471:
			return (ERR_CHANNELISFULL(args));
        case 473:
			return (ERR_INVITEONLYCHAN(args));
		case 479:
			return (ERR_BADCHANNAME(args));
        case 481:
			return (ERR_NOPRIVILEGES());
        case 482:
			return (ERR_CHANOPRIVSNEEDED(args));
        case 491:
			return (ERR_NOOPERHOST(args));
        case 501:
			return (ERR_UMODEUNKNOWNFLAG(args));
		case 502:
			return (ERR_USERSDONTMATCH(args));
		default:
			return std::string();
	}
}

std::string get_ERR_RPL(int code, strVec args)
{
	std::string reply;

	try
	{
		return server_replies(code, args);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return "";
}