# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 07:46:31 by jcervoni          #+#    #+#              #
#    Updated: 2023/02/01 12:43:06 by jcervoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=			ircserv

CC			=			c++
CPPFLAGS	=			-g3 -MMD -Wall -Werror -Wextra -std=c++98

INC			=			-I ./includes/\
						-I ./includes/numeric_replies/

SRCS 		= 			$(addprefix $(SRCS_PATH),	\
						main.cpp \
						Server.cpp \
						ServerSocket.cpp \
						Socket.cpp \
						Client.cpp \
						Request.cpp \
						Channel.cpp \
						Channel_mode.cpp \
						./numeric_replies/numeric_replies.cpp \
						./numeric_replies/numeric_errors.cpp \
						)

SRCS_PATH	=			./sources/
OBJS_PATH	=			./objects/

OBJS	 	=			$(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))
DEPS		=			${OBJS:.o=.d}

SILENT		=			--no-print-directory
all:			${NAME}

${NAME}:		${OBJS}
					${CC} ${CPPFLAGS} ${OBJS} -o ${NAME}
					@echo "Linking done"

${OBJS_PATH}%.o: %.cpp
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