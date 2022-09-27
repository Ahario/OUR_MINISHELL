/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:57:20 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:00:55 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_old_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "PWD", 3))
		i++;
	return (data->envp[i]);
}

void	put_old_pwd(t_data *data, char *old)
{
	int		i;
	char	*val;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD", 6))
		i++;
	val = find_value(old);
	free(old);
	old = ft_strjoin_normal("OLDPWD=", val);
	free(val);
	free(data->envp[i]);
	data->envp[i] = old;
}
