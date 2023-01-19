# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 07:46:31 by jcervoni          #+#    #+#              #
#    Updated: 2023/01/19 10:39:10 by jcervoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=			myServ

CC			=			c++
CPPFLAGS	=			-MMD -Wall -Werror -Wextra -std=c++98

INC			=			-I ./includes/

SRCS 		= 			$(addprefix $(SRCS_PATH),	\
						main.cpp \
						Server.cpp \
						ServerSocket.cpp \
						Socket.cpp \
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