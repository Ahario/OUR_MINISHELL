/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:24:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/01 22:57:59 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *envp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (envp[i] != '=')
		i++;
	ret = (char *)malloc(sizeof(char) * i);
	ret[i] = '\0';
	while (--i >= 0)
		ret[i] = envp[i];
	return (ret);
}

char	*find_value(char *envp)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	i = 0;
	ret = NULL;
	while (envp[i] != '=' && envp[i])
		i++;
	if (!envp[i])
		return (NULL);
	i++;
	j = i;
	while (envp[i])
		i++;
	size = i - j;
	ret = (char *)malloc(sizeof(char) * size);
	ret[size] = '\0';
	while (size >= 0)
		ret[size--] = envp[--i];
	return (ret);
}



void	ft_export_narg(char **envp)
{
	char	*val;
	char	*key;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = find_key(envp[i]);
		val = find_value(envp[i]);
		printf("declare -x ");
		printf("%s", key);
		if (val)
			printf ("=\"%s\"\n", val);
		i++;
	}
}
void	ft_export(t_data *data)
{
	t_arg	*tem;

	tem = data->cmd->next;
	if (!tem)
		ft_export_narg(data->envp);
}
