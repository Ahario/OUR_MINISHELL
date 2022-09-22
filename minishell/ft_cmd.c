/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:46:05 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/22 13:39:00 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	ft_list_len(t_arg *cmd)
{
	int	len;

	len = 0;
	while (cmd  && cmd->ac)
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
	ret = (char **)malloc(sizeof(char *) * (len));
	while (len-- > 0)
	{
		ret[i++] = cmd->ac;
//		printf ("!!!!!!!!!%s\n", cmd->ac);
//		printf ("!!!!!!!!!%d\n", len);
		cmd = cmd->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_child_cmd(t_data *data, char *cmd)
{
	char **arg;
//	int	i;

//	i = 0;
//	printf("data fd_in%d\n", data->fd_in);
//	printf("data fd_out%d\n", data->fd_out);
	ft_redirect_restore(data, 0);
	arg = ft_arg_split(data->cmd);
//	printf ("cmdcmd %s\n", cmd);
//	while (arg[i])
//		printf ("arg %s\n", arg[i++]);
	if (execve(cmd, arg, data->envp))
	{
		ft_redirect_restore(data, 1);
		free(cmd);
		exit (0);
	}
	ft_redirect_restore(data, 1);
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
	{
	//	ft_redirect_restore(data, 0);
	//	ft_redirect_restore(data, 1);
		return ;
	}
	ft_signal_cmd();
	if (!data->next)
	{
		printf ("test~~~~~~~~\n");
//		printf ("cmd_head_point %p\n", data);
//		printf ("cmd_head_cmd %s\n", data->cmd->ac);
//		printf ("cmd_head_export %s\n", data->envp[0]);
		cmd = data->cmd;
		if(cmd && ft_strchr(cmd->ac, ' '))
		{
			error_message("MINISHELL: ");
			printf("%s: command not found\n", cmd->ac);
			return ;
		}
		if(cmd && !check_built(data, cmd->ac))
		{
			ft_redirect_restore(data, 0);
			play_built(data, cmd->ac);
			ft_redirect_restore(data, 1);
		}
		else
			ft_one_cmd(data);
		ft_signal();
		return ;
	}
	ft_pipe_cmd(data);
	ft_signal();
}
