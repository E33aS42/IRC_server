/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:14 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:42:48 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// to do

# include "ircCommands.hpp"

# define USER_I "i"
# define USER_A "a"
# define USER_O "o"

// gerer les modes i, l, o

bool        ismode(std::string)
{
    return (true);
}

void    	MODE(Command &command)//   Parameters: <target> [<modestring> [<mode arguments>...]]
{
    int         op = 1; // 1 == + 2 == -
    bool        rply472 = false;
    bool        rply441 = false;
    bool        rplyo = false;
    bool        rplyi = false;
    bool        rplyl = false;
    strVec      args;
    strVec      ret;
    chanMap     servChan;
    chanMap     userChan;
    userMap     chanUsers;
    std::string target;

    // User	&user = command.getUser();
	args = command.getParameters();
    servChan = command.getServer().get_channels2();
    userChan = command.getUser().getChannels();

    ret.push_back("MODE");
    if (args.empty())		
		return (command.reply(461, ret));              // ERR_NEEDMOREPARAMS (461)

    target = args[0];
    ret.push_back(args[0]);
    if (target[0] == '#')                               // CHANNELS
    {
        if (servChan.find(target) == servChan.end())
            return command.reply(403, args);		    // ERR_NOSUCHCHANNEL (403)
        if (args.size() == 1)
            return command.reply(324, args);            // RPL_CHANNELMODEIS (324)
        chanMap_it it = servChan.find(target);
        if (!(*it).second->isOperator(command.getUser().getNickname()))
            return command.reply(482);              // ERR_CHANOPRIVSNEEDED (482)
        for(size_t i = 1; i < args[1].size(); i++)
        {
            if (userChan.find(target) == userChan.end())
            {
                command.reply(442);              // ERR_NOTONCHANNEL (442)
                continue ;
            }
            else if (args[1][i] == '+')
                op = 1;
            else if (args[1][i] == '-')
                op = 2;
            else if (rplyo == false && args[1][i] == 'o')
            {
                if (args.size() < 3 || userChan.find(args[2]) == userChan.end() && rply441 == false)
                {
                    command.reply(441, args);            // ERR_USERNOTINCHANNEL (441)
                    rply441 = true;
                    continue ;
                }
                if (op == 1)
                {
                    
                }
                else
                {
                    
                }
                rplyo = true;
            }
            else if (rplyi == false && args[1][i] == 'i')
            {
                if (op == 1)
                {}
                else
                {}
                rplyo = true;
            }
            else if (rplyl == false && args[1][i] == 'l')
            {
                if (op == 1)
                {}
                else
                {}
                rplyo = true;
            }
            else if (rply472 == false)
            {
                ret.push_back(args[1].substr(i, 1));
                command.reply(472, args);        // ERR_UNKNOWNMODE (472)
                ret.pop_back();
                rply472 = true;
            }
        }
    }
    
    //     ERR_KEYSET
    //     ERR_NOCHANMODES                 
    //     
    //     
    //     RPL_BANLIST                     RPL_ENDOFBANLIST
    //     RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
    //     RPL_INVITELIST                  RPL_ENDOFINVITELIST
    //     RPL_UNIQOPIS
    
    else                                    // USERS
    {
        
    }
            //  ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
            // ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS   

    
    
    // User mode
    
    
}

// mode asd
// :helix.oftc.net 403 qwe asd :No such channel
// mode qwe
// :helix.oftc.net 221 qwe +i
// mode qwe -i
// :qwe!~a@62.210.34.8 MODE qwe :-i
// mode qwe
// :helix.oftc.net 221 qwe +
// mode qwe +i
// :qwe!~a@62.210.34.8 MODE qwe :+i
// mode qwe
// :helix.oftc.net 221 qwe +i
// mode sdfs
// :helix.oftc.net 403 qwe sdfs :No such channel



//   The MODE command is used to set or remove options (or modes) from a given target.

// User mode
// If <target> is a nickname that does not exist on the network, the ERR_NOSUCHNICK (401) numeric is returned. If <target> is a different nick than the user who sent the command, the ERR_USERSDONTMATCH (502) numeric is returned.

// If <modestring> is not given, the RPL_UMODEIS (221) numeric is sent back containing the current modes of the target user.

// If <modestring> is given, the supplied modes will be applied, and a MODE message will be sent to the user containing the changed modes. If one or more modes sent are not implemented on the server, the server MUST apply the modes that are implemented, and then send the ERR_UMODEUNKNOWNFLAG (501) in reply along with the MODE message.

