# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 07:46:31 by jcervoni          #+#    #+#              #
#    Updated: 2023/02/10 15:19:46 by jcervoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=			ircserv

CC			=			c++
CPPFLAGS	=			-g3 -MMD -Wall -Werror -Wextra -std=c++98

INC			=			-I ./includes/\
						-I ./includes/numeric_replies/

SRCS_PATH	=			./sources/
SRCS_CHAN_PATH	= 		./channel/
SRCS_REQU_PATH	=		./request/
SRCS_RPLY_PATH	=		./numeric_replies/
OBJS_PATH	=			./objects/

SRCS 		= 			main.cpp \
						Server.cpp \
						ServerSocket.cpp \
						Socket.cpp \
						Client.cpp \
						sig.cpp \
						$(addprefix $(SRCS_REQU_PATH),	\
						Request.cpp \
						Request_serv_cmds.cpp \
						Request_chan_cmds.cpp \
						Request_utils.cpp \
						)\
						$(addprefix $(SRCS_CHAN_PATH),	\
						Channel.cpp \
						Channel_mode.cpp \
						chan_cmds.cpp \
						)\
						$(addprefix $(SRCS_RPLY_PATH),	\
						numeric_replies.cpp \
						numeric_errors.cpp \
						)


OBJS	 	=			$(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))
DEPS		=			${OBJS:.o=.d}

SILENT		=			--no-print-directory
all:			${NAME}

${NAME}:		${OBJS}
					${CC} ${CPPFLAGS} ${OBJS} -o ${NAME}
					@echo "Linking done"

${OBJS_PATH}%.o: $(SRCS_PATH)%.cpp
					@mkdir -p $(dir $@)
					${CC} ${CPPFLAGS} -c $< -o $@ $(INC)
clean:			
					@rm -rf ${OBJS_PATH}
					@echo " Objects cleaned !"

fclean:			clean
					@rm -rf ${NAME}

re:				fclean
					@make all ${SILENT}

-include ${DEPS}
.PHONY:			all clean fclean re