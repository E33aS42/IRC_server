/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:29:46 by esommier          #+#    #+#             */
/*   Updated: 2022/10/10 12:49:11 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "All.hpp"

int	check_args(int ac)
{
	if (ac == 1)
	{
		print_error("missing both arguments : there should be 2 arguments: <port> and <password>");
		return (-1);
	}
	else if (ac == 2)
	{
		print_error("missing one argument : there should be 2 arguments: <port> and <password>");
		return (-1);
	}
	else if (ac > 3)
	{
		print_error("too many arguments : there should be 2 arguments: <port> and <password>");
		return (-1);
	}
	return (1);
}

int	check_port(std::string port)
{
	int 							port_number;
	std::string::const_iterator		it;

	it = port.begin();
	while (it != port.end() && std::isdigit(*it)) 
		++it;
	if (it != port.end())
    {
        print_error("port must be an int");
		return (-1);
    }

	port_number = atoi(port.c_str());
	if (port_number < 1024 || port_number > 65535)
    {
        print_error("port number is invalid (it should be between 1024 and 65535)");
		return (-2);
    }
	return (1);
}

int	check_pwd(std::string pwd)
{
	if (pwd.length() < 4 || pwd.length() > 20)
    {
        print_error("password is invalid : must be more than 4 characters and less than 20 characters");
		return (-1);
    }
	return (1);
}

int	error_args(std::string port, std::string pwd)
{
	if((check_port(port) < 0) || (check_pwd(pwd) < 0))
		return (-1);
	return (1);
}

int	check_special(char c)
{
	if (c == 45 || c == 91 || (c >= 93 && c <= 96))
		return (1);
	return (0);
}