/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 01:19:45 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/23 23:46:46 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_envp_pwd(char **envp)
{
	char	*val;
	int		i;

	i = 0;
	while (envp && ft_strncmp(envp[i], "PWD", 3))
		i++;
	val = find_value(envp[i]);
	if (val)
	{
		printf("%s\n", val);
		free(val);
	}
}

void	ft_pwd(t_data *data)
{
	char	*str;

	str = getcwd(NULL, 1024);
	if (str &&!str[0])
		ft_envp_pwd(data->envp);
	else
		printf ("%s\n", str);
	free (str);
	return ;
}
