/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:46:05 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/17 01:41:19 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

char	**ft_arg_split(t_arg *cmd)
{
	char	**ret;
	int		len;
	t_arg	*start;
	int		i;

	start = cmd;
	len = 0;
	i = 0;
	while (start->next)
	{
		start = start->next;
		len++;
	}
	ret = (char **)malloc(sizeof(char *) * len + 1);
	while (len-- >= 0)
	{
		ret[i++] = cmd->ac;
		printf ("!!!!!!!!!%s\n", cmd->ac);
		cmd = cmd->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_child_cmd(t_data *data, char *cmd)
{
	char **arg;
	int	i;

	i = 0;
	arg = ft_arg_split(data->cmd);
	printf ("cmd %s\n", cmd);
	while (arg[i])
		printf ("arg %s\n", arg[i++]);
	if (execve(cmd, arg, data->envp))
	{
		free(cmd);
		exit (0);
	}
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
	val = find_value(envp[i]);
	j = 0;
	i = 0;
	if(val)
	{
		ret = ft_split(val, ":");
		while(ret[j])
		{
			ret[j] = ft_strjoin_free(ret[j], ft_strdup("/"));
			j++;
		}
		free(val);
		return (ret);
	}
	return (NULL);

}

char	*ft_executable(t_data *data)
{
	struct stat	buf;
	char		*ret;
	char		**envp_path;
	int			i;

	if (ft_strchr("./~" , data->cmd->ac[0]))
	{
		ret = ft_home_path(data);
		if (ret && stat(ret, &buf))
		{
			free(ret);
			ret = NULL;
		}
		return (ret);
	}
	i = 0;
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
	return (NULL);
}


void	ft_one_cmd(t_data *data)
{
	char	*cmd;
	int		pid;
	int		ret;

	cmd = ft_executable(data);
	if (!cmd)
	{
		error_message("MINISHELL: ");
		printf("%s: command not found\n", data->cmd->ac);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		free(cmd);
		error_message("fork error\n");
	}
	else if (pid == 0)
		ft_child_cmd(data, cmd);
	else
	{
		free(cmd);
		waitpid(pid, &ret, 0);
	}



}

void	ft_cmd_start(t_data *data)
{
	t_arg	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return ;
	if (ft_strchr(cmd->ac, ' '))
	{
		error_message("MINISHELL: ");
		printf("%s: command not found\n", cmd->ac);
		return ;
	}
	if(!check_built(data, cmd->ac))
	{
		//ft_redirect_restore(data, 0);

	}
	else
		ft_one_cmd(data);
	return ;
}
