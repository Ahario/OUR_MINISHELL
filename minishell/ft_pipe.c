/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:51:40 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/22 15:00:29 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/*char	*pipe_char(t_data *data)
{
	int	i;
	int	len;
	int		**ret;
	t_data	*head;

	len = 1;
	head = data;
	while (data->next)
	{
		data = data->next;
		i++;
	}
	ret = malloc(sizeof(int *) * i);
	i = 0;
	while (i < len - 1)
		ret[i++] = data->pipe;
	ret[i] = NULL;
}*/
void	last_cmd(t_data *data)
{
	char	*cmd;
	char	**arg;
	int		ret;

	ret = 0;
	cmd = NULL;
	printf ("fd_in %d\n" ,data->fd_in);
	printf ("fd_out %d\n" ,data->fd_out);
	printf ("fd_pipe_in %d\n" ,data->pipe[1]);
	printf ("fd_pipe_out %d\n" ,data->pipe[0]);
//	waitpid();
	ft_redirect_restore(data, 0);
	if(data->cmd && !check_built(data, data->cmd->ac))
		play_built(data, data->cmd->ac);
	else
	{
		cmd = ft_executable(data);
		arg = ft_arg_split(data->cmd);
		execve(cmd, arg, data->envp);
		free(cmd);
		close(data->pipe[1]);
		close(data->pipe[0]);
		ret = 1;
	}
//	sleep(10);
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
//	close(data->pipe[0]);
//	printf("!!11\n");
	ft_redirect_restore(data, 0);
//	printf("!!111\n");
	if(data->cmd && !check_built(data, data->cmd->ac))
		play_built(data, data->cmd->ac);
	else
	{
		cmd = ft_executable(data);
		arg = ft_arg_split(data->cmd);
		execve(cmd, arg, data->envp);
		free(cmd);
		close(data->pipe[1]);
		close(data->pipe[0]);
		ret = 1;
	}
	ft_redirect_restore(data, 1);
	exit(ret);
}

void	ft_pipe_cmd(t_data *data)
{
//	int	i;
	int	pid;
	t_data	*tem;
	int	check;
//	int	**pipe;

	tem = data;
	check = WNOWAIT;
//	pipe = pipe_char(data);
	while (tem)
	{
		pid = fork();
		if (pid < 0)
			error_message("Fork error\n");
		if (pid == 0)
		{
			if(tem && ft_strchr(tem->cmd->ac, ' '))
			{
				error_message("MINISHELL: ");
				printf("%s: command not found\n", tem->cmd->ac);
				return ;
			}
			if (tem->next)
			{
	//			printf("!!1\n");
				close(tem->pipe[0]);
				first_cmd(tem);
			}
			else if (!tem->next)
			{
				last_cmd(tem);
			}
		//	else if (tem->next)
		//		child_cmd(tem);
		}
		else
		{
			close(tem->pipe[1]);
			waitpid(pid, &check, 0);
			if (!tem->next)
				break;
			tem = tem->next;
		}
		close(tem->pipe[1]);
	}
}

void	ft_pipe_set(t_data *data, t_data *new)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	pipe(fd);
	data->pipe = fd;
	new->pipe = fd;
	data->fd_out = fd[1];
	new->fd_in = fd[0];
}

struct s_data	*ft_pipe_list(t_data *data)
{
	t_data	*new;
	t_arg	*tem;
	t_data	*head;

	new = NULL;
	data->start = NULL;
	head  = data;
	while (data->cmd)
	{
		tem = data->cmd;
		if (tem->ac[0] == '|' && tem->type != SINQ && tem->type != DOUQ)
		{
			tem = ft_list_del_n(tem);
			if (!tem)
				break;
	//		printf ("prev_cmd %s\n", data->cmd->prev->ac);
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
			data = new;
	//		printf ("new_cmd %s\n", data->cmd->ac);
		}
		if (!data->start)
			data->start = data->cmd;
		data->cmd = data->cmd->next;
	}
	data->cmd = data->start;
///	printf ("final_cmd %s\n", data->cmd->ac);
//	printf ("final_next_point %p\n", data->next);
//	printf ("head_cmd %s\n", head->cmd->ac);
//	printf ("head_prev_point %p\n", head->prev);
//	printf ("head_next_point %p\n", head->next);
//	printf ("head_next_cmd %s\n", head->next->cmd->ac);
	return (head);
}

