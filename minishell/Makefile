SRCS = ft_exit.c\
	   ft_redir.c\
	   hs_parse12.c\
	   hs_parse8.c\
	   ft_exit2.c\
	   ft_redir2.c\
	   hs_parse13.c\
	   hs_parse9.c\
	   free_utils.c\
	   ft_export.c\
	   ft_redir3.c\
	   hs_parse14.c\
	   ft_cd.c\
	   ft_export2.c\
	   ft_redir4.c\
	   hs_parse15.c\
	   ft_cd2.c\
	   ft_export3.c\
	   ft_signal.c\
	   hs_parse2.c\
	   main.c\
	   ft_cmd.c\
	   ft_here_doc.c\
	   ft_signal2.c\
	   hs_parse3.c\
	   ft_cmd2.c\
	   ft_pipe.c\
	   ft_unset.c\
	   hs_parse4.c\
	   ft_cmd3.c\
	   ft_pipe2.c\
	   hs_parse.c\
	   hs_parse5.c\
	   ft_echo.c\
	   ft_pipe3.c\
	   hs_parse10.c\
	   hs_parse6.c\
	   ft_env.c\
	   ft_pwd.c\
	   hs_parse11.c\
	   hs_parse7.c

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
