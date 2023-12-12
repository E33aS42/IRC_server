/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:10:59 by esommier          #+#    #+#             */
/*   Updated: 2022/11/11 13:09:37 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "All.hpp"
# include "typedefs.hpp"
# include "ircCommands.hpp"

class Server;
class User;
class Channel;

class Command
{

	public:
		// Constructors and destructor
		Command();
		Command(User* user, Server* serv, Params *params, std::string input);
		Command( Command const & src );
		~Command();

		// Operators
		Command &		operator=( Command const & rhs );

		// Getters
		std::string					getInput() const;
		std::string 				getPrefix() const;
		std::string 				getCommand() const;
		std::vector<std::string> 	getParameters() const;
		std::string 				getTrailer() const;
		User&						getUser() const;
		User*						getUser(std::string nick) const;
		Server&						getServer() const;
		Params*						getParams();

		// Members
		std::string					compose_reply(int code, strVec args); // User* sender, User* receiver
		std::string					compose_replyTo(User *sender, User *receiver, int code, strVec args);
		void						replyTo(User *sender, User *receiver, int code, strVec args = strVec());
		void						replyToAll(userVec receivers, int code, strVec args);
		void						reply(int code, strVec args = strVec());
		void						msgReply(User *receiver, int code, strVec args);

		// IRC commands

		// Replies
		

	private:
		std::string 				_input;
		std::string 				_prefix;
		std::string 				_command;
		std::vector<std::string> 	_parameters;
		std::string 				_trailer;
		User*						_client;
		Server*						_server;
		Params*						_params;

};

std::ostream &			operator<<( std::ostream & o, Command const & i );

#endif /* ******************************************************** Command_H */