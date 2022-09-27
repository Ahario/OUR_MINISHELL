/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:51:40 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:46:23 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

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

void	ft_pipe_set(t_data *data, t_data *newdata)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	if (pipe(fd) == -1)
		error_message(" PIPE ERROR \n", NULL);
	data->pipe = fd;
	newdata->pipe = fd;
}

t_data	*ft_pipe_list_utill(t_data	*data, t_arg *tem)
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

t_data	*ft_pipe_list(t_data *data)
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
