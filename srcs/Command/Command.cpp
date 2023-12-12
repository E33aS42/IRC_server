/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:10:54 by esommier          #+#    #+#             */
/*   Updated: 2022/11/23 13:39:56 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ircCommands.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Command::Command(){ }

Command::Command(User* user, Server* serv, Params *params, std::string input):
												_input(input),
												_prefix(""),
												_command(""), 
												_trailer(""), 
												_client(user),
												_server(serv),
												_params(params)
{
	std::string delimiter(" ");
	size_t  	loc = 0;
	size_t  	i = 0;

	// 1. Look for prefix
	if (input[0] == ':')
	{
		loc = input.find(delimiter);
		_prefix = input.substr(0, loc);
		i += loc + 1;
	}
	
	// get input command line without prefix
	std::string tmp = input.substr(i);

	// get input command line without trailer & 4. save trailer if any
	if ((loc = input.substr(i).find(":")) != std::string::npos)
	{
		tmp = tmp.substr(0, loc);
		_trailer = input.substr(i + loc + 1);
	}

	while ((loc = tmp.find(delimiter)) != std::string::npos)
	{
		// std::cout << "loc: " << loc << ", npos: " << 
		_parameters.push_back(tmp.substr(0, loc));
		tmp.erase(0, loc + delimiter.length());
	}
	if (tmp[0] != '\r')
		_parameters.push_back(tmp);

	// 2. get command word
	_command = *(_parameters.begin());
	// put any command character upper case
	for (size_t j = 0; j < _command.length(); ++j)
		_command[j] = toupper(_command[j]);

	// 3. get parameters if any
	_parameters.erase(_parameters.begin());
}

Command::Command( const Command & src ):_input(src._input),
										_prefix(src._prefix),
										_command(src._command),
										_parameters(src._parameters),
										_trailer(src._trailer),
										_client(src._client),
										_server(src._server),
										_params(src._params)
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Command::~Command()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Command &				Command::operator=( Command const & rhs )
{
	_input = rhs._input;
	_prefix = rhs._prefix;
	_command = rhs._command;
	_parameters = rhs._parameters;
	_trailer = rhs._trailer;
	_client = rhs._client;
	_server = rhs._server;
	_params = rhs._params;
	return (*this);
}

/*
** -------------------------------- GETTERS -----------------------------------
*/

std::string					Command::getInput(void) const { return _input; }
std::string					Command::getPrefix(void) const { return _prefix; }
std::string					Command::getCommand(void) const { return _command; }

std::vector<std::string>	Command::getParameters(void) const { return _parameters; }

std::string					Command::getTrailer(void) const { return _trailer; }
User&						Command::getUser(void) const { return *_client; }
User*						Command::getUser(std::string nick) const { return _server->getUser_fromNick(nick); }
Server&						Command::getServer() const { return *_server; }
Params*						Command::getParams() { return _params; }

/*
** --------------------------------- MEMBER -----------------------------------
*/

std::string	Command::compose_replyTo(User *sender, User *receiver, int code, strVec args) // User* sender, User* receiver, 
{
	std::string		reply = ":";
	std::stringstream 	ss;
	
	// std::cout << "4- " << getCommand() << std::endl;
	// std::cout << "5- " << getServer().get_server_name() << std::endl;
	(void)receiver;
	if (code > 400)
	{
		reply += sender->getNickname();
		reply += " ";
		ss << code;
		reply += ss.str();
		reply += " ";
		reply += get_ERR_RPL(code, args);
		reply += "\r\n";
	}
	// else if (code > 0 && code < 400)
	// {
	// 	reply += receiver->buildPrefix();
	// 	reply += " ";
	// 	ss << code;
	// 	reply += ss.str();
	// 	reply += " ";
	// 	reply += get_ERR_RPL(code, args);
	//  reply += "\n";
	// }
	else if (code < 0)
	{
		// :old_nick!~username@server_ip_name_address NICK :new_nick
		reply += sender->buildPrefix();
		reply += " ";
		reply += get_ERR_RPL(code, args);
		reply += "\r\n";
	}
	return (reply);
}

std::string	Command::compose_reply(int code, strVec args) // User* sender, User* receiver, 
{
	std::string		reply = ":";
	std::stringstream 	ss;
	
	// std::cout << "4- " << getCommand() << std::endl;
	// std::cout << "5- " << getServer().get_server_name() << std::endl;

	if (code > 400)
	{
		reply += getServer().get_server_name();
		reply += " ";
		ss << code;
		reply += ss.str();
		reply += " ";
		reply += get_ERR_RPL(code, args);
		reply += "\r\n";
	}
	else if (code > 0 && code < 400)
	{
		// :liquid.oftc.net 353 asd = #test :asd opara_v25267525182197 tkob FloodServ zmanian Peetz0r
		reply += getServer().get_server_name();
		reply += " ";
		ss << code;
		reply += ss.str();
		reply += " ";
		reply += get_ERR_RPL(code, args);
	 	reply += "\r\n";
	}
	else if (code < 0)
	{
		// :old_nick!~username@server_ip_name_address NICK :new_nick
		reply += getUser().buildPrefix();
		reply += " ";
		reply += get_ERR_RPL(code, args);
		reply += "\r\n";
	}
	return (reply);
}

void						Command::replyTo(User *sender, User *receiver, int code, strVec args)
{
	// receiver->add_reply(compose_replyTo(sender, receiver, code, args));
	(void)sender;
	msgReply(receiver, code, args);

}

// void						Command::replyToAll(User *sender, userVec receivers, int code, strVec args)
// {
// 	for (userVec_it it = receivers.begin(); it != receivers.end(); it++)
// 		replyTo(sender, *it, code, args);
// }

void						Command::msgReply(User *receiver, int code, strVec args)
{
	std::string		reply = compose_reply(code, args);
	
	send(receiver->getFd(), reply.c_str(), reply.length(), 0);
}

void						Command::reply(int code, strVec args)
{
	_client->add_reply(compose_reply(code, args)); 
}


/*
** ------------------------------- NON-MEMBER ---------------------------------
*/

std::ostream &			operator<<( std::ostream & o, Command const & rhs )
{
	o << "Input: " << rhs.getInput() << std::endl;
	o << "Prefix : "  << rhs.getPrefix() << std::endl;
	o << "Command : " << rhs.getCommand() << std::endl;
	o << "Parameters : " << std::endl;
	strVec	tmp = rhs.getParameters();
	for (strVec_it it = tmp.begin(); 
		it != tmp.end(); ++it)
		o << "\t" << *it << std::endl;
	o << "Trailer : " << rhs.getTrailer() << std::endl;
	return o;
}

/* ************************************************************************** */