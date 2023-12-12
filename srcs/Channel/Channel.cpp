/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:37:02 by alpascal          #+#    #+#             */
/*   Updated: 2022/11/23 13:49:24 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(){ }

Channel::Channel(std::string name, Server* serv) :  _name(name), _password(""), _topic("")
{
    _serv = serv;
    _usernb = 0;
    print_channel_created(name);
}

// Channel::Channel( Channel const & chan ):
//     _name(chan._name),
//     _password(chan._password),
//     _serv(chan._serv),
//     _fds(chan._fds),
//     _users_chan(chan._users_chan),
//     _usernb(chan._usernb)
// {
// }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
    print_channel_del(_name);
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel     &Channel::operator=(const Channel &chan)
{
    _name = chan._name;
    _password = chan._password;
    _serv = chan._serv;
    _fds = chan._fds;
    _users_chan = chan._users_chan;
    _usernb = chan._usernb;
	_nicks_chan = chan._nicks_chan;
    return (*this);
}

/*
** -------------------------------- GETTERS -----------------------------------
*/

userMapFd   Channel::get_fds(void) const { return (_fds); }
userMap     Channel::get_users(void) const { return (_users_chan); }
std::string Channel::get_chan_name(void) const { return (_name); }
std::string Channel::get_password(void) const { return (_password); }
int         Channel::get_usernb(void) const { return (_usernb); }
strSet      Channel::get_nicksChan(void) const { return (_nicks_chan); }
std::string Channel::get_topic(void) const { return (_topic); }

/*
** --------------------------------- SETTERS-----------------------------------
*/

void		Channel::set_password(std::string pwd) { _password = pwd; }
void		Channel::set_nicksChan(strSet nickChan) { _nicks_chan = nickChan; }
void        Channel::set_topic(std::string topic) { _topic = topic; }

/*
** --------------------------------- MEMBER -----------------------------------
*/

bool        Channel::isChanFull()
{
    if (_usernb >= MAX_IN_CHAN)
        return (true);
    return (false);
}

void        Channel::sendToAll(std::string msg, User usr, Command &command)
{
    userMap_it it = _users_chan.begin();
    strVec          rpl;

    while (it != _users_chan.end())
    {
        if (it->first != usr.getFd())
        {
            // rpl.push_back(usr.getNickname());
            // rpl.push_back(usr.getIP());
            rpl.push_back(get_chan_name());
            rpl.push_back(msg);
            command.replyTo(&usr, (*it).second, -5, rpl);
            // send(it->first, msg.c_str(), sizeof(char) * msg.size(), 0);
            // send(it->first, "\n", sizeof(char) * 1, 0);
        }
        it++;
    }
}

void        Channel::addUser(User *user, Command &command)
{
    int         tmp = user->getFd();
    std::string name = user->getNickname();
    strVec      rpl;

    (void)command;

    if (!(_users_chan.find(user->getFd()) != _users_chan.end()))
    {
        // sendToAll(name + " has just arrived on the channel !", *user, command); // tmp -> make a RPL        !!!!!!!!!!!!!!!!!!!!1
        // rpl.push_back(user->getNickname());
        // rpl.push_back(user->getIP());
        rpl.push_back(get_chan_name());
        // command.reply(-2, rpl);                 // User has joined      :nickname!~username@server_name JOIN :#chan_name
        _users_chan.insert(std::make_pair(tmp, user));
        user->addChan(_name, this);
        _usernb++;
        //  " << name << " has join " << get_chan_name() << std::endl; //  display
    }
}

void        Channel::delUser(User *user)
{
    // std::cout << "User " << user->getNickname() << " has left " << get_chan_name() << std::endl; // display
    _nicks_chan.erase(user->getNickname());
    _users_chan.erase(user->getFd());
    user->delChan(get_chan_name());
    _usernb--;
}

void        Channel::kickUser(std::string chan, User *user, Command &command)
{
    (void)command;
    // std::cout << "User " << user->getNickname() << " has been kicked from " << get_chan_name() << std::endl;  // displauy
    _nicks_chan.erase(user->getNickname());
    _users_chan.erase(user->getFd());
    user->delChan(chan);
    _usernb--;
}

void        Channel::addNick(std::string nick)
{
	_nicks_chan.insert(nick);
}

void       Channel::delNick(std::string nick)
{
	_nicks_chan.erase(nick);
}

void        Channel::print_channel_created(std::string name)
{
    std::cout << BYellow << "[ Channel ] : " << IYellow << "Channel " << name << " has been created " << Reset << "\n";
}

void        Channel::print_channel_del(std::string name)
{
    std::cout << BYellow << "[ Channel ] : " << IYellow << "Channel " << name << " has been deleted " << Reset << "\n";
}

