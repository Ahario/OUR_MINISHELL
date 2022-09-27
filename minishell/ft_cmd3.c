/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:00:17 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:01:26 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(char *str, int flag)
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

int	cmd_check_utill(char *str, char *envp_path)
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

char	*path_check(char *str)
{
	struct stat	buf;

	if (stat(str, &buf))
	{
		error_message(NULL, NULL);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	if (S_ISDIR(buf.st_mode))
	{
		error_message(NULL, NULL);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_exit_number = 126;
		return (NULL);
	}
	return (str);
}

char	*ft_cmd_return(char	*str, char *envp, char **envp_path)
{
	if (cmd_check_utill(str, envp))
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
