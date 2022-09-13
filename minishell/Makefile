SRCS = main.c \
	   ft_signal.c
LIBFT = -L ./libft -lft
LIBSRCS = libft
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS	= -Werror -Wall -Wextra
CFLAGS += -I $(LIBRD)/include -I ./libft/
#CFLAGS += -g -fsanitize=address
LIBRD = $(shell brew --prefix readline)
READLINE_OP	= -lreadline -L $(LIBRD)/lib


NAME = minishell

all :  $(NAME)

$(NAME): ${OBJS}
			make all -C $(LIBSRCS)/
			$(CC) $(CFLAGS) -o $@ $(OBJS) $(READLINE_OP) $(LIBFT)

clean:
	 rm -f ${OBJS}
	 make -C $(LIBSRCS) clean

.c.o:		&{CC} &{CFLAGS} -c $< -o $@

fclean :	clean
	make fclean -C $(LIBSRCS)
	rm -rf $(NAME)

re : fclean all clean

.PHONY: all bonus clean fclean re
