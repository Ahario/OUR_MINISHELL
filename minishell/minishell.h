#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
#include <sys/signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_arg{
	char	*ac;
	int		type;
	int		fd_in;
	int		fd_out;
	struct s_arg	*next;
}	t_arg;

typedef struct s_data{
	t_arg	*cmd;
	int		argc;
	char	**argv;
	char	**envp;
}	t_data;


enum	e_pars{
    NORM, SPCE, SINQ, DOUQ, BSLA, DOLR,
    PIPE, DPIP, SEMC, DSEM,
    RDRT, DRGT
};

void replace_parse(t_data *data);
//t_arg	*set_cmd(char *ch);
void	before_init(void);
void	ft_signal(void);
void	exit_C_d(void);

//exit
void	error_message(char *str);
void	ft_exit(t_arg *head);
int	exitcheck(t_arg *head);
void	exit2(void);
//env
void	ft_env(char **envp);
void	ft_export(t_data *data);
//export
char	*find_key(char *envp);
int	ft_check_key(char *str, int flag);
char	*find_value(char *envp);
//unset
void	ft_unset(t_data *data);
//pwd
void	ft_pwd(t_data *data);
//cd
void	ft_cd(t_data *data);
//
void	ft_echo(t_data *data);
#endif
