/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:05:46 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:06:06 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_change_val(char *envp, char *str, int len)
{
	if (envp)
	{
		if (str[len] == '+' && str[len + 1] == '=')
			envp = ft_strjoin_free(envp, ft_strdup(&str[len + 2]));
		else if (envp)
		{
			free(envp);
			envp = ft_strdup(str);
		}
	}
	return (envp);
}

char	**ft_new_envp(char **tem, char *key, char *val)
{
	char	**ret;
	int		size;

	size = 0;
	while (tem[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	size = 0;
	while (tem[size])
	{
		ret[size] = tem[size];
		size++;
	}
	ret[size] = ft_strjoin_keyval(key, val);
	ret[++size] = NULL;
	free(tem);
	return (ret);
}
