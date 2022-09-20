/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:13:19 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/20 17:47:49 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(2, "\b\b\b\b\b\b\b\b\b\b\b\b", 12);
	exit(1);
}

void	ft_signal_here(void)
{
	signal(SIGINT, ft_signal_cltr_c);
}

int	ft_child_here(int fd[2], char *stop)
{
	char *line;

	line = NULL;
	close(fd[0]);
	ft_signal_here();
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, stop) || !line)
			break;
		ft_putstr_fd(line, fd[1]);
		write(fd[1], "\n", 1);
	}
	if (stop)
		free(stop);
	if (line)
		free(line);
	close(fd[1]);
	exit(0);
}

void	ft_here_doc(t_data *data, char *str, int *i, char *stop)
{
	int	fd[2];
	int	fork_fd;
	int	check;

	while(str[*i] && str[*i] == ' ')
		*i += 1;
	if(str[*i])
		stop = ft_strdup(&str[*i]);
	if (!stop)
	{
		error_message("MINISHELL: syntax error near unexpected token 'newline'");
		return ;
	}
	check = 0;
	pipe(fd);
	fork_fd = fork();
	if (fork_fd < 0)
		error_message("fork error\n");
	else if (fork_fd == 0)
		ft_child_here(fd, stop);
	else
	{
		waitpid(fork_fd, &check, 0);
		if (data && data->fd_in > 0)
		{
			close(data->fd_in);
			data->fd_in = -1;
		}
		if (stop)
			free(stop);
		close(fd[1]);
		data->fd_in = fd[0];
		if (check)
			return ;
	}
	return ;
}
