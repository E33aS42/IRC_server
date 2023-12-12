# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esommier <esommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 11:21:59 by esommier          #+#    #+#              #
#    Updated: 2022/11/23 14:31:40 by esommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	ircserv

INC_DIR				=	includes

INC_FILES			=	All.hpp \
						Colors.hpp \
						Command.hpp \
						Params.hpp \
						Server.hpp \
						typedefs.hpp \
						User.hpp \
						utilities.hpp \
						
						

INC					=	$(addprefix $(INC_DIR)/, $(INC_FILES))
INCLUDE				=	-I $(INC_DIR)

SRCS_DIR			= 	srcs/
		
OBJ_DIR 			= 	objs
DEP_DIR				=	deps

CXX					= 	clang++
CXXFLAGS			= 	-Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP

VALGRIND			= 	valgrind -s
VALGRIND_FLAG		= 	--leak-check=full --show-leak-kinds=all --track-origins=yes

NEW_DIR				=	mkdir -p
RM					= 	rm -rf

#**********************************************************************************************#

ifndef ARG
	ARG = 6665 pass
endif

#**********************************************************************************************#

COMMAND_DIR			=	$(SRCS_DIR)Command/
COMMAND_IRC_DIR		= 	$(COMMAND_DIR)irc_cmd/
REPLIES_DIR			= 	$(COMMAND_DIR)replies/
SERVER_DIR			= 	$(SRCS_DIR)Server/
TOOLS_DIR			= 	$(SRCS_DIR)tools/
USER_DIR			= 	$(SRCS_DIR)User/
CHANNEL_DIR			= 	$(SRCS_DIR)Channel/


VPATH				=	$(COMMAND_DIR) \
						$(COMMAND_IRC_DIR) \
						$(REPLIES_DIR) \
						$(SRCS_DIR) \
						$(SERVER_DIR) \
						$(TOOLS_DIR) \
						$(USER_DIR) \
						$(CHANNEL_DIR) \
	

SRCS				=	Channel.cpp \
						check_args.cpp \
						Command.cpp \
						init_cmd.cpp \
						main.cpp \
						Params.cpp \
						ping_pong.cpp \
						ERR_msg.cpp \
						RPL_msg.cpp \
						Server.cpp \
						server_replies.cpp \
						Users.cpp \
						User_comm.cpp \
						utilities.cpp \
						PASS.cpp \
						JOIN.cpp \
						KICK.cpp \
						MODE.cpp \
						MOTD.cpp \
						NAMES.cpp \
						NICK.cpp \
						NOTICE.cpp \
						OPER.cpp \
						PART.cpp \
						PING.cpp  \
						PONG.cpp \
						PRIVMSG.cpp \
						QUIT.cpp \
						TOPIC.cpp \
						USER.cpp \
						WHOIS.cpp \
						
						

OBJS 				= 	$(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))
DEPS				= 	$(addprefix $(DEP_DIR)/,$(OBJS:.o=.d))

#**********************************************************************************************#

all:					$(NAME)

$(NAME):				$(OBJS)
						@${CXX} $(CXXFLAGS) -I$(INC_DIR) $(OBJS) -o $(NAME)
						@echo $(NAME) was created.

$(OBJ_DIR)/%.o: 		%.cpp $(INC)
						@$(NEW_DIR)  $(OBJ_DIR)
						@${CXX} $(CXXFLAGS)  -c $< -I$(INC_DIR) -o $@


valgrind: 				all
						$(VALGRIND) $(VALGRIND_FLAG) ./$(NAME) $(ARG)

#**********************************************************************************************#

clean:
						$(RM) $(OBJ_DIR)

fclean:					clean
						$(RM) $(NAME)

re:						fclean all

 -include 				$(DEP)

.PHONY:					all clean fclean re

