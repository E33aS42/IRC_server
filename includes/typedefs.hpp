/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:28:25 by esommier          #+#    #+#             */
/*   Updated: 2022/11/17 13:17:01 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_HPP
# define TYPEDEFS_HPP

# include <string>
# include <vector>
# include <queue>
# include <iterator>
# include <map>
# include <algorithm>
# include <set>

class User;
class Command;
class Channel;

typedef	std::vector<pollfd>								pollVec;
typedef	pollVec::iterator								pollVec_it;
typedef std::vector<std::string>						strVec;
typedef strVec::iterator								strVec_it;
typedef std::map<std::string, void *>               	strMap;
typedef strMap::iterator         						strMap_it;
typedef std::set<std::string>                           strSet;
typedef strSet::iterator         						strSet_it;
typedef std::vector<User *>	                        	userVec;
typedef userVec::iterator								userVec_it;
typedef std::set<Channel *>                             chanSet;
typedef chanSet::iterator								chanSet_it;
typedef std::map<std::string, Channel *>                chanMap;
typedef chanMap::iterator         						chanMap_it;
typedef std::map<int, User *>							userMap;
typedef userMap::iterator								userMap_it;
typedef std::map<std::string, User *>					nickMap;
typedef nickMap::iterator								nickMap_it;
typedef std::map<int, User>								userMapFd;
typedef userMapFd::iterator								userMapFd_it;
typedef std::map<std::string, void (*)(Command&)>		CmdMap;
typedef CmdMap::iterator  							    CmdMap_it;
typedef std::map<int, strVec>							rplMap;
typedef std::queue<std::string>							strQue;
typedef std::vector<Command *>                          CmdVec;
typedef CmdVec::iterator                                CmdVec_it;
typedef std::queue<Command> 							CmdQue;

# include "Command.hpp"
# include "User.hpp"

#endif