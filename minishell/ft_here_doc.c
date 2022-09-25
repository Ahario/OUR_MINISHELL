/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:13:19 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/25 16:56:33 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_signal_kill(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}

void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(1, "\b\b\b\b\b\b\b\b\b\b\b\b", 12);
	exit(1);
}

void	ft_signal_here(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, ft_signal_kill);
}

int	ft_child_here(int fd[2], char *stop)
{
	char	*line;

	line = NULL;
	close(fd[0]);
	ft_signal_here();
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, stop) || !line)
			break ;
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

static int	ft_here_fork(t_data *data, char *stop, int check)
{
	int	fd[2];
	int	fork_fd;

	pipe(fd);
	fork_fd = fork();
	if (fork_fd < 0)
		error_message("fork error\n", NULL);
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
			return (1);
	}
	return (0);
}

void	ft_here_doc(t_data *data, char *str, int *i, char *stop)
{
	while (str[*i] && str[*i] == ' ')
		*i += 1;
	if (str[*i])
		stop = ft_strdup(&str[*i]);
	if (!stop)
	{
		error_message(NULL, NULL);
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
		return ;
	}
	if (!ft_here_fork(data, stop, 0))
		g_exit_number = 0;
	else
		g_exit_number = 1;
}
