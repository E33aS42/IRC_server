/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:23:10 by julpelle          #+#    #+#             */
/*   Updated: 2022/11/23 14:30:56 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User():	_hostname("IRC server"),
				_nickname(""),
				_username(""),
				_ip_address (LOCALHOST),
				_ping_request(false),
				_ping(""),
				_error_found(0),
				_authentification(false),
				_bool_nick(false), 
				_bool_user(false), 
				_bool_pass(false),
				_bool_quit(false),
				_mode_i(false),
				_mode_a(false),
				_mode_o(false),
                _inputStr(""),
				_oldnickset(0),
				_oper(false),
				_buffer("")
{
    _initCmd();    
}

User::User(int fd, in_addr addr, Server *serv): _fd(fd),
												_hostname("IRC server"),
												_nickname(""), 
                                                _username(""),
												_ip_address (LOCALHOST),
												_ping_request(false),
                                                _ping(""),
												_error_found(0),
												_authentification(false),
												_bool_nick(false), 
                                                _bool_user(false), 
                                                _bool_pass(false),
												_bool_quit(false),
												_mode_i(false),
												_mode_a(false),
												_mode_o(false),
												_inputStr(""),
												_oldnickset(0),
												_oper(false),
												_buffer("")												
{
    (void)addr;
	_serv = serv;
	_initCmd();
}


User::User(User const &src) { *this = src; }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

User::~User()
{
	// remove user and channels
	// std::cout << "***** User destructor *****" << std::endl;
	std::string nick = getNickname();
	chanMap		channels = getChannels();
	for (chanMap_it it = channels.begin(); it != channels.end(); it++)
	{
		(*it).second->get_nicksChan().erase(getNickname());
		(*it).second->get_users().erase(getFd());
	}
	channels.clear();
	if (!(nick.empty()))
		getServer()->del_userNick(nick);
	//close(getFd());
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

User			&User::operator=(const User &rhs)
{
	if (this == &rhs)
		return (*this);
    _fd = rhs._fd;
    _hostname = rhs._hostname;
    _nickname = rhs._nickname;
	_oldnickset = rhs._oldnickset;
    _username = rhs._username;
    _realname = rhs._realname;
	_oper = rhs._oper;
    _mode = rhs._mode;
    _oldnickname = rhs._oldnickname;
    _ip_address = rhs._ip_address;
    _ping_time = rhs._ping_time;
    _ping_request = rhs._ping_request;
    _ping = rhs._ping;
    _serv = rhs._serv;
	_channels = rhs._channels;
    return (*this);
}

/*
** -------------------------------- Setters --------------------------------
*/

void            User::setNickname(std::string nickname) { _nickname = nickname; }
void            User::setOldNickname(std::string oldnick) { _oldnickname = oldnick; }
void            User::setUsername(std::string username) { _username = username; }
void            User::setRealname(std::string realname) { _realname = realname; }
void			User::setHostname(std::string hostname) { _hostname = hostname; }
void            User::setMode(std::string mode) { _mode = mode; }
void			User::setPing(std::string ping) { _ping = ping; }
void			User::setPingrequest(bool val) { _ping_request = val; }
void 			User::setPingtime(time_t time) { _ping_time = time; }

void            User::setBoolAuthentification(bool val) { _authentification = val; }
void            User::setBoolNickname(bool val) { _bool_nick = val; } 
void            User::setBoolUsername(bool val) { _bool_user = val; }
void            User::setBoolPassword(bool val) { _bool_pass = val; }
void			User::setBoolQuit(bool val) { _bool_quit = val; }

void			User::setBoolI(bool val) { _mode_i = val; }
void			User::setBoolA(bool val) { _mode_a = val; }
void			User::setBoolO(bool val) { _mode_o = val; }

void			User::setBuffer(std::string str) { _buffer = str; }
void			User::setErrorFound(bool val) { _error_found = val; }
void			User::setOldNick(bool val) { _oldnickset = val; }

void			User::setmsgQueue(strQue que) { _msgQueue = que; }
void			User::setOper(bool val) { _oper = val; }

/*
** -------------------------------- Getters --------------------------------
*/

