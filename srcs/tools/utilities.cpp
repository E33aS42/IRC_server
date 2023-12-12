/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:23:02 by esommier          #+#    #+#             */
/*   Updated: 2022/11/15 09:16:03 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utilities.hpp"

void    print_str(std::string s1, std::string s2)
{
    std::cout << std::endl << s1 << " - " << s2 << std::endl << std::endl;
}

void    print_error(std::string error_msg)
{
    std::cout << Reset "Error : " Red << error_msg << Reset "\n"; 
}

void    print_debug(std::string var, std::string value)
{
	if (var.size() > 12)
    	std::cout << Blue << var << Cyan << " : " << value << Reset "\n";
	else if (var.size() > 6)
    	std::cout << Blue << var << Cyan << "\t : " << value << Reset "\n";
	else
    	std::cout << Blue << var << Cyan << "\t\t : " << value << Reset "\n"; 
}

void			print_dragon()
{
	std::cout << Blue " \t\t  ___------~~~~~~~~~~~----__         .:.         __----~~~~~~~~~~~------___   \n";
	std::cout << "\t\t ~~ ~--__          ......====\\~~    .:::.    ~~//====......          __--~ ~~ \n";
	std::cout << "\t\t         ~\\ ...::::~~~~~~  //|||    .:::::.    |||\\  ~~~~~~::::... /~         \n";
    std::cout << "\t\t 	      -~~\\_            //  |||***.(:::::).***|||  \\            _/~~-        \n";
	std::cout << "\t\t             ~\\_        // *******.:|\\^^^/|:.******* \\        _/~             \n";
	std::cout << "\t\t                \\      / ********.::(>: :<)::.******** \\      /                \n";
	std::cout << "\t\t                 \\   /  ********.::::\\|//::::.********  \\   /                 \n";
	std::cout << "\t\t                  \\ /   *******.:::::(o o):::::.*******   \\ /                  \n";
	std::cout << "\t\t                   /.   ******.::::'*|V_V|***`::.******   .\\                   \n";
	std::cout << "\t\t                     ~~--****.:::'***|___|*****`:.****--~~                     \n";
	std::cout << "\t\t                           *.::'***//|___|\\*****`.*                           \n";
	std::cout << "\t\t                           .:'  **/##|___|##\\**    .                           \n";
	std::cout << "\t\t                          .    (v(VVV)___(VVV)v)							     \n" Reset;
}

void			print_irc()
{
	std::cout << "\n\n\n";
	std::cout << "\t\t         /\\    \\                  /\\    \\                  /\\    \\                 \n";
	std::cout << "\t\t        /::\\    \\                /::\\    \\                /::\\    \\                \n";
	std::cout << "\t\t        \\:::\\    \\              /::::\\    \\              /::::\\    \\              \n";
	std::cout << "\t\t         \\:::\\    \\            /::::::\\    \\            /::::::\\    \\             \n";
	std::cout << "\t\t          \\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\          \n"; 
	std::cout << "\t\t           \\:::\\    \\        /:::/__\\:::\\    \\        /:::/  \\:::\\    \\         \n"; 
	std::cout << "\t\t           /::::\\    \\      /::::\\   \\:::\\    \\      /:::/    \\:::\\    \\        \n"; 
	std::cout << "\t\t  ____    /::::::\\    \\    /::::::\\   \\:::\\    \\    /:::/    / \\:::\\    \\       \n"; 
	std::cout << "\t\t /\\   \\  /:::/\\:::\\    \\  /:::/\\:::\\   \\:::\\____\\  /:::/    /   \\:::\\    \\  \n";     
	std::cout << "\t\t/::\\   \\/:::/  \\:::\\____\\/:::/  \\:::\\   \\:::|    |/:::/____/     \\:::\\____\\   \n";   
	std::cout << "\t\t\\:::\\  /:::/    \\::/    /\\::/   |::::\\  /:::|____|\\:::\\    \\      \\::/    /     \n"; 
	std::cout << "\t\t \\:::\\/:::/    / \\/____/  \\/____|:::::\\/:::/    /  \\:::\\    \\      \\/____/      \n"; 
	std::cout << "\t\t  \\::::::/    /                 |:::::::::/    /    \\:::\\    \\                     \n";
	std::cout << "\t\t   \\::::/____/                  |::|\\::::/    /      \\:::\\    \\                    \n";
	std::cout << "\t\t    \\:::\\    \\                  |::| \\::/____/        \\:::\\    \\                  \n";
	std::cout << "\t\t     \\:::\\    \\                 |::|  ~|               \\:::\\    \\                  \n";
	std::cout << "\t\t      \\:::\\    \\                |::|   |                \\:::\\    \\                 \n";
	std::cout << "\t\t       \\:::\\____\\               \\::|   |                 \\:::\\____\\               \n";
	std::cout << "\t\t        \\::/    /                \\:|   |                  \\::/    /                \n";
	std::cout << "\t\t         \\/____/                  \\|___|                   \\/____/                 \n";
	std::cout << "\t\t                                                                                   \n" Reset;
}

void			print_menu()
{
	print_dragon();
	print_irc();
}

void	sig_handler(int sig)
{
	(void)sig;
	// if (sig == SIGINT || sig == SIGQUIT)
	*sigint = false;
}

void	signals() 
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGPIPE, SIG_IGN);
}

std::string clean_string(std::string str)
{
	size_t i = 0;
	while (i < str.size())
	{
		if (std::isalnum(str[i]))
			i++;
		else
			break;
	}
	return (str.substr(0, i));
	// if (str.find('\r') != 0)
	// {
	// 	std::cout << "\\r at end of line\n";
	// 	std::cout << str.find('\r') << "\n";
	// 	return (str.substr(0, str.find("\r\n") - 1));
	// }
	// else if (str.find('\n') != 0)
	// {
	// 	std::cout << "\\n at end of line\n";
	// 	std::cout << str.find('\n') << "\n";
	// 	return (str.substr(0, str.find("\n") - 1));
	// }
	return (str);
}