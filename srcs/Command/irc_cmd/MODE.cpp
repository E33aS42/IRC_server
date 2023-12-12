/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:14 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 14:34:03 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

// User modes : a,i,o
// Channel modes : 

# define USER_I 'i'
# define USER_A 'a'
# define USER_O 'o'

bool    check_flag(char mode)           // check unvalid characters
{
    if (!isalpha(mode))
        return (true);
    return (false);
}

std::string     user_modes(User *user)  // return all user modes available
{
    std::string ret = "";
    if (!user->getBoolI() && !user->getBoolA() && !user->getBoolO())
        return (ret);
    ret += '+';
    if (user->getBoolI())
        ret += 'i';
    if (user->getBoolA())
        ret += 'a';
    if (user->getBoolO())
        ret += 'o';
    return (ret);
}

void    MODE(Command &command)
{
    strVec          args = command.getParameters();
    strVec          ret;
    std::string     nick2 = command.getUser().getNickname();
    std::string     ret_modes;
    
    int             i;
    bool            unknown_flag = false;
    
    if (args.size() < 1 || args.empty())        // ERR_NEEDMOREPARAMS
    {
        ret.push_back(command.getUser().getNickname());
        ret.push_back("MODE");
        return (command.reply(461, ret));
    }

    std::string     nick1 = args[0];
    User            *user = command.getUser(nick1);

    if (nick1[0] == '#')
        return;
    if (nick1 != nick2)                         // ERR_USERSDONTMATCH
    {
        ret.push_back("MODE");
        return (command.reply(502, ret));
    }

    if (args.size() == 1 && user_modes(user).size() != 0)   // MODE <nickname> only (display all modes available for user)
    {
        user->message_reply(user->getFd(), user->getHostname(), CODE_RPL_UMODEIS + std::string(" ") + \
            command.getCommand() + std::string(" ") + user->getNickname() + std::string(" :") + user_modes(user));     // RPL_UMODEIS
        return;
    }

    ret.push_back("MODE");
    for (strVec_it it = args.begin(); it != args.end(); ++it)
    {
        i = 1;
        if ((*it)[0] == '+')
        {
            if (user->getBoolI() && user->getBoolA() && user->getBoolO())   // user already has all modes available
                return ;
            ret_modes += '+';

            while ((*it)[i])
            {
                if (check_flag((*it)[i]))                                   // check for unvalid characters
                    unknown_flag = check_flag((*it)[i]);
                else if ((*it)[i] == USER_I && user->getBoolI() == false)
                {
                    user->setBoolI(true);
                    ret_modes += "i";
                }

                i++;
            }
        }
        else if ((*it)[0] == '-')
        {
            ret_modes += '-';

            while ((*it)[i])
            {
                if (check_flag((*it)[i]))
                    unknown_flag = check_flag((*it)[i]);
                if ((*it)[i] == USER_I && user->getBoolI() == true)
                {
                    user->setBoolI(false);
                    ret_modes += "i";
                }
                if ((*it)[i] == USER_A && user->getBoolA() == true)
                {
                    user->setBoolA(false);
                    ret_modes += "a";
                }
                if ((*it)[i] == USER_O && user->getBoolO() == true)
                {
                    if (args[args.size() - 1] == PASS_OPER)
                    {
                        user->setBoolO(false);
                        ret_modes += "o";
                        user->setOper(false);
                    }
                }
                i++;
            }
        }
    }
    // RPL_UMODEIS
    if (ret_modes.size() == 1)                                                                              // if modes have been deleted and no more modes are available
        return;
    user->message_reply(user->getFd(), user->getHostname(), CODE_RPL_UMODEIS + std::string(" ") + \
        command.getCommand() + std::string(" ") + user->getNickname() + std::string(" :") + ret_modes);     // RPL_UMODEIS
    if (unknown_flag == true)                                                                               // ERR_UMODEUNKNOWNFLAG
    {
        ret.push_back("MODE");
        return (command.reply(501, ret));
        ret.pop_back();
    }
}
