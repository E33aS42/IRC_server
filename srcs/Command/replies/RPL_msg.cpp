/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_msg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:13:05 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 13:25:10 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

std::string	RPL_SETNICK(strVec args)														// -1
{
    std::string nick = args[0];
	return "NICK :" + nick;
}

std::string RPL_HASJOIN(strVec args)														// -2
{	// :firstuser!~l@62.210.34.109 JOIN :#1
    std::string chan	= args[0];
    return "JOIN :" + chan; 
}                                      

std::string RPL_HASLEFT(strVec args)                                                        // -3
{
    std::string chan	= args[0];
    return "PART " + chan;
    // :firstuser!~l@62.210.34.109 PART #1 (les deux le voient)
}

std::string RPL_MSGTOONE(strVec args)														// -4
{
	// :firstuser!~l@62.210.34.109 PRIVMSG #1 :helooo
	// :firstuser!~l@62.210.34.109 PRIVMSG #1 :test
	std::string target	= args[0];
	std::string msg		= args[1];
	return " PRIVMSG " + target + " :" + msg; 
}

std::string RPL_MSGTOCHAN(strVec args)														// -5
{
	// :firstuser!~l@62.210.34.109 PRIVMSG seconduser :hellooooooo
	std::string chan	= args[0];
	std::string msg		= args[1];
	return " PRIVMSG " + chan + " :" + msg;
}

std::string RPL_KICKUSER(strVec args)														// -6
{
	std::string chan	= args[0];
	std::string nick	= args[1];
	return "KICK " + chan + " " + nick + " :" + nick;
}

std::string RPL_LEFTCHAN(strVec args)														// -7
{
	std::string chan	= args[0];
	std::string msg		= args[1];
	return " PART " + chan + " " + msg;
}

std::string RPL_NOTICETOONE(strVec args)													// -8
{
	// :firstuser!~l@62.210.34.109 PRIVMSG #1 :helooo
	// :firstuser!~l@62.210.34.109 PRIVMSG #1 :test
	std::string target	= args[0];
	std::string msg		= args[1];
	return " NOTICE " + target + " :" + msg; 
}

std::string RPL_NOTICETOCHAN(strVec args)													// -9
{
	// :firstuser!~l@62.210.34.109 PRIVMSG seconduser :hellooooooo
	std::string chan	= args[0];
	std::string msg		= args[1];
	return " NOTICE " + chan + " :" + msg;
}

std::string	RPL_PING(strVec args)															// -10
{
    std::string nick = args[1];
    std::string hostname = args[2];
	return " PONG " + hostname + " :" + nick;
	
	// return " PRIVMSG " + nick + " :PING " + nick;
}

std::string	RPL_QUIT(strVec args)															// -11
{
    std::string reason = args[0];
	return "QUIT :" + reason;
}

std::string RPL_TOPIC(strVec args) 															// -14
{
	std::string channel = args[0];
	std::string topic = args[1];
	return "TOPIC " + channel + " :" + topic;
}	

std::string RPL_WELCOME(strVec args) 														// 001
{
	std::string	nick = args[0];
	std::string	username = args[1];
	std::string	hostname = args[2];
	
	return " :Welcome to the Internet Relay Network " + nick + "!" + username + "@" + hostname; 
}	

// std::string RPL_WELCOME(std::string nick) 
// { return " :Welcome to the Internet Relay Network " + nick; }								// 001
std::string RPL_YOURHOST(std::string servername, std::string ver) 
{ return " :Your host is " + servername + ", running version " + ver; }						// 002
std::string RPL_CREATED()
{ return " :This server was created on 22/10/2022"; }
std::string RPL_MYINFO(std::string servername, std::string ver)
{ return " :" + servername + " ver " + ver; }
std::string RPL_UMODEIS(void)
{ return std::string(""); }																	// 201
std::string RPL_AWAY(std::string nick, std::string message) 
{ return nick + " :" + message; }															// 301
std::string RPL_UNAWAY() 
{ return " :You are no longer marked as being away"; }										// 305
std::string RPL_NOWAWAY() 
{ return " :You have been marked as being away"; }											// 306

std::string RPL_WHOISUSER(strVec args) 														// 311
{ return args[0] + " " + args[0] + " ~" + args[1] + " " + args[2] + " * :" + args[3]; }		//:coulomb.oftc.net 311 poiu poiu ~user 2a01:e0a:232:dbd0:58c1:7fbe:dcd7:bcd2 * :realname


