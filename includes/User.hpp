#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>

# include "All.hpp"

class Server;
class Channel;

class User
{
	private:
		int             		_fd;
		std::string     		_hostname;
		std::string     		_nickname;
		std::string     		_username;
		std::string     		_realname;
		std::string     		_mode;
		std::string				_oldnickname;
		std::string				_ip_address;
		time_t         		 	_ping_time;
		bool					_ping_request;
		std::string				_ping;
		chanMap					_channels;
		Server*					_serv;
		bool					_error_found;

		bool					_authentification;
		bool					_bool_nick;
		bool					_bool_user;
		bool					_bool_pass;
		bool					_bool_quit;

		bool					_mode_i;
		bool					_mode_a;
		bool					_mode_o;

		std::string				_inputStr;
		strQue					_recvQueue;
		strQue					_msgQueue;
		CmdQue					_cmdQueue;
		bool					_oldnickset;

		bool					_oper;
		strSet					_modes;


		std::vector<Command *>  _command;
		std::string				_buffer;

		static void				_initCmd(void);
		static CmdMap			_cmdMap;

		Params					_params;

	public:
		User();
		User(int fd, in_addr addr, Server *serv);
		User(User const &src);
		// User(int fd, struct sockaddr_in addr);
		~User();

		User			&operator=(const User &rhs);

		// Setters
		void            setNickname(std::string nickname);
		void            setOldNickname(std::string oldnick);
		void            setUsername(std::string username);
		void            setRealname(std::string realname);
		void			setHostname(std::string hostname);
		void            setMode(std::string mode);
		void			setPing(std::string ping);
		void			setPingrequest(bool val);
		void 			setPingtime(time_t time);

		void            setBoolAuthentification(bool val);
		void            setBoolNickname(bool val);
		void            setBoolUsername(bool val);
		void            setBoolPassword(bool val);
		void			setBoolQuit(bool val);

		void			setBoolI(bool val);
		void			setBoolA(bool val);
		void			setBoolO(bool val);

		void			setBuffer(std::string str);
		void			setErrorFound(bool val);
		void			setOldNick(bool val);

		void			setmsgQueue(strQue que);
		void			setOper(bool val);

		// Getters
		int             &getFd();
		time_t          &getPing_time();
		std::string     &getHostaddress();
		std::string     &getHostname();
		// std::string     getHost();
		std::string     &getNickname();
		std::string     &getUsername();
		std::string     &getRealname();
		std::string		&getIP();
		time_t			&getPingtime();
		bool			&getPingrequest();
		std::string		&getPing();
		strQue			&getrecvQueue();
		strQue			&getmsgQueue();
		CmdQue			&getCmdQueue();
		chanMap			getChannels();
		Server			*getServer() const;
		// Server			&getServer();
		CmdVec			&getUserCommands();
		CmdMap			&getCmdMap();

		bool			&getBoolAuthentification();
		bool			&getBoolNickname();
		bool			&getBoolUsername();
		bool			&getBoolPassword();
		bool			&getBoolQuit();

		bool			&getBoolI();
		bool			&getBoolA();
		bool			&getBoolO();

		std::string		getBuffer() const ;
		bool			getErrorFound() const ;
		bool			getOldNick() const;

		bool			getOper() const;


		// Methods
		std::string		buildPrefix(void);
		void			clearBuffer();

		void          	add_reply(std::string reply);
		void			add_replyTo(User *receiver, std::string reply);
		void			add_rcvQueue(std::string & msg);
		void			add_msgQueue(std::string & msg);
		void			add_cmdQueue(Command & cmd);
		void			clear_CmdQueue();
		void			clear_msgQueue();
		void			message_reply(int fd, std::string hostname, std::string message);
		
		void			show_modes();

		// void			user_registered(Command *command);
		void			free_command_vec(CmdVec &vec);
		void            authentificate(int fd, User *u);
		void			user_registered(Command *command);

		void			addChan(std::string name, Channel *chan);
		void            delChan(std::string name);

};

#endif /* ************************************************************ USER_H */