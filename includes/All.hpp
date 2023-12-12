/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   All.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:58:30 by julpelle          #+#    #+#             */
/*   Updated: 2022/11/22 18:03:38 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ALL_HPP
# define ALL_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <netinet/in.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string>
# include <sys/socket.h>
# include <sys/select.h>
# include <unistd.h>
# include <iostream>
# include <unistd.h>
# include <cstdlib>
# include <exception>
# include <sys/ioctl.h>
# include <sys/poll.h>
# include <sys/time.h>
# include <errno.h>
// # include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <poll.h>
# include <csignal>
# include <ctime>
# include <arpa/inet.h>


// Containers

# include <vector>
# include <map>

// Macros

# define BACKLOG		    5       // maximum length to which the queue of pending connections may grow
# define MAX_CLIENTS	    50
# define POLL_TIMEOUT		-1		// ms
# define PING_TIMEOUT		60		// ms
# define READ_BUFFER_SIZE	1025
# define LOCALHOST			"127.0.0.1"
# define MAX_IN_CHAN        4
# define MAX_CHANNELS       4
# define PASS_OPER          "psswrd"

// Server

# include "Params.hpp"
# include "Server.hpp"

// Users

# include "User.hpp"

// Commands

# include "Command.hpp"

// Channels

# include "Channel.hpp"

// Utils

# include "Colors.hpp"
# include "utilities.hpp"
# include "typedefs.hpp"

# endif