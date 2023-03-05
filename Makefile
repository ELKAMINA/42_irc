# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 07:46:31 by jcervoni          #+#    #+#              #
#    Updated: 2023/03/05 22:55:25 by jcervoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=			ircserv

CC			=			c++
CPPFLAGS	=			-g3 -MMD -Wall -Werror -Wextra -std=c++98

INC			=			-I ./includes/

SRCS_PATH		=		./sources/
SRCS_CHAN_PATH	= 		./channel/
SRCS_CLTS_PATH	=		./client/
SRCS_REQU_PATH	=		./request/
SRCS_SERV_PATH	=		./server/
SRCS_UTLS_PATH	=		./utils/
SRCS_RPLY_PATH	=		./numeric_replies/
SRCS_MARV_PATH	=		./bot/
OBJS_PATH		=		./objects/

SRCS 		= 			main.cpp \
						$(addprefix $(SRCS_CHAN_PATH),	\
						Channel.cpp \
						Channel_cmds.cpp \
						Channel_mode.cpp \
						)\
						$(addprefix $(SRCS_CLTS_PATH),	\
						Client.cpp \
						)\
						$(addprefix $(SRCS_REQU_PATH),	\
						Request.cpp \
						Request_utils.cpp \
						Request_cmds_chan.cpp \
						Request_cmds_serv.cpp \
						)\
						$(addprefix $(SRCS_SERV_PATH),	\
						Server.cpp \
						server_init.cpp \
						server_connection_manager.cpp \
						server_request_manager.cpp \
						)\
						$(addprefix $(SRCS_UTLS_PATH),	\
						request_utils.cpp \
						utils.cpp \
						signal.cpp \
						)\
						$(addprefix $(SRCS_RPLY_PATH),	\
						numeric_replies.cpp \
						numeric_errors.cpp \
						)\
						$(addprefix $(SRCS_MARV_PATH),	\
						Marvin.cpp \
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
