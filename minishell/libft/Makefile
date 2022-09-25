# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeo <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 12:29:08 by hyeo              #+#    #+#              #
#    Updated: 2021/12/01 15:50:28 by hyeo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_striteri.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strchr.c ft_strlcat.c ft_strrchr.c ft_strnstr.c\
	ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c\
	ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isascii.c
BONS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = ${SRCS:.c=.o}
BONSOBJS = ${BONS:.c=.o}
CC    = gcc
CFLAGS	= -Wextra -Wall -Werror
NAME	= libft.a

ifdef WITH_BONUS
	OBJ_FILES = ${OBJS} ${BONSOBJS}
else
	OBJ_FILES = ${OBJS}
endif

.c.o:		&{CC} &{CFLAGS} -c -o $@ $<

${NAME} : ${OBJ_FILES}
			ar -rc ${NAME} ${OBJ_FILES}

all:  ${NAME}

bonus : 
	make WITH_BONUS=1 all

clean:
	 rm -f ${OBJS}
	 rm -f ${BONSOBJS}

fclean :	clean
	rm -f ${NAME}

re : fclean all clean

.Phony: all bonus clean fclean re
