/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Params.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:17:45 by esommier          #+#    #+#             */
/*   Updated: 2022/09/26 17:46:37 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Params::Params()
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Params::~Params()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

// void			Params::set_param(std::string name, std::string value)
// {
// 	params[name] = value;
// }

// std::string		Params::get_param(std::string name)
// {
// 	return params[name];
// }

void        Params::set_port(std::string port)
{
    this->port = port;
}

void        Params::set_password(std::string pass)
{
    this->pass = pass;
}

std::string    Params::get_port()
{
    return (port);
}

std::string Params::get_password()
{
    return (pass);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */