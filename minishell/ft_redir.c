/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:04:06 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:27:02 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/fcntl.h>

t_arg	*ft_symbol(t_data *data, t_arg *cmd, int sw)
{
	char	*str;
	t_arg	*prev;

	prev = NULL;
	while (cmd)
	{
		str = cmd->ac;
		sw = check_symbol(data, str, &prev, &cmd);
		if (sw)
		{
			if (sw == 4)
				if (ft_start_heredoc(data, &cmd, str, &prev))
					return (0);
			if (sw == 2)
				return (0);
		}
		else
		{
			if (symbol_dollar(&cmd, &prev))
				break ;
			cmd = cmd->next;
		}
	}
	data->cmd = prev;
	return (data->cmd);
}

int	ft_cmd_set(t_data *data)
{
	t_arg	*prev;
	t_arg	*head;

	if (!data->cmd)
		return (1);
	data->cmd->prev = NULL;
	head = data->cmd;
	while (data->cmd)
	{
		prev = data->cmd;
		data->cmd = data->cmd->next;
		if (data->cmd)
			data->cmd->prev = prev;
	}
	data->cmd = head;
	return (0);
}

int	ft_redir(t_data *r_data)
{
	t_data	*data;

	data = r_data;
	data->prev = NULL;
	data->next = NULL;
	if (ft_cmd_set(data))
		return (1);
	data = ft_pipe_list(data);
	while (data)
	{
		data->cmd = ft_symbol(data, data->cmd, 0);
		if (!data->cmd)
			return (1);
		if (!data->next)
			break ;
		data = data->next;
	}
	while (data->prev)
		data = data->prev;
	return (0);
}

void	ft_redirect_restore2(int restore_in, int restore_out)
{
	close(0);
	close(1);
	dup2(restore_in, 0);
	dup2(restore_out, 1);
	close(restore_in);
	close(restore_out);
}

void	ft_redirect_restore(t_data *data, int flag)
{
	static int	restore_in = -1;
	static int	restore_out = -1;

	if (data->fd_in < 0 && data->fd_out < 0 \
			&& restore_in < 0 && restore_out < 0)
		return ;
	if (!flag)
	{
		restore_in = dup(0);
		restore_out = dup(1);
		if (data->fd_in > 0)
		{
			dup2(data->fd_in, 0);
			close(data->fd_in);
			data->fd_in = -1;
		}
		if (data->fd_out > 0)
		{
			dup2(data->fd_out, 1);
			close(data->fd_out);
			data->fd_out = -1;
		}
	}
	else if (flag)
		ft_redirect_restore2(restore_in, restore_out);
}
