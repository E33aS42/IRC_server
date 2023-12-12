/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:17:50 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 14:34:28 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() : 
					_users_nick(), 
					_server_name("IRC_server"),
					_running(true),
					_channels(),				 
					_channb(0)
{
	// std::cout << "***** Server starting *****" << std::endl;
	sigint = &_running;
}

Server::Server(Server const &serv) { *this = serv; }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/


Server::~Server()
{
	// std::cout << "***** Server destructor ***** " << std::endl;

	for (userMap_it it = _user_map.begin(); it != _user_map.end(); it++)
	{
		if ((*it).second)
			delete (*it).second;
		close((*it).first);
	}
	_user_map.clear();
	
	for(chanMap::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if ((*it).second)
			delete (*it).second;
	}
	_channels.clear();
	close(_client);
	close(_sockfd);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Server			&Server::operator=(const Server &rhs)
{
	if (this == &rhs)
		return (*this);
    _users_nick = rhs._users_nick;
    _hostname = rhs._hostname;
    _server_name = rhs._server_name;
	_running = rhs._running;
    _channels = rhs._channels;
    _channb = rhs._channb;

    _serv_addr = rhs._serv_addr;

    return (*this);
}

/*
** --------------------------------- GETTERS ----------------------------------
*/

Params					&Server::getParams(void) { return _params; }
userMap					&Server::getUserMap(void) { return _user_map; }
userVec					&Server::getUserVec(void) { return _users; }
userVec					&Server::getOldUserVec(void) { return _old_users; }
strMap					&Server::getCommandMap(void) { return _cmd_map; }

struct sockaddr_in		Server::get_serv_addr(void) const { return _serv_addr; }
socklen_t				Server::get_serv_size(void) const { return _serv_size; }
struct sockaddr_in		Server::get_conn_addr(void) const { return _conn_addr; }
socklen_t				Server::get_conn_size(void) const { return _conn_size; }
std::string				Server::get_hostname(void) { return _hostname;}
std::string 			Server::get_password(void) { return _password;}
bool					Server::get_running(void) { return _running; }
std::string				Server::get_server_name(void) const { return _server_name; }
chanMap					*Server::get_channels(void) { return &_channels; }
chanMap					&Server::get_channels2(void) { return _channels; }
int						Server::get_channb(void) { return _channb; }
strSet					Server::get_users_nick(void) { return _users_nick; }

/*
** --------------------------------- SETTERS ----------------------------------
*/

void					Server::set_serv_addr(struct sockaddr_in addr) { _serv_addr = addr; }
void					Server::set_activ_conn(int conn) { _activ_conn = conn; }
void					Server::set_running(bool value) { _running = value; }
void					Server::set_users_nick(strSet servNick) { _users_nick = servNick; }

/*
** --------------------------------- METHODS ----------------------------------
*/

// Channels

bool			Server::isServFull(void)
{
	if (_channb >= MAX_CHANNELS)
		return (1);
	return (0);
}

void			Server::add_chan(Channel *chan)
{
	_channels.insert(std::make_pair(chan->get_chan_name(), chan));
	_channb++;
	// std::cout << "channel " << chan->get_chan_name() << " was created !" << std::endl; // display
}

void        	Server::del_chan(Channel *chan)
{
	std::string name = chan->get_chan_name();
	_channb--;
    _channels.erase(name);
	delete chan;
	// std::cout << "channel " << name << " was deleted !" << std::endl; // display
}

void			Server::addChan(std::string chan)
{
	_chanList.insert(chan);
}

void			Server::delChan(std::string chan)
{
	_chanList.erase(chan);
}

strSet			Server::getChanlist(void) const
{
	return (_chanList);
}

void			Server::setChanlist(strSet chans)
{
	_chanList = chans;
}


// Others

void 			Server::send_msg_to_all(int sender, char *s)
{
	for (int fd = 0; fd <= MAX_CLIENTS; fd++)
	{
		if (FD_ISSET(fd, &_write_fds) && fd != sender)
			send(fd, s, strlen(s), 0);
	}
}

void			Server::create_socket(void)
{
	if ((_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket() failed");
		close(_sockfd);
		exit(1);
	}
	print_server("Socket created 👍🏻");
}

void			Server::init_variables(void)
{
	FD_ZERO(&_fds);
	_number_fds = 0;
	create_socket();
	FD_SET(_sockfd, &_fds);
	// std::cout << " Socket created" << std::endl;

	_serv_addr.sin_family = AF_INET;
	_serv_addr.sin_addr.s_addr = INADDR_ANY;
	_serv_addr.sin_port = htons(atoi(getParams().get_port().c_str()));
	_serv_size = sizeof(_serv_addr);
	_conn_size = sizeof(_conn_addr);
	_hostname = LOCALHOST;
	print_server("Server variables initialized 👍🏻");
}

void			Server::bind_socket(void)
{
	int run = 1;
	setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &run, sizeof(int));
	if (bind(_sockfd, (struct sockaddr *)&_serv_addr, (socklen_t)sizeof(_serv_addr)) < 0)
	{
		perror("bind() failed");
		close(_sockfd);
		exit(1);
	}
	print_server("Socket bound to port 👍🏻");
}

void			Server::listen_socket(void)
{
	if (listen(_sockfd, BACKLOG) < 0)
	{
		perror("listen() failed");
		close(_sockfd);
		exit(1);
	}
	print_server("Server listening to socket ... 🎧");
}

void			Server::init_server(void)
{
	init_variables();
	bind_socket();
	listen_socket();

	_number_fds = _sockfd;
	print_server("Server configured, ready to run ... 🏁");
}

void			Server::add_new_user(int client_fd, struct sockaddr_in serv_addr)
{
	User*	new_user = new User(client_fd, serv_addr.sin_addr, this);
	
	new_user->setHostname(inet_ntoa(serv_addr.sin_addr));
	print_client_conn(new_user);
	_user_map.insert(std::make_pair(client_fd, new_user));
}

void			Server::add_userNick(std::string nick)
{
	_users_nick.insert(nick);	
}

void			Server::del_userNick(std::string nick)
{
	if (!(nick.empty()))
		_users_nick.erase(nick);	
}

void					Server::add_client(int fd)
{
	socklen_t	addr_len;
	(void)fd;

	addr_len = sizeof(_serv_addr);
	
	if ((_activ_conn = accept(_sockfd, (struct sockaddr *)&_serv_addr, (socklen_t*)&addr_len)) < 0)
		exit(1);

	if (_number_fds < _activ_conn)
		_number_fds = _activ_conn;

	_client_socket[_activ_conn] = _client;
	_client++;
	
	add_new_user(_activ_conn, _serv_addr);

	userMap_it p; 
	p = _user_map.find(_activ_conn);
	FD_SET(_activ_conn, &_fds);				// add new active connection to fds set then reinitialize loop
}

void			Server::remove_client(int fd)
{
	std::string nick = _user_map[fd]->getNickname();
	print_client_leave(_user_map[fd]);

	chanMap		*channels = get_channels();
	strSet		nickChan;
	
	if (!(channels->empty()))
		delUser_fromChan(channels, nick, *_user_map[fd]);
	
	// if (!(nick.empty()))
	delUser_fromNick(nick);
	close(fd);
	FD_CLR(fd, &_fds);
}

void			Server::read_message(int fd, char *rbuf)
{
	User*	client = _user_map[fd];
	
	rbuf[strlen(rbuf)] = '\0';
	std::string buffer;
	buffer.assign(rbuf, strlen(rbuf));
	std::string input_buffer(client->getBuffer());
	client->clearBuffer();
	input_buffer += buffer;
	std::string split_buffer = "";
	
	while (!input_buffer.empty())
	{
		std::size_t	end_input = input_buffer.find("\n");
		if (end_input == input_buffer.npos)		// there are no matches for "\n"
		{
			client->setBuffer(input_buffer);	// we save incomplete input into buffer
			break;
		}
		
		/* check for "\r" */
		std::size_t	ignore_crlf = 1;
		if (end_input && input_buffer[end_input - 1] != '\r')
			ignore_crlf = 0;
		split_buffer = input_buffer.substr(0, end_input - ignore_crlf);

		client->add_rcvQueue(split_buffer);
		Command	newCmd(client, this, &(this->getParams()), split_buffer);
		client->add_cmdQueue(newCmd);
		
		input_buffer.erase(0, end_input + 1);
	}
}

void			Server::ping(int fd)
{
	if (fd != _sockfd)
	{
		User	*user = _user_map[fd];
		if (user->getPingrequest() && time(NULL) - user->getPing_time() > PING_TIMEOUT)
			remove_client(fd);
		else
		{
			if (user->getPing().size() == 0)
				user->setPing(generate_ping(8));
			user->setPingtime(time(NULL));
			send_ping(fd);
		}
	}

}

void			Server::auth_handler(int fd)
{
	User*		client = _user_map[fd];
	CmdQue		cmdQueue = client->getCmdQueue();
	std::string word;

	while(!(client->getBoolAuthentification()) && !(cmdQueue.empty()))
	{
		Command &cmd = cmdQueue.front();
		word = cmd.getCommand();
		if ((word == "NICK") 
		|| (word == "USER" && client->getBoolUsername() == false) 
		|| (word == "PASS" && client->getBoolPassword() == false) || (word == "QUIT" ))
		{
			print_client_input(client, word);
			client->getCmdMap()[cmd.getCommand()](cmd);
		}

		cmdQueue.pop();
		if (client->getBoolNickname() && client->getBoolPassword() && client->getBoolUsername())
		{
			client->setBoolAuthentification(true);
			client->authentificate(fd, client);
			print_server_auth(client);
		}
	}
}

void			Server::message_handler(int fd)
{
	User*		client = _user_map[fd];
	CmdQue		cmdQueue = client->getCmdQueue();

	if (client->getBoolAuthentification() == false)
		auth_handler(fd);
	else
	{
		while(!(cmdQueue.empty()))
		{
			Command &cmd = cmdQueue.front();

			if (client->getCmdMap().count(cmd.getCommand()))
			{
				print_client_input(client, cmd.getCommand());
				client->getCmdMap()[cmd.getCommand()](cmd);
			}
			else
			{
				strVec	args;
				args.push_back(cmd.getCommand());
				cmd.reply(421, args);		
			}
			cmdQueue.pop();
		}
	}
	client->clear_CmdQueue();
}

void 		Server::send_msg(int fd, std::string str)
{
	char *s = const_cast<char*>(str.c_str());
	if (FD_ISSET(fd, &_write_fds))
		send(fd, (char*)s, strlen(s), 0);	
}

void		Server::send_replies(int fd)
{
	User*	client = _user_map[fd];
	strQue	que = _user_map[fd]->getmsgQueue();

	while (!que.empty())
	{
		send_msg(fd, que.front());
		que.pop();
	}
	client->clear_msgQueue();
}

void	Server::show_msg_queue(strQue que)	// *** debug function ***
{
  while (!que.empty())
  {
    std::cout << que.front() << " " << std::endl;
    que.pop();
  }
  std::cout << std::endl;
}

void	Server::run_server(void)
{
	char		rbuf[READBUFFERSIZE];		// data buffer for reading
	
	_activ_conn = 0;
	_client = 0;
	_running = true;
	print_server("Server running ... 🏃🏻🏃🏼‍♀️");
	while (_running)
	{
		signals();
		_read_fds = _fds;
		_write_fds = _fds;
		if (select(_number_fds + 1, &_read_fds, &_write_fds, NULL, NULL) < 0)
		{
			if (!(*sigint))
			{
				_running = false;
				continue;
			}
			exit(1);
		}
		for(int i = 0; i <= _number_fds; i++)
		{

			if (!FD_ISSET(i, &_read_fds)) // check if fd i is in fd_set readfds, if not go to next fd
				continue ;
			if (i == _sockfd)	// current fd is listening socket
			{
				add_client(i);
				break ;
			}
			else	// current fd is active connection
			{
				signals();
				bzero(rbuf, READBUFFERSIZE - 1);
				int r = recv(i, rbuf, 1024, 0);
				userMap_it it = _user_map.find(i);
				if (it == _user_map.end() || (_user_map[i]->getBoolQuit() || r <= 0))
				{
					remove_client(i);
					break ;
				}
				else
				{
					read_message(i, rbuf);
					message_handler(i);
				}

			}
			// std::cout << "fd: " << i << std::endl << std::endl;			// *** debug line ***
			// std::cout << "recvQue : " << i << std::endl;					// *** debug line ***
			// show_msg_queue(_user_map[i]->getrecvQueue());				// *** debug line ***
			// std::cout << std::endl << "2 msgQue : " << i << std::endl;	// *** debug line ***
			// show_msg_queue(_user_map[i]->getmsgQueue());					// *** debug line ***
			send_replies(i);												
		}
	}
	print_server("Server closing");
}

void	Server::send_ping(int fd)
{
	if (!_user_map[fd]->getPingrequest())
	{
		send(fd, "PING ", sizeof("PING "), 0);
		send(fd, _user_map[fd]->getPing().c_str(), (size_t)_user_map[fd]->getPing().size(), 0);
		send(fd, "\r\n", sizeof("\r\n"), 0);
		_user_map[fd]->setPingrequest(true);
	}
}

int		Server::get_pong(int fd, std::string password)
{
	char	command[password.size()];

	int r = recv(fd, command, 1024, 0);
	if (r > 0)
	{
		FD_ISSET(fd, &_write_fds);
		if (check_pong(command, password) == 1)
			print_client("Authentification Successful", _client_socket[_activ_conn] + 1);
		else
			print_error("Authentification Failed");
	}
	return (1);
}


void		Server::print_server(std::string msg)
{
    std::cout << BPurple "[ Server ] : " << IPurple << msg << Reset "\n";
}

void		Server::print_client(std::string msg, int client_number)
{
    std::cout << BBlue "[ Client " << client_number << "] : " << Blue << msg << Reset "\n";
}

void		Server::print_client_conn(User *user)
{
    std::cout << BPurple "[ Server ] : " << Blue << "Client " << user->getFd() - 3 << " connected from " << user->getIP() << Reset "\n";
}

void		Server::print_client_leave(User *user)
{
    std::cout << BPurple "[ Server ] : " << Red << "Client " << user->getFd() - 3 << " left from " << user->getIP() << Reset "\n";
}

void		Server::print_client_input(User *user, std::string input)
{
    std::cout << BBlue "[ Client ] : " << ICyan << "Client " << user->getFd() - 3 << " sent " << input << " to server " << Reset "\n";
}

void		Server::print_server_auth(User *user)
{
	std::cout << BPurple "[ Server ] : " << IGreen << "Client " << user->getFd() - 3 << " authentificated from " << user->getIP() << Reset "\n";
}

void		Server::show_user_map(userMap map)
{
	std::cout << "\n ----- User Map ------- : size" << map.size() << "\n";
	for (userMap_it it = map.begin(); it != map.end(); ++it)
		std::cout << "fd : " << it->first << " | nickname : " << it->second->getNickname() << " \t| username : " << it->second->getUsername() << " \t|ping : " << it->second->getPing() << "\n";
	std::cout << "\n";
}


/* ************************************************************************** */