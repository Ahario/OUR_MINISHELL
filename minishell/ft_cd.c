/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 01:50:20 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/21 21:05:17 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_old_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] &&ft_strncmp(data->envp[i], "PWD", 3))
		i++;
	return(data->envp[i]);
}

void	put_old_pwd(t_data *data, char *old)
{
	int		i;
	char	*val;

	i = 0;
	while (data->envp[i] &&ft_strncmp(data->envp[i], "OLDPWD", 6))
		i++;
	val = find_value(old);
	free(old);
	old = ft_strjoin_normal("OLDPWD=", val);
	free(val);
	free(data->envp[i]);
	data->envp[i] = old;
}

int	ft_get_pwd(t_data *data, char *key)
{
	char	**envp;
	char	*val;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(key);
	envp = data->envp;
	while (envp[i] && ft_strncmp(key, envp[i], (len - 1)))
		i++;
	val = find_value(envp[i]);
	if (envp[i])
	{
		if (chdir(val) == -1)
		{
			error_message("MINISHELL : cd error\n");
			return(1);
		}
		i = 0;
		while (envp[i] &&ft_strncmp(envp[i], "PWD=", 4))
			i++;
		envp[i] = ft_strjoin_normal("PWD=", val);
		free(val);
	}
	else
	{
		error_message("MINISHELL : cd error\n");
		return (1);
	}
	return (0);
}

void	ft_cd(t_data *data)
{
	t_arg	*arg;
	char	*old;
	char	*pwd;
	int		i;

	old = get_old_pwd(data);
	arg = data->cmd->next;
	i = 0;
	if (!arg || !ft_strcmp (arg->ac, "~"))
	{
		if (ft_get_pwd (data, "HOME"))
			return ;
	}
	else if (arg && !ft_strcmp(arg->ac, "-"))
	{
		if (ft_get_pwd (data, "OLDPWD"))
			return ;
	}
	else
	{
		printf ("!!!!!!test\n");
		if (chdir(arg->ac) == -1)
		{
			error_message("MINISHELL : cd error\n");
			return ;
		}
		while (data->envp[i] &&ft_strncmp(data->envp[i], "PWD=", 4))
			i++;
		pwd = getcwd(NULL, 1024);
		data->envp[i] = ft_strjoin_normal("PWD=", pwd);
		free(pwd);
	}
	put_old_pwd(data, old);
}