// Channel mode
// If <target> is a channel that does not exist on the network, the ERR_NOSUCHCHANNEL (403) numeric is returned.

// If <modestring> is not given, the RPL_CHANNELMODEIS (324) numeric is returned. Servers MAY choose to hide sensitive information such as channel keys when sending the current modes. Servers MAY also return the RPL_CREATIONTIME (329) numeric following RPL_CHANNELMODEIS.

// If <modestring> is given, the user sending the command MUST have appropriate channel privileges on the target channel to change the modes given. If a user does not have appropriate privileges to change modes on the target channel, the server MUST not process the message, and ERR_CHANOPRIVSNEEDED (482) numeric is returned. If the user has permission to change modes on the target, the supplied modes will be applied based on the type of the mode (see below). For type A, B, and C modes, arguments will be sequentially obtained from <mode arguments>. If a type B or C mode does not have a parameter when being set, the server MUST ignore that mode. If a type A mode has been sent without an argument, the contents of the list MUST be sent to the user, unless it contains sensitive information the user is not allowed to access. When the server is done processing the modes, a MODE command is sent to all members of the channel containing the mode changes. Servers MAY choose to hide sensitive information when sending the mode changes.

// <modestring> starts with a plus ('+', 0x2B) or minus ('-', 0x2D) character, and is made up of the following characters:

// '+': Adds the following mode(s).
// '-': Removes the following mode(s).
// 'a-zA-Z': Mode letters, indicating which modes are to be added/removed.
// The ABNF representation for <modestring> is:

//   modestring  =  1*( modeset )
//   modeset     =  plusminus *( modechar )
//   plusminus   =  %x2B / %x2D
//                    ; + or -
//   modechar    =  ALPHA
// There are four categories of channel modes, defined as follows:

// Type A: Modes that add or remove an address to or from a list. These modes MUST always have a parameter when sent from the server to a client. A client MAY issue this type of mode without an argument to obtain the current contents of the list. The numerics used to retrieve contents of Type A modes depends on the specific mode. Also see the EXTBAN parameter.
// Type B: Modes that change a setting on a channel. These modes MUST always have a parameter.
// Type C: Modes that change a setting on a channel. These modes MUST have a parameter when being set, and MUST NOT have a parameter when being unset.
// Type D: Modes that change a setting on a channel. These modes MUST NOT have a parameter.
// Channel mode letters, along with their types, are defined in the CHANMODES parameter. User mode letters are always Type D modes.

// The meaning of standard (and/or well-used) channel and user mode letters can be found in the Channel Modes and User Modes sections. The meaning of any mode letters not in this list are defined by the server software and configuration.

// Type A modes are lists that can be viewed. The method of viewing these lists is not standardised across modes and different numerics are used for each. The specific numerics used for these are outlined here:

// Ban List "+b": Ban lists are returned with zero or more RPL_BANLIST (367) numerics, followed by one RPL_ENDOFBANLIST (368) numeric.
// Exception List "+e": Exception lists are returned with zero or more RPL_EXCEPTLIST (348) numerics, followed by one RPL_ENDOFEXCEPTLIST (349) numeric.
// Invite-Exception List "+I": Invite-exception lists are returned with zero or more RPL_INVITELIST (336) numerics, followed by one RPL_ENDOFINVITELIST (337) numeric.
// After the initial MODE command is sent to the server, the client receives the above numerics detailing the entries that appear on the given list. Servers MAY choose to restrict the above information to channel operators, or to only those clients who have permissions to change the given list.

// Command Examples:

//   MODE dan +i                     ; Setting the "invisible" user mode on dan.

//   MODE #foobar +mb *@127.0.0.1    ; Setting the "moderated" channel mode and
//                                   adding the "*@127.0.0.1" mask to the ban
//                                   list of the #foobar channel.
// Message Examples:

//   :dan!~h@localhost MODE #foobar -bl+i *@192.168.0.1
//                                   ; dan unbanned the "*@192.168.0.1" mask,
//                                   removed the client limit from, and set the
//                                   #foobar channel to invite-only.

//   :irc.example.com MODE #foobar +o bunny
//                                   ; The irc.example.com server gave channel
//                                   operator privileges to bunny on #foobar.



// mode user i = invisible user
// mode #chan1 i = channel in invite-only mode
