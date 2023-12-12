/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:30:29 by esommier          #+#    #+#             */
/*   Updated: 2022/11/22 21:34:56 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "All.hpp"

bool	*sigint;

int main(int ac, char **av)
{
	try
	{
		Server	server = Server();

		if (check_args(ac) < 0)
			exit(1);
		server.getParams().set_port(av[1]);
		server.getParams().set_password(av[2]);

		if (error_args(server.getParams().get_port(), server.getParams().get_password()) < 0)
			exit(1);
		server.init_server();
		server.run_server();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}
