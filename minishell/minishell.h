/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:41:17 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 18:09:07 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <sys/signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_arg
{
	char			*ac;
	int				type;
	struct s_arg	*prev;
	struct s_arg	*next;
}	t_arg;

typedef struct s_data{
	t_arg			*cmd;
	t_arg			*start;
	int				argc;
	char			**argv;
	char			**envp;
	int				fd_out;
	int				fd_in;
	int				*pipe;
	int				error;
	struct s_data	*prev;
	struct s_data	*next;
}	t_data;

enum	e_pars
{
	NORM,
	SPCE,
	SINQ,
	DOUQ,
	BSLA,
	DOLR,
	PIPE,
	DPIP,
	SEMC,
	DSEM,
	RDRT,
	DRGT,
	DOLLAR
};

int	g_exit_number;

//free_utils
void	free_split(char **str);
t_arg	*ft_list_del(t_arg *cmd);
t_arg	*ft_list_del_n(t_arg *cmd);

//ft_cd
char	*get_old_pwd(t_data *data);
void	put_old_pwd(t_data *data, char *old);
int		cd_error(char *val);
int		ft_get_pwd(t_data *data, char *key, int len, char *val);
void	ft_cd_pwd(t_data *data);
void	ft_cd_error(char *str);
void	ft_cd(t_data *data);
//ft_cmd
int		ft_list_len(t_arg *cmd);
char	**ft_arg_split(t_arg *cmd);
void	ft_child_cmd(t_data *data, char *cmd);
char	*ft_home_path(t_data *data);
char	**ft_get_path(char **envp);
void	cmd_error(char *str, int flag);
int		cmd_check_utill(char *str, char *envp_path);
char	*path_check(char *str);
char	*cmd_check(char *str, char **envp);
char	*ft_executable(t_data *data, int i);
void	ft_one_cmd(t_data *data, int pid);
void	ft_cmd_start(t_data *data);
char	*ft_cmd_return(char	*str, char *envp, char **envp_path);
//ft_echo
void	ft_echo(t_data *data, int flag);
//ft_env
int		check_env_visible(char *envp);
void	ft_env(char **envp);
//ft_exit
void	exit2(int flag);
int		count_total(t_arg *head);
void	error_message(char *str, char *des);
int		ft_atoi_exit(char *str, int i, int flag);
void	exit_numeric_check(char *str, int flag);
void	ft_exit(t_data *data);
void	exit_c_d(void);
//ft_export
char	*find_key(char *envp);
char	*find_value(char *envp);
char	**print_array(char **envp, int i);
void	ft_export_narg(char **envp, char *key, char *val);
int		ft_check_key(char *str, int flag);
char	*ft_change_val(char *envp, char *str, int len);
char	**ft_new_envp(char **tem, char *key, char *val);
char	**ft_change_envp(t_data *data, char *str, int len);
int		ft_check_export(t_data *data, char *key);
void	add_export(t_data *data, t_arg *tem);
void	ft_export(t_data *data);
//ft_here_doc
void	ft_signal_kill(int sig);
void	ft_signal_cltr_c(int sig);
void	ft_signal_here(void);
int		ft_child_here(int fd[2], char *stop);
int		ft_here_fork(t_data *data, char *stop, int check);
void	ft_here_doc(t_data *data, char *str, int *i, char *stop);
//ft_pipe
void	last_cmd(t_data *data);
void	first_cmd(t_data *data);
void	child_cmd(t_data *data);
void	ft_child_pipe(t_data *tem);
int		ft_parent_pipe(t_data *tem, int pid);
void	ft_pipe_cmd(t_data *data);
void	ft_pipe_set(t_data *data, t_data *newdata);
t_data	*ft_pipe_list_utill(t_data	*data, t_arg *tem);
t_data	*ft_pipe_list(t_data *data);
//ft_pwd
void	ft_envp_pwd(char **envp);
void	ft_pwd(t_data *data);
//ft_redir
int		check_str(char c, char *str);
int		ft_open_flag(t_data *data, char *filename, int flag);
int		filename_token(char *str, int *j);
int		filename_error(char *str, int *j);
int		infilename_check(t_data *data, char *str, int *i, int flag);
int		get_flag(char *str, t_arg *cmd);
void	symbol_del2(t_arg **cmd, char **str, int *i);
void	symbol_del(t_arg **cmd, char **str, int *i, int flag);
int		check_symbol(t_data *data, char *str, t_arg **prev, t_arg **cmd);
void	heredoc_error(t_arg **prev);
int		ft_start_heredoc(t_data *data, t_arg **cmd, char *str, t_arg **prev);
int		symbol_dollar(t_arg **cmd, t_arg **prev);
t_arg	*ft_symbol(t_data *data, t_arg *cmd, int sw);
int		ft_cmd_set(t_data *data);
int		ft_redir(t_data *r_data);
void	ft_redirect_restore2(int restore_in, int restore_out);
void	ft_redirect_restore(t_data *data, int flag);
void	infile_error_print(t_data *data, char *filename);
//ft_signal
void	ft_ctrl_c(int sig);
void	ft_signal(void);
void	ft_child_c(int sig);
void	ft_quit(int sig);
void	ft_signal_cmd(void);
//ft_unset
char	**unset_envp(char	**envp, int i);
void	ft_unset(t_data *data);
//hs_parse
void	ft_set_data(t_data *data);
t_data	*clean_all(t_data *data, char *ch);
void	ft_envp_change(char **envp);
char	**ft_malloc_envp(char **envp);
t_data	*ft_before(int argc, char *argv[], char **envp);
//hs_parse2
int		check_dp(char *ch, int i);
int		check_red(char *ch, int i);
int		for_bp(int flag, int i, char *ch);
void	before_parse(char *ch, t_data *data);
void	parse(char *ch, t_data *data);
//ft_parse3
int		check_dp(char *ch, int i);
int		check_red(char *ch, int i);
int		for_red(char *c, int f);
int		for_d_red(char *c);
void	increase_temp(char *temp, char *ch, int *k, int *l);
int		is_ws(char *str);
void	before_parse(char *ch, t_data *data);
void	parse(char *ch, t_data *data);
//ft_parse4
int		ft_charlen(char *str);
int		for_ft_find_red(char *c, int f);
int		ft_find_red(char *str);
int		check_dq_pair(char *str);
int		check_parse(char *ch, t_data *data);
//ft_parse5
int		get_temp_size(char *str);
void	if_replace_parse(char *str, char *temp, int *i, int *j);
char	*reset_replace_parse(int *i, int *j, char *str);
void	replace_parse(t_data *data);
int		check_flag(int flag, char *str);
//ft_parse6
char	*replace_dollar_sign_dq(char *st, t_data *data);
char	*get_full_path_dq(char *str, t_data *data);
void	add_i(int *i, char *str);
char	*replace_ds_parse(char *str, t_data *data, int flag);
char	*ft_strcpy_hth(char *str, int here, int there);
//ft_parse7
void	if_replace_ds_parse(int *k, char *c, char *t, t_data *data);
void	hs_check_for_space(int *j, int i, char *temp2, char *t);
void	if_replace_ds_parse_dq(int *k, char *c, char *t, t_data *data);
char	*get_full_exit(char *temp, char *str);
char	*hs_change_full_path_dq(char *str, t_data *data);
//ft_parse8
void	increase_both(int *i, int *j);
int		ft_charlen_export_free(char *str);
int		before_r_ds_parse(char *str, t_data *data);
int		for_replace_ds_parse(char *c, int k);
void	reset_replace_ds_parse(int *flag, int *i, int *k);
//ft_parse9
int		hs_for_only_ds(char *s, int i);
char	*hs_change_pid(char *str, int i);
char	*hs_give_dollar(void);
char	*replace_dollar_sign(char *st, t_data *data);
int		for_before_r_ds_parse(char *c);
//ft_parse10
int		search_mini_path(int j, char *envp[], char *str);
char	*backup_path(char *str);
char	*get_full_path(char *str, t_data *data);
char	*hs_change_exit_number(char *str, int i);
char	*hs_change_full_path(char *str, t_data *data);
//ft_parse11
void	assign_parse(t_data *data);
int		check_type(char *str, t_arg *curr);
void	parse_bigpart(t_data *data);
int		total_path_len(char *str);
char	*get_path(char *str);
//ft_parse12
void	assign_q(t_arg **head);
void	assign_dq(t_arg **head);
void	assign_redirect(t_arg **head);
void	assign_pipe(t_arg **head);
void	assign_norm(t_arg **head);
//ft_parse13
int		check_q(char *str);
int		check_dq(char *str);
int		check_redirect(char *str);
int		check_exitnumber(char *str);
int		check_pipe(char *str);
//ft_parse14
int		check_dq_flag(int flag);
int		if_char(char const *str);
void	add_back(t_arg **head, char *ch);
void	play_built(t_data *data, char *str);
int		check_built(t_data *data, char *str);
//ft_parse15
void	hs_create_empty(char *s);
void	ft_clean_all_utill(t_data **data);

#endif
