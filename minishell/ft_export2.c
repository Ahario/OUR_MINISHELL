/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:04:54 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:06:41 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *envp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] && envp[i] != '=' && envp[i] != '+')
		i++;
	ret = (char *)malloc(sizeof(char) * i + 1);
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
	if (!envp)
		return (NULL);
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i] || !envp[i + 1])
		return (NULL);
	i++;
	j = i;
	while (envp[i])
		i++;
	size = i - j;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	while (size >= 0)
		ret[size--] = envp[i--];
	return (ret);
}

char	**print_array(char **envp, int i)
{
	char	**array;
	char	*tem;
	int		size;

	array = ft_strdup_2(envp);
	while (array[i])
		i++;
	size = i - 1;
	while (size)
	{
		i = 0;
		while (i < size)
		{
			if (array[i] && ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tem = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tem;
			}
			i++;
		}
		size--;
	}
	return (array);
}

void	ft_export_narg(char **envp, char *key, char *val)
{
	char	**array;
	int		i;

	i = 0;
	array = print_array(envp, 0);
	while (array[i])
	{
		key = find_key(array[i]);
		val = find_value(array[i]);
		if (key)
		{
			printf("declare -x ");
			printf ("%s", key);
			free(key);
		}
		if (val)
		{
			printf ("=\"%s\"\n", val);
			free(val);
		}
		else
			printf ("\n");
		i++;
	}
	free_split(array);
}

int	ft_check_key(char *str, int flag)
{
	int	i;

	if (!str || !str[0])
		return (1);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '=' && str[i] != '+' \
				&& !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (1);
		if (str[i] == '+' && str[i + 1] != '=')
			return (1);
		if (str[i] == '=' && !flag)
			return (1);
		else if ((str[i] == '=' || str[i] == '+') && flag)
			break ;
		i++;
	}
	return (0);
}
