# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 02:24:53 by slahrach          #+#    #+#              #
#    Updated: 2022/04/16 02:50:00 by slahrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c philo.c utils.c messages.c init.c ft_strcmp.c

OBJS = ${SRCS:.c=.o}


all : ${NAME}

${NAME} : ${OBJS}
	@echo "objects created"
	@gcc ${OBJS} -o ${NAME}
	@echo "executable is ready"

clean :
	@rm -rf ${OBJS}
	@echo "objects are cleaned"

fclean : clean
	@rm -rf ${NAME}
	@echo "executable is removed"

re : fclean all

%.o : %.c
	@${CC} ${CFLAGS} -c $<

.PHONY: clean all fclean re bonus