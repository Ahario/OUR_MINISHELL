/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:08:54 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:09:39 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_child_pipe(t_data *tem)
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
