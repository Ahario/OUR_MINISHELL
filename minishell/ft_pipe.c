/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:51:40 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/25 21:23:10 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void	last_cmd(t_data *data)
{
	char	*cmd;
	char	**arg;
	int		ret;

	ret = 0;
	cmd = NULL;
//	printf("LAST\n");
//	printf ("data_in%d\n", data->fd_in);
//	printf ("data_out%d\n", data->fd_out);
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
		play_built(data, data->cmd->ac);
	else
	{
		cmd = ft_executable(data, 0);
		arg = ft_arg_split(data->cmd);
//		printf("lastcmd%s\n", cmd);
		execve(cmd, arg, data->envp);
//		printf("%s\n", strerror(errno));
		free(arg);
		free(cmd);
		if (ret == -1)
			ret = 1;
		close(data->pipe[1]);
		close(data->pipe[0]);
	}
	ft_redirect_restore(data, 1);
	exit(ret);
}

void	first_cmd(t_data *data)
{
	char	*cmd;
	char	**arg;
	int		ret;

	ret = 0;
	cmd = NULL;
//	printf("FIRST\n");
//	printf ("data_in%d\n", data->fd_in);
//	printf ("data_out%d\n", data->fd_out);
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
		play_built(data, data->cmd->ac);
	else
	{
		cmd = ft_executable(data, 0);
		arg = ft_arg_split(data->cmd);
//		printf("firscmd%s\n", cmd);
		ret = execve(cmd, arg, data->envp);
		free(cmd);
		free(arg);
		if (ret == -1)
			ret = 1;
//		printf("%s\n", strerror(errno));
		close(data->prev->pipe[1]);
	}
	close(data->pipe[1]);
	ft_redirect_restore(data, 1);
	exit(ret);
}

void	child_cmd(t_data *data)
{
	char	*cmd;
	char	**arg;
	int		ret;

	ret = 0;
	cmd = NULL;
//	printf("CHULD\n");
//	printf ("data_in%d\n", data->fd_in);
//	printf ("data_out%d\n", data->fd_out);
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
		play_built(data, data->cmd->ac);
	else
	{
		cmd = ft_executable(data, 0);
		arg = ft_arg_split(data->cmd);
//		printf("childcmd%s\n", cmd);
		execve(cmd, arg, data->envp);
		free(cmd);
		free(arg);
		if (ret == -1)
			ret = 1;
//		printf("%s\n", strerror(errno));
		close(data->prev->pipe[0]);
	}
	close(data->pipe[1]);
	ft_redirect_restore(data, 1);
	exit(ret);
}

static void	ft_child_pipe(t_data *tem)
{
	if (tem && ft_strchr(tem->cmd->ac, ' '))
	{
		error_message(NULL , NULL);
		ft_putstr_fd(tem->cmd->ac, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
//	printf ("play_child\n");
	if (!tem->prev)
	{
		close(tem->pipe[0]);
		first_cmd(tem);
	}
	else if (!tem->next)
		last_cmd(tem);
	else if (tem->next)
	{
		close(tem->pipe[0]);
		child_cmd(tem);
	}
}

static int	ft_parent_pipe(t_data *tem, int pid)
{
	int	check;

	check = 0;
	close(tem->pipe[1]);
	waitpid(pid, &check, 0);
	if (tem->prev)
		close(tem->prev->pipe[0]);
	if (!tem->next)
	{
		if (check && errno == 2)
			g_exit_number = 1;
		else if (check)
			g_exit_number = 127;
		else
			g_exit_number = 0;
		return (1);
	}
	return (0);
}

void	ft_pipe_cmd(t_data *data)
{
	int		pid;
	t_data	*tem;

	tem = data;
	while (tem)
	{
		pid = fork();
		if (pid < 0)
			error_message(" Fork error\n", NULL);
		if (pid == 0)
			ft_child_pipe(tem);
		else
		{
			if (tem->prev)
				close(tem->prev->pipe[0]);
			if (ft_parent_pipe(tem, pid))
				break ;
			tem = tem->next;
		}
	}
	close(tem->pipe[1]);
	close(tem->pipe[0]);
}

void	ft_pipe_set(t_data *data, t_data *new)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	if (pipe(fd) == -1)
		error_message(" PIPE ERROR \n", NULL);
	data->pipe = fd;
	new->pipe = fd;
	data->fd_out = fd[1];
	new->fd_in = fd[0];
	new->fd_out = -1;
}

static t_data	*ft_pipe_list_utill(t_data	*data, t_arg *tem)
{
	t_data	*new;

	new = NULL;
	new = (struct s_data *)malloc(sizeof(t_data));
	ft_set_data(new);
	new->cmd = tem;
	new->next = NULL;
	new->start = NULL;
	new->envp = data->envp;
	data->cmd = data->start;
	new->prev = data;
	data->next = new;
	ft_pipe_set(data, new);
	return (new);
}

struct s_data	*ft_pipe_list(t_data *data)
{
	t_arg	*tem;
	t_data	*head;

	data->start = NULL;
	head = data;
	if (!data->cmd)
		return (data);
	while (data->cmd)
	{
		tem = data->cmd;
		if (tem->ac[0] == '|' && tem->type != SINQ && tem->type != DOUQ\
				&& data->cmd->ac[1] != '|')
		{
			tem = ft_list_del_n(tem);
			if (!tem)
				break ;
			data = ft_pipe_list_utill(data, tem);
		}
		if (!data->start)
			data->start = data->cmd;
		data->cmd = data->cmd->next;
	}
	data->cmd = data->start;
	return (head);
}
