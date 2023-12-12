#ifndef SERVER_HPP
# define SERVER_HPP

# include "All.hpp"
# include "typedefs.hpp"

# define	READBUFFERSIZE		1025

class User;
class Channel;

class Server
{
	public:
		// Constructors and destructor
		Server();
		Server(Server const &serv);
		~Server();

		Server					&operator=(const Server &rhs);

		// Params
		Params					&getParams();
		pollVec					&getPolls(void);
		userMap					&getUserMap(void);
		userVec					&getUserVec(void);
		userVec					&getOldUserVec(void);
		strMap					&getCommandMap(void);

		// Getters
		struct sockaddr_in		get_serv_addr(void) const;
		socklen_t				get_serv_size(void) const;
		struct sockaddr_in		get_conn_addr(void) const;
		socklen_t				get_conn_size(void) const;
		int						get_serv_fd(void);
		int						get_serv_port(void);
		char					get_buff(void) const;
		std::string				get_hostname(void);
		std::string 			get_password(void);
		bool					get_running(void);
		chanMap					*get_channels(void);
		chanMap					&get_channels2(void);
		int						get_channb(void);

		int						get_activ_conn(void) const;
		std::string				get_server_name(void) const;
		strSet					get_users_nick(void);
		

		// Setters
		void					set_serv_addr(struct sockaddr_in addr);
		void					set_activ_conn(int conn);
		void					set_running(bool value);
		void					set_users_nick(strSet servNick);

		// Functions
		void					init_variables(void);
		void					create_socket(void);
		void					bind_socket(void);
		void					listen_socket(void);
		void					server_loop(void);
		void					init_server(void);
		void					run_server(void);
		void 					send_msg_to_all(int sender, char *s);
		void 					send_msg(int fd, std::string str);
		void					send_replies(int fd);
		void					send_ping(int fd);
		int						get_pong(int fd, std::string password);
		void					add_new_user(int client_fd, struct sockaddr_in serv_addr);
		void					add_userNick(std::string nick);
		void					del_userNick(std::string nick);
		void					add_client(int fd);
		void					remove_client(int fd);
		void					read_message(int fd, char *rbuf);
		void					auth_handler(int fd);
		void					message_handler(int fd);
		void					show_msg_queue(strQue que);
		void					ping(int fd);

		// Channels
		void					add_chan(Channel *chan);
		void        			del_chan(Channel *chan);
		bool					isServFull(void);
		void					addChan(std::string chan);
		void					delChan(std::string chan);
		strSet					getChanlist(void) const;
		void					setChanlist(strSet chans);

		// Print
		void					print_server(std::string msg);
		void					print_client(std::string msg, int client_number);
		void					print_client_conn(User *user);
		void					print_client_leave(User *user);
		void					print_client_input(User *user, std::string input);
		void					print_server_auth(User *user);
		void					show_user_map(userMap map);

		// Extra Users Functions
		User*					getUser_fromNick(std::string nick);
		void					delUser_fromNick(std::string nick);
		void					delUser_fromChan(chanMap *channels, std::string nick, User &user);
		

		
	private:		
		// Classes instances
		Params					_params;

		// Users variables
		userMap					_user_map;
		userMapFd				_user_fd;
		userVec					_users;
		strSet					_users_nick;
		userVec					_old_users;
		strMap					_cmd_map;

		// Server Variables
		int						_number_fds;
		fd_set					_fds;
		fd_set					_write_fds;
		fd_set					_read_fds;
		int						_sockfd;
		struct sockaddr_in  	_serv_addr;
		std::string				_server_name;
		socklen_t				_serv_size;
		struct sockaddr_in		_conn_addr;
		socklen_t				_conn_size;
		bool					_running;
		int						_activ_conn;
		int						_client_socket[MAX_CLIENTS];
		int 					_client;
		std::string				_hostname;
		std::string				_password;

		// Channel variables
		chanMap					_channels;
		strSet					_chanList;
		int						_channb;

};

extern bool *sigint;

#endif /* ********************************************************** SERVER_H */

