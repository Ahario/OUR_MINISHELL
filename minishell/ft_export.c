/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:24:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:27:22 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

char	**ft_change_envp(t_data *data, char *str, int len)
{
	char	*key;
	char	**tem;
	int		i;

	i = 0;
	tem = data->envp;
	len = ft_strchr_ind(str, '+');
	if (!len)
		len = ft_strchr_ind(str, '=');
	key = find_key(str);
	while (tem[i] && ft_strncmp(tem[i], key, len))
		i++;
	if (tem[i])
	{
		tem[i] = ft_change_val(tem[i], str, len);
		free(key);
		return (tem);
	}
	tem = ft_new_envp(tem, key, find_value(str));
	return (tem);
}

int	ft_check_export(t_data *data, char *key)
{
	char	**tem;
	char	*check;
	int		i;

	i = 0;
	tem = data->envp;
	while (tem[i])
	{
		check = find_key(tem[i]);
		if (!ft_strcmp(check, key))
		{
			free(check);
			check = NULL;
			return (1);
		}
		free(check);
		check = NULL;
		i++;
	}
	return (0);
}

void	add_export(t_data *data, t_arg *tem)
{
	char	*key;

	key = find_key(tem->ac);
	if (ft_strchr(tem->ac, '=') || ft_strchr(tem->ac, '+'))
	{
		data->envp = ft_change_envp(data, tem->ac, 0);
		free(key);
		key = NULL;
	}
	else if (ft_check_export(data, key))
	{
		free(key);
		key = NULL;
	}
	else
		data->envp = ft_new_envp(data->envp, key, NULL);
}

int	ft_export_error(t_arg **tem)
{
	error_message("export: ", (*tem)->ac);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("not a valid identifier\n", 2);
	if ((*tem)->next)
		(*tem) = (*tem)->next;
	else
	{
		g_exit_number = 1;
		return (1);
	}
	return (0);
}

void	ft_export(t_data *data)
{
	t_arg	*tem;

	if (!data->cmd->next)
	{
		ft_export_narg(data->envp, 0, 0);
		return ;
	}
	tem = data->cmd->next;
	while (tem)
	{
		while (ft_check_key(tem->ac, 1))
		{
			if (ft_export_error(&tem))
				return ;
		}
		add_export(data, tem);
		tem = tem->next;
	}
}