std::string RPL_WHOISSERVER(std::string nick, std::string server, std::string info) 
{ return nick + " " + server + " :" + info; }				    						 	// 312
std::string RPL_WHOISOPERATOR(std::string nick) 
{ return nick + " :is an IRC operator"; }			                    					// 313
std::string RPL_WHOISIDLE(std::string nick, std::string integer) 
{ return nick + " " + integer + " :seconds idle"; }											// 317

std::string RPL_ENDOFWHOIS(strVec args) 													// 318
{ return args[0] + " :End of /WHOIS list"; }

std::string RPL_WHOISCHANNELS(strVec args) 										// 319
{
	std::string	str = args[0];												//:coulomb.oftc.net 319 qwe qwe :@#3333 @#2222 @#1111 @#wert
	str += " " + args[0] + " :";
	for (strVec_it it = args.begin() + 1; it != args.end(); it++)
	{
		str += (*it);
		str += " ";
	}
	
	return str; 
}

std::string RPL_LISTSTART(std::string channel) 									// 321
{ return channel + " Channel :Users  Name"; }
std::string RPL_LIST(std::string channel, std::string count, std::string topic) // 322
{ return channel + " " + count + " :" + topic; }
std::string RPL_NOTOPIC(strVec args) 											// 331
{
	std::string nick = args[0];
	std::string channel = args[1];
	return nick + " " + channel + " :No topic is set";
}
std::string RPL_TOPIC(std::string nick, std::string channel, std::string topic) // 332
{ return nick + " " + channel + " :" + topic; }	
std::string RPL_TOPICWHOTIME(std::string channel, std::string nick) 			// 333
{
	size_t time = std::time(0);
	std::stringstream ss;
	ss << time;
	std::string str = ss.str();
	
	return nick + " " + channel + " " + nick + " " + str; 
}
std::string RPL_INVITING(std::string nick, std::string channel) 				// 341
{ return nick + channel; }	

std::string RPL_NAMREPLY(strVec args)											// 353
{
	// nick = #test :nick opara_v25267525182197 tkob FloodServ zmanian Peetz0r
	std::string	str = args[0];
	str += " = ";
	str += args[1];
	str += " :";
	str += args[2];
	for (strVec_it it = args.begin() + 3; it != args.end(); it++)
	{
		str += " ";
		str += *it;
	}
	return str; 
}

std::string RPL_NAMREPLYbis(strVec args)													// 353 for NAMES  -12
{
// :liquid.oftc.net 353 qwe = #debian-nordic :TinoDidriksen pabs Brainstorm
	std::string	str = args[0];
	str += " = ";
	str += args[1];
	str += " :";
	str += args[2];
	return str; 
}

std::string RPL_NAMREPLYbis2(strVec args)													// 353 for NAMES -13
{
// :liquid.oftc.net 353 qwe * * :admin ToboT Mikaela pabs Brainstorm ketas zcrayfish Maus ]_ esselfe jlsalvador pmp-p TReKiE djackal Gugge-47527 CTCPServ MoranServ GroupServ Bopm GanneffServ FloodServ OperServ ChanServ NickServ mwk mtj rektide Tatanka Myon rkta Frogging101 cheapie TinoDidriksen Nothing4You 
	
	std::string	str = args[0];
	str += " *";
	str += " *";
	str += " :";
	if (args.empty() != 1 && args.size() >= 2)
		str += args[1];
	return str; 
}


std::string RPL_ENDOFNAMES(strVec args) 	                    							// 366
{ return args[0] + " " + args[1] + " :End of /NAMES list."; }
std::string RPL_MOTD(std::string line_number) 
{ return " :" + line_number; }										                    	// 372
std::string RPL_MOTDSTART(std::string server_name) 
{ return " :- " + server_name + " Message of the day - "; }									// 375
std::string RPL_ENDOFMOTD() 
{ return " :End of /MOTD command."; }														// 376
std::string RPL_WHOISHOST(std::string nick)
{ return nick + " :is connecting from *@localhost 127.0.0.1"; }								// 378
std::string RPL_WHOISMODES(std::string nick) 
{ return nick + " :is using modes +ailosw"; }												// 379
std::string RPL_YOUREOPER(strVec args) 
{ return args[0] + " :You are now an IRC operator"; }													// 381