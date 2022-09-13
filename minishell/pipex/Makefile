# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeo <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 12:58:39 by hyeo              #+#    #+#              #
#    Updated: 2022/06/16 12:47:04 by hyeo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = pipex.c ft_split.c pipex_utils.c pipex_error.c pipex_utils2.c pipex_error2.c
OBJS = ${SRCS:.c=.o}
CC    = gcc
CFLAGS	= -Wextra -Wall -Werror
NAME	= pipex
.c.o:		&{CC} &{CFLAGS} -c -o $@ $<

${NAME} : ${OBJS}
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:  ${NAME}

clean:
	 rm -f ${OBJS}
	
fclean :	clean
	rm -f ${NAME}

re : fclean all clean

test: re
	./${NAME} a.c "ls -al" "wc -l" b.c

leaks: 
	leaks -atExit -- ./pipex

.Phony: all bonus clean fclean re
