/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:58:08 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:00:10 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!cmd)
		exit(127);
	ft_redirect_restore(data, 0);
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
	{
		exit(126);
	}
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
