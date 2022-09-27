/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:46:05 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:01:42 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

char	*cmd_check(char *str, char **envp)
{
	char		**envp_path;
	int			i;

	i = 0;
	if (str[0] == '.')
		return (path_check(str));
	envp_path = ft_get_path(envp);
	while (envp_path[i])
	{
		if (!ft_strncmp(envp_path[i], str, ft_strlen(envp_path[i])))
			return (ft_cmd_return(str, envp_path[i], envp_path));
		i++;
	}
	free_split(envp_path);
	str = path_check(str);
	return (NULL);
}

char	*ft_executable(t_data *data, int i)
{
	struct stat	buf;
	char		*ret;
	char		**envp_path;

	if (ft_strchr("./~", data->cmd->ac[0]))
	{
		ret = ft_home_path(data);
		return (cmd_check(ret, data->envp));
	}
	envp_path = ft_get_path(data->envp);
	while (envp_path && envp_path[i])
	{
		ret = ft_strjoin_normal(envp_path[i], data->cmd->ac);
		if (!stat(ret, &buf))
		{
			free_split(envp_path);
			return (path_check(ret));
		}
		free(ret);
		i++;
	}
	if (envp_path)
		free_split(envp_path);
	cmd_error(data->cmd->ac, 1);
	return (NULL);
}

void	ft_one_cmd(t_data *data, int pid)
{
	char	*cmd;
	int		ret;

	cmd = ft_executable(data, 0);
	if (!cmd)
		return ;
	pid = fork();
	if (pid < 0)
	{
		free(cmd);
		error_message("error: fork error\n", NULL);
	}
	else if (pid == 0)
		ft_child_cmd(data, cmd);
	else
	{
		free(cmd);
		waitpid(pid, &ret, 0);
		g_exit_number = WEXITSTATUS(ret);
	}
}

int	ft_cmd_error(t_data *data)
{
	if (!data->cmd)
	{
		ft_signal();
		return (1);
	}
	if (data->error)
	{
		g_exit_number = 1;
		ft_signal();
		return (1);
	}
	if (data->cmd && ft_strchr(data->cmd->ac, ' '))
	{
		cmd_error(data->cmd->ac, 1);
		return (1);
	}
	return (0);
}

void	ft_cmd_start(t_data *data)
{
	ft_signal_cmd();
	if (!data->next)
	{
		if (ft_cmd_error(data))
			return ;
		if (data->cmd && !check_built(data, data->cmd->ac))
		{
			ft_redirect_restore(data, 0);
			play_built(data, data->cmd->ac);
			ft_redirect_restore(data, 1);
		}
		else
			ft_one_cmd(data, 0);
		ft_signal();
		return ;
	}
	else
	{
		ft_pipe_cmd(data);
	}
	ft_signal();
}
