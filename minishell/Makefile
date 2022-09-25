SRCS = main.c \
	   ft_signal.c\
	   ft_exit.c\
	   ft_env.c\
	   ft_export.c\
	   ft_unset.c\
	   ft_pwd.c\
	   ft_cd.c\
	   ft_echo.c\
	   ft_redir.c\
	   free_utils.c\
	   ft_cmd.c\
	   ft_here_doc.c\
	   ft_pipe.c
LIBFT = -L ./libft -lft
LIBSRCS = libft
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS	= -Werror -Wall -Wextra # -g3 -fsanitize=address
CFLAGS += -I $(LIBRD)/include -I ./libft/
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
