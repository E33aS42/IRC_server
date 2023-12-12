/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:26:34 by esommier          #+#    #+#             */
/*   Updated: 2022/11/02 14:44:42 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

# include "All.hpp"

//print
void			print_dragon();
void			print_irc();
void			print_menu();
void	    	print_str(std::string s1, std::string s2);
void	    	print_error(std::string error_msg);
void	    	print_debug(std::string var, std::string value);

// Checks
int		    	check_args(int ac);
int		    	check_port(std::string port);
int				check_pwd(std::string pwd);
int				error_args(std::string port, std::string pwd);
int	            check_letter(char c);
int	            check_digit(char c);
int	            check_special(char c);

// Command Utils

std::string 	generate_ping(const int len);
int				check_pong(char *command, std::string password);
std::string     clean_string(std::string str);
void			signals();
void			sig_handler(int sig);

#endif 
