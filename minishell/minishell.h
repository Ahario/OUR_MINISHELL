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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_arg{
	char	*ac;
	int		type;
	struct s_arg	*prev;
	struct s_arg	*next;
}	t_arg;

typedef struct s_data{
	t_arg	*cmd;
	int		argc;
	char	**argv;
	char	**envp;
	int		fd_out;
	int		fd_in;
}	t_data;


enum	e_pars{
    NORM, SPCE, SINQ, DOUQ, BSLA, DOLR,
    PIPE, DPIP, SEMC, DSEM,
    RDRT, DRGT
};

void replace_parse(t_data *data);
int check_built(t_data *data, char *str);
void play_built(t_data *data, char *str);
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
//
void	ft_redir(t_data *data);
//cmd
void	ft_cmd_start(t_data *data);
//free_utils
void	free_split(char **str);
struct s_arg	*ft_list_del(t_arg *cmd);
//redir
void	ft_redir(t_data	*data);
void	ft_redirect_restore(t_data *data, int flag);
//here_doc
void	ft_here_doc(t_data *data, char *str, int *i, char *stop);
#endif
