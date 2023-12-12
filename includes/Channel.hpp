/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:21:19 by alpascal          #+#    #+#             */
/*   Updated: 2022/11/22 11:43:55 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "All.hpp"


class Server;
class User;

class Channel
{
    public:
        // Constructors and destructor
		Channel();
		Channel(std::string name, Server* serv);
        // Channel( Channel const & src );
		~Channel();

        // Operators
        Channel     &operator=(const Channel &chan);

        // Setters
        void        set_password(std::string pwd);
        void		set_nicksChan(strSet nickChan);
        void        set_topic(std::string topic);
    
		// Getters
        userMapFd   get_fds(void) const;
        userMap     get_users(void) const;
        std::string get_chan_name(void) const;
        std::string get_password(void) const;
        int         get_usernb(void) const;
        strSet      get_nicksChan(void) const;
        std::string get_topic(void) const;


        // Members
        bool        isChanFull(void);
        void        sendToAll(std::string msg, User usr, Command &command);
        void        addUser(User *user, Command &command);
        void        delUser(User *user);
        void        addNick(std::string nick);
        void        delNick(std::string nick);
        void        kickUser(std::string chan, User *user, Command &command);

        void        print_channel_created(std::string name);
        void        print_channel_del(std::string name);

        

    private:
        std::string _name;
        std::string _password;
        std::string _topic;
        Server*     _serv;
        userMapFd   _fds;
        userMap     _users_chan;
        strSet      _nicks_chan;
        int         _usernb;
};

#endif/* ********************************************************* CHANNEL_H */