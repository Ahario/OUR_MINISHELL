/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:51:40 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/26 17:00:26 by lee-sung         ###   ########.fr       */
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

	cmd = NULL;
//	printf ("last_out%d\n", data->fd_out);
//	printf ("last_in%d\n", data->fd_in);
//	printf ("last_pi_extrance%d\n", data->pipe[0]);
	if (data->fd_in > 0)
		close(data->pipe[0]);
	else
		data->fd_in = data->pipe[0];
	data->pipe[0] = -1;
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
	{
		play_built(data, data->cmd->ac);
	}
	else
	{
		cmd = ft_executable(data, 0);
		arg = ft_arg_split(data->cmd);
		execve(cmd, arg, data->envp);
		ft_redirect_restore(data, 1);
		if (errno != 2 && errno != 14)
			printf("%s\n", strerror(errno));
		if (errno && errno != 2)
			exit(errno);
	}
	ft_redirect_restore(data, 1);
	exit(0);
}

void	first_cmd(t_data *data)
{
	char	*cmd;
	char	**arg;
	int		ret;

	ret = 0;
	cmd = NULL;
//	printf ("fd_out%d\n", data->fd_out);
//	printf ("fd_in%d\n", data->fd_in);
//	printf ("fd_pip_exit%d\n", data->pipe[1]);
	if (data->fd_out > 0)
	{
		close(data->pipe[1]);
	}
	else
	{
		data->fd_out = data->pipe[1];
	}
	data->pipe[1] = -1;
	ft_redirect_restore(data, 0);
	if (data->cmd && !check_built(data, data->cmd->ac))
	{
		play_built(data, data->cmd->ac);
	}
	else
	{
		cmd = ft_executable(data, 0);
		arg = ft_arg_split(data->cmd);
		ret = execve(cmd, arg, data->envp);
		free(cmd);
		free(arg);
		if (ret == -1)
			ret = 1;
		printf("%s\n", strerror(errno));
	}
	ft_redirect_restore(data, 1);
	exit(0);
}

void	child_cmd(t_data *data)
{
	char	*cmd;
	char	**arg;

	cmd = NULL;

//	printf ("chfd_in%d\n", data->fd_in);
//	printf ("chfd_ouu%d\n", data->fd_out);
//	printf ("chfd_pip_entrance%d\n", data->pipe[0]);
//	printf ("chfd_pip_entrance%d\n", data->pipe[1]);
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
		play_built(data, data->cmd->ac);
	else
	{
		cmd = ft_executable(data, 0);
		arg = ft_arg_split(data->cmd);
		execve(cmd, arg, data->envp);
		free(cmd);
		free(arg);
		exit(errno);
	}
	ft_redirect_restore(data, 1);
	exit(0);
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
	int	check;

	check = 0;

	tem = data;
	while (tem)
	{
		pid = fork();
		if (pid < 0)
			error_message(" Fork error\n", NULL);
		if (pid == 0)
		{
	//		printf ("fd_in%d\n", data->fd_out);
			ft_child_pipe(tem);
		}
		else
		{
			if (ft_parent_pipe(tem, pid))
				break ;
			tem = tem->next;
		}
	}
	waitpid(pid, &check, 0);
	if (errno == 2 && check)
		g_exit_number = 2;
	else if (check)
		g_exit_number = 1;
	else
		g_exit_number = 0;
	while(tem->prev)
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
//	data->fd_out = fd[1];
//	new->fd_in = fd[0];
//	new->fd_out = -1;
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
