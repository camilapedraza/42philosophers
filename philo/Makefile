# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/06 16:49:10 by mpedraza          #+#    #+#              #
#    Updated: 2026/02/16 20:20:42 by mpedraza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC 			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-pthread

SRCS		=	cleanup.c \
				init.c \
				main.c \
				monitor.c \
				parse.c \
				philosophers.c \
				print.c \
				utils.c
OBJS		= ${SRCS:%.c=%.o}
HEADERS		= philosophers.h		

all: 		${NAME}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ 

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME} 

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re