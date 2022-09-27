/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:17:57 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 16:49:12 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

char	**unset_envp(char	**envp, int i)
{
	char	**ret;
	int		size;
	int		j;

	size = 0;
	j = 0;
	while (envp[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * size - 1);
	size = 0;
	while (envp[j])
	{
		if (j != i)
			ret[size++] = envp[j];
		j++;
	}
	ret[size] = NULL;
	free(envp[i]);
	free(envp);
	envp = NULL;
	return (ret);
}

void	ft_unset_error(char *ac)
{
	error_message("export: ", ac);
	ft_putstr_fd(": not a vaild identifier\n", 2);
	g_exit_number = 1;
}

void	ft_unset(t_data *data)
{
	char	**envp;
	t_arg	*tem;
	int		i;

	i = 0;
	tem = data->cmd->next;
	while (tem)
	{
		envp = data->envp;
		if (ft_check_key(tem->ac, 0))
		{
			ft_unset_error(tem->ac);
			return ;
		}
		while (envp[i] && ft_strncmp(envp[i], tem->ac, ft_strlen(tem->ac)))
			i++;
		if (!envp[i])
		{
			tem = tem->next;
			continue ;
		}
		data->envp = unset_envp(envp, i);
		tem = tem->next;
	}
}
