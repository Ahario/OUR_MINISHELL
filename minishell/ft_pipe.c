/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:51:40 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 16:40:35 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void	ft_pipe_exec(t_data *data)
{
	char	*cmd;
	char	**arg;

	cmd = ft_executable(data, 0);
	if (!cmd)
		exit(g_exit_number);
	arg = ft_arg_split(data->cmd);
	execve(cmd, arg, data->envp);
	ft_redirect_restore(data, 1);
	if (errno != 2 && errno != 14)
	{
		error_message(cmd, NULL);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
	}
	if (errno == 13 || errno == 14 || errno == 20)
		exit(126);
}

void	last_cmd(t_data *data)
{
	if (data->fd_in > 0)
		close(data->pipe[0]);
	else
		data->fd_in = data->pipe[0];
	data->pipe[0] = -1;
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
	{
		play_built(data, data->cmd->ac);
		ft_redirect_restore(data, 1);
		if (g_exit_number == 1 || g_exit_number == 2)
			exit(1);
	}
	else
	{
		ft_pipe_exec(data);
	}
	exit(0);
}

void	first_cmd(t_data *data)
{
	if (data->fd_out > 0)
		close(data->pipe[1]);
	else
		data->fd_out = data->pipe[1];
	data->pipe[1] = -1;
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
	{
		play_built(data, data->cmd->ac);
		ft_redirect_restore(data, 1);
		if (g_exit_number == 1 || g_exit_number == 2)
			exit(1);
	}
	else
	{
		ft_pipe_exec(data);
	}
	exit(0);
}

void	child_cmd(t_data *data)
{
	if (data->fd_in > 0)
		close(data->prev->pipe[0]);
	else
		data->fd_in = data->prev->pipe[0];
	data->pipe[0] = -1;
	if (data->fd_out > 0)
		close(data->pipe[1]);
	else
		data->fd_out = data->pipe[1];
	data->pipe[1] = -1;
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
	{
		play_built(data, data->cmd->ac);
		ft_redirect_restore(data, 1);
		if (g_exit_number == 1 || g_exit_number == 2)
			exit(1);
	}
	else
	{
		ft_pipe_exec(data);
	}
	exit(0);
}

static void	ft_child_pipe(t_data *tem)
{
	if (tem && ft_strchr(tem->cmd->ac, ' '))
	{
		error_message(NULL, NULL);
		ft_putstr_fd(tem->cmd->ac, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (!tem->next)
		last_cmd(tem);
	else if (!tem->prev)
		first_cmd(tem);
	else if (tem->next)
		child_cmd(tem);
}

static int	ft_parent_pipe(t_data *tem, int pid)
{
	int	check;

	check = 0;
	(void)pid;
	close(tem->pipe[1]);
	if (!tem->next)
		return (1);
	return (0);
}

int	ft_pipe_fork(t_data **tem, int pid)
{
	if (pid < 0)
		error_message(" Fork error\n", NULL);
	if (pid == 0)
	{
		if ((*tem)->error)
			exit(1);
		ft_child_pipe(*tem);
	}
	else
	{
		if (ft_parent_pipe(*tem, pid))
			return (1);
		*tem = (*tem)->next;
	}
	return (0);
}

void	ft_pipe_cmd(t_data *data)
{
	int		pid;
	t_data	*tem;
	int		check;

	check = 0;
	tem = data;
	while (tem)
	{
		pid = fork();
		if (ft_pipe_fork(&tem, pid))
			break ;
	}
	waitpid(pid, &check, 0);
	g_exit_number = WEXITSTATUS(check);
	while (tem->prev)
	{
		close(tem->pipe[0]);
		tem = tem->prev;
	}
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
		if (tem->ac[0] == '|' && tem->type != SINQ && tem->type != DOUQ \
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
