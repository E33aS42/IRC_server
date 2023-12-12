/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:05:42 by esommier          #+#    #+#             */
/*   Updated: 2022/09/29 11:06:06 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "All.hpp"

std::string 	generate_ping(const int len)
{
	char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string res;
	time_t		t;
	const char		*password = NULL;

    res.reserve(len);
	srand((unsigned) time(&t));
    for (int i = 0; i < len; ++i) {
        res[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
	res[0] = ':';
	password = res.c_str();
	std::cout << "Password : " << password << "\n";

	return (password);
}

int				check_pong(char *command, std::string password)
{
	char	*tmp;
	char	*pwd;

	tmp = const_cast<char *>(password.c_str());
	if (strncmp(command, "PONG", 4) == 0)
		;
	else
		return (-1);
	pwd = &command[5];
	if (strncmp(pwd, tmp, password.size() - 1) == 0)
		;
	else
		return (-1);
	return (1);
}