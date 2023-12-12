/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircCommands.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:58:22 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:43:56 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCOMMANDS_HPP
# define IRCCOMMANDS_HPP

# include "All.hpp"

/* Commands*/

void	JOIN(Command& command);
void	KICK(Command& command);
void	MODE(Command &command);
void	MOTD(Command &command);
void    motd(int fd, User *u);
void    NAMES(Command &command);
void    NICK(Command &command);
void	NOTICE(Command& command);
void	OPER(Command& command);
void	PART(Command &command);
void	PASS(Command &command);
void	PING(Command &command);
void	PONG(Command &command);
void	PRIVMSG(Command& command);
void	QUIT(Command& command);
void	TOPIC(Command &command);
void	USER(Command &command);
void	WHOIS(Command& command);

/* Functions */
std::string server_replies(int code, strVec args);
std::string get_ERR_RPL(int code, strVec args);

/* Errors */

std::string ERR_NOSUCHNICK(strVec args);
std::string ERR_NOSUCHCHANNEL(strVec args);
std::string ERR_TOOMANYCHANNELS(strVec args);
std::string ERR_CANNOTSENDTOCHAN(strVec args);
std::string ERR_TOOMANYTARGETS(strVec args);
std::string ERR_NOORIGIN();
std::string ERR_NORECIPIENT(strVec args);
std::string ERR_NOTEXTTOSEND(strVec args);
std::string ERR_UNKNOWNCOMMAND(strVec args);
std::string ERR_NOMOTD();
std::string	ERR_NONICKNAMEGIVEN(strVec args);
std::string	ERR_ERRONEUSNICKNAME(strVec args);
std::string	ERR_NICKNAMEINUSE(strVec args);
std::string ERR_USERNOTINCHANNEL(strVec args);
std::string ERR_NOTONCHANNEL(strVec args);
std::string ERR_USERONCHANNEL(strVec args);
std::string ERR_NEEDMOREPARAMS(strVec args);
std::string ERR_ALREADYREGISTERED(strVec args);
std::string ERR_PASSWDMISMATCH(strVec args);
std::string ERR_CHANNELISFULL(strVec args);
std::string ERR_BADCHANNAME(strVec args);
std::string ERR_INVITEONLYCHAN(strVec args);
std::string ERR_NOPRIVILEGES();
std::string ERR_CHANOPRIVSNEEDED(strVec args);
std::string ERR_NOOPERHOST(strVec args);
std::string ERR_UMODEUNKNOWNFLAG(strVec args);
std::string ERR_USERSDONTMATCH(strVec args);

/* Replies */

# define CODE_RPL_SETNICK            "-1"
# define CODE_RPL_HASJOIN            "-001"
# define CODE_RPL_MSGTOONE           "-002"
# define CODE_RPL_MSGTOCHAN          "-003"
# define CODE_RPL_WELCOME            "001"
# define CODE_RPL_YOURHOST           "002"
# define CODE_RPL_CREATED            "003"
# define CODE_RPL_MYINFO             "004"
# define CODE_RPL_UMODEIS            "201"
# define CODE_RPL_AWAY               "301"
# define CODE_RPL_UNAWAY             "305"
# define CODE_RPL_NOWAWAY            "306"
# define CODE_RPL_WHOISUSER          "311"
# define CODE_RPL_WHOISSERVER        "312"
# define CODE_RPL_WHOISOPERATOR      "313"
# define CODE_RPL_WHOISIDLE          "317"
# define CODE_RPL_ENDOFWHOIS         "318"
# define CODE_RPL_WHOISCHANNELS      "319"
# define CODE_RPL_LISTSTART          "321"
# define CODE_RPL_LIST               "322"
# define CODE_RPL_NOTOPIC            "331"
# define CODE_RPL_TOPIC              "332"
# define CODE_RPL_TOPICWHOTIME       "333"
# define CODE_RPL_INVITING           "341"
# define CODE_RPL_NAMREPLY           "353"

# define CODE_RPL_ENDOFNAMES         "366"
# define CODE_RPL_MOTD               "372"
# define CODE_RPL_MOTDSTART          "375"
# define CODE_RPL_ENDOFMOTD          "376"
# define CODE_RPL_WHOISHOST          "378"
# define CODE_RPL_WHOISMODES         "379"
# define CODE_RPL_YOUREOPER          "381"

std::string	RPL_SETNICK(strVec args);
std::string RPL_HASJOIN(strVec args);
std::string RPL_HASLEFT(strVec args);
std::string RPL_MSGTOONE(strVec args);
std::string RPL_MSGTOCHAN(strVec args);
std::string RPL_KICKUSER(strVec args);
std::string RPL_LEFTCHAN(strVec args);
std::string RPL_NOTICETOONE(strVec args);
std::string RPL_NOTICETOCHAN(strVec args);
std::string	RPL_PING(strVec args);
std::string	RPL_QUIT(strVec args);

std::string RPL_WELCOME(strVec args);
std::string RPL_YOURHOST(std::string servername, std::string ver);
std::string RPL_CREATED();
std::string RPL_MYINFO(std::string servername, std::string ver);
std::string RPL_AWAY(std::string nick, std::string message);
std::string RPL_UNAWAY();
std::string RPL_NOWAWAY();
std::string RPL_WHOISUSER(strVec args);
std::string RPL_WHOISSERVER(std::string nick, std::string server, std::string info);
std::string RPL_WHOISOPERATOR(std::string nick);
std::string RPL_WHOISIDLE(std::string nick, std::string integer);
std::string RPL_ENDOFWHOIS(strVec args);
std::string RPL_WHOISCHANNELS(strVec args);
std::string RPL_LISTSTART(std::string channel);
std::string RPL_LIST(std::string channel, std::string count, std::string topic);
std::string RPL_NOTOPIC(strVec args);
std::string RPL_TOPIC(std::string nick, std::string channel, std::string topic);
std::string RPL_TOPIC(strVec args);
std::string RPL_TOPICWHOTIME(std::string channel, std::string nick);
std::string RPL_INVITING(std::string nick, std::string channel);
std::string RPL_NAMREPLY(strVec args);
std::string RPL_NAMREPLYbis(strVec args);
std::string RPL_NAMREPLYbis2(strVec args);
std::string RPL_ENDOFNAMES(strVec args);
std::string RPL_MOTD(std::string line_number);
std::string RPL_MOTDSTART(std::string server_name);
std::string RPL_ENDOFMOTD();
std::string RPL_WHOISHOST(std::string nick);
std::string RPL_WHOISMODES(std::string nick);
std::string RPL_YOUREOPER(strVec args);

#endif