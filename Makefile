# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 02:24:53 by slahrach          #+#    #+#              #
#    Updated: 2022/04/14 03:29:46 by slahrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c philo.c utils.c error.c init.c ft_strcmp.c

OBJS = ${SRCS:.c=.o}


all : ${NAME}

${NAME} : ${OBJS}
	gcc ${OBJS} -o ${NAME}

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

%.o : %.c
	@${CC} ${CFLAGS} -c $<

.PHONY: clean all fclean re bonus