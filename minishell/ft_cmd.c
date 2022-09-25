/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:46:05 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/26 03:25:30 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <errno.h>
#include <string.h>

int	ft_list_len(t_arg *cmd)
{
	int	len;

	len = 0;
	while (cmd && cmd->ac)
	{
		cmd = cmd->next;
		len++;
	}
	return (len);
}

char	**ft_arg_split(t_arg *cmd)
{
	char	**ret;
	int		len;
	int		i;

	len = ft_list_len(cmd);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	while (len-- > 0)
	{
		ret[i++] = cmd->ac;
		cmd = cmd->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_child_cmd(t_data *data, char *cmd)
{
	char	**arg;

	ft_redirect_restore(data, 0);
	arg = ft_arg_split(data->cmd);
	execve(cmd, arg, data->envp);
	ft_redirect_restore(data, 1);
	if (errno != 2)
		ft_putstr_fd(strerror(errno), 2);
	if (errno && errno != 2)
		exit(errno);
	exit (1);
}

char	*ft_home_path(t_data *data)
{
	char	*ret;
	char	**envp;

	if (data->cmd->ac[1] == '.' && data->cmd->ac[2] == '\0')
		return (NULL);
	if (ft_strchr("./", data->cmd->ac[0]))
		return (ft_strdup(data->cmd->ac));
	envp = data->envp;
	while (envp && ft_strncmp(*envp, "HOME=", 5))
		envp++;
	if (envp)
	{
		ret = ft_strjoin_free(find_value(*envp), ft_strdup(&data->cmd->ac[1]));
		return (ret);
	}
	return (NULL);
}

char	**ft_get_path(char **envp)
{
	int		i;
	int		j;
	char	**ret;
	char	*val;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	val = find_value(envp[i]);
	j = 0;
	i = 0;
	if (val)
	{
		ret = ft_split(val, ":");
		while (ret[j])
		{
			ret[j] = ft_strjoin_free(ret[j], ft_strdup("/"));
			j++;
		}
		free(val);
		return (ret);
	}
	return (NULL);
}

static void	cmd_error(char *str, int flag)
{
	if (flag)
	{
		error_message(NULL, NULL);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (!flag)
	{
		error_message(NULL, NULL);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

static	int	cmd_check_utill(char *str, char *envp_path)
{
	int			j;
	char		*cmd;
	struct stat	buf;

	j = 0;
	while (envp_path[j] == str[j])
		j++;
	while (str[j] != '/')
		j++;
	cmd = ft_strdup(str);
	ft_strlcpy(cmd, str, j + 1);
	if (cmd && stat(cmd, &buf))
	{
		cmd_error(str, 0);
		free(str);
		free(cmd);
		return (1);
	}
	else
	{
		free(cmd);
		return (0);
	}
}

char	*cmd_check(char *str, char **envp)
{
	char		**envp_path;
	int			i;

	i = 0;
	if(str[0] == '.')
		return (str);
	envp_path = ft_get_path(envp);
	while (envp_path[i])
	{
		if (!ft_strncmp(envp_path[i], str, ft_strlen(envp_path[i])))
		{
			if (cmd_check_utill(str, envp_path[i]))
			{
				free_split(envp_path);
				return (NULL);
			}
			else
			{
				free_split(envp_path);
				return (str);
			}
		}
		i++;
	}
	free_split(envp_path);
	cmd_error(str, 0);
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
			return (ret);
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
		if (errno == 2 && ret)
			g_exit_number = 2;
		else if (ret)
			g_exit_number = 126;
		else
			g_exit_number = 0;
	}
}

void	ft_cmd_start(t_data *data)
{
	ft_signal_cmd();
	if (!data->next)
	{
		if (!data->cmd)
			return ;
		if (data->cmd && ft_strchr(data->cmd->ac, ' '))
		{
			cmd_error(data->cmd->ac, 1);
			return ;
		}
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
		ft_pipe_cmd(data);
	ft_signal();
}
