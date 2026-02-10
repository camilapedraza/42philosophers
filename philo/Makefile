# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/06 16:49:10 by mpedraza          #+#    #+#              #
#    Updated: 2026/02/10 20:25:20 by mpedraza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC 			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-pthread

SRCS		=	main.c \
				routine.c \
				monitor.c \
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