int             &User::getFd() { return (_fd); }
time_t          &User::getPing_time() { return (_ping_time); }
std::string     &User::getHostname() { return (_hostname); }
std::string     &User::getNickname() { return (_nickname); }
std::string     &User::getUsername() { return (_username); }
std::string     &User::getRealname() { return (_realname); }
std::string     &User::getIP() { return _ip_address; }
time_t          &User::getPingtime() { return _ping_time; }
bool            &User::getPingrequest() { return _ping_request; }
std::string     &User::getPing() { return _ping; }
strQue			&User::getrecvQueue() {return _recvQueue; }
strQue			&User::getmsgQueue() {return _msgQueue; }
CmdQue			&User::getCmdQueue() {return _cmdQueue; }
chanMap         User::getChannels() {return _channels;}
Server          *User::getServer() const {return _serv;}
CmdVec			&User::getUserCommands() { return _command; }
CmdMap			&User::getCmdMap() { return _cmdMap;}

bool			&User::getBoolAuthentification() { return _authentification ; }
bool			&User::getBoolNickname() { return _bool_nick ; }
bool			&User::getBoolUsername()  { return _bool_user ; }
bool			&User::getBoolPassword() { return _bool_pass ; }
bool			&User::getBoolQuit() { return _bool_quit ; }

bool			&User::getBoolI() { return _mode_i; }
bool			&User::getBoolA() { return _mode_a; }
bool			&User::getBoolO() { return _mode_o; }

std::string		User::getBuffer() const { return _buffer ; }
bool			User::getErrorFound() const { return _error_found; }
bool			User::getOldNick() const { return _oldnickset; }
bool			User::getOper() const { return (_oper); }

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string		User::buildPrefix(void) // :old_nick!~username@hostname
{
	std::string	prefix;
	if (getOldNick() && _oldnickname != "")
	{
		prefix = _oldnickname;
		setOldNick(false);
	}
	else
		prefix = _nickname;

	prefix += "!~" + _username;
	prefix += "@" + _hostname;
	return prefix;
}

void			User::clearBuffer()
{
	_buffer.clear();
}

void			User::free_command_vec(CmdVec &vec)
{
    for (CmdVec_it  it = vec.begin(); it != vec.end(); ++it)
        vec.erase(it);
    vec.clear();
}

void			User::add_rcvQueue(std::string & msg)
{
	_recvQueue.push(msg);
}

void			User::add_msgQueue(std::string & msg)
{
	_msgQueue.push(msg);
}

void			User::add_cmdQueue(Command & cmd)
{
	_cmdQueue.push(cmd);
}

void			User::clear_CmdQueue()
{
    CmdQue	empty;
	std::swap(_cmdQueue, empty);
}

void			User::clear_msgQueue()
{
    strQue	empty;
	std::swap(_msgQueue, empty);
}

void            User::authentificate(int fd, User *u)
{
    strVec	args;
	args.push_back(getNickname());
	args.push_back(getUsername());
	args.push_back(getHostname());

    message_reply(getFd(), getHostname(), CODE_RPL_WELCOME + std::string(" ") + getNickname() + RPL_WELCOME(args));
    message_reply(getFd(), getHostname(), CODE_RPL_YOURHOST + std::string(" ") + getNickname() + RPL_YOURHOST(getHostname(), "2.0"));
    message_reply(getFd(), getHostname(), CODE_RPL_CREATED + std::string(" ") + getNickname() + RPL_CREATED());
    message_reply(getFd(), getHostname(), CODE_RPL_MYINFO + std::string(" ") + getNickname() + RPL_MYINFO(getHostname(), "2.0"));
	
    motd(fd, u);
}

void			User::show_modes()
{
	if (_mode_i == true)
		std::cout << " I";
	if (_mode_a == true)
		std::cout << " A";
	if (_mode_o == true)
		std::cout << " O";
}

void		    User::message_reply(int fd, std::string hostname, std::string message)
{
	if (fd < 0)
		return ;
	std::string res = ":" + hostname + " " + message + "\r\n";
	send(fd, &res[0], res.length(), 0);
}

void			User::add_reply(std::string reply)
{
	_msgQueue.push(reply);	
}

void			User::add_replyTo(User *receiver, std::string reply)
{
	strQue	que = receiver->getmsgQueue();
	que.push(reply);
	receiver->setmsgQueue(que);	
}

void            User::addChan(std::string name, Channel *chan)
{
    _channels.insert(std::make_pair(name, chan));
}

void            User::delChan(std::string name)
{
    _channels.erase(name);
}



/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */