/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:35:53 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/27 16:35:58 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hs_for_only_ds(char *s, int i)
{
	if (s[i] == '$' && ((s[i + 1] == '\0') || (s[i + 1] == '\"')
			|| (s[i + 1] == '\'') || (s[i + 1] == ' ')))
		return (0);
	return (1);
}

char	*hs_change_pid(char *str, int i)
{
	int		j;
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	j = 0;
	j = getpid();
	temp2 = ft_itoa(j);
	temp = get_full_exit(temp2, &str[i + 2]);
	free(temp2);
	return (temp);
}

char	*hs_give_dollar(void)
{
	char	*temp;

	temp = malloc(sizeof(char) * (2));
	temp[0] = '$';
	temp[1] = '\0';
	return (temp);
}

char	*replace_dollar_sign(char *st, t_data *data)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (st[i] != '\0')
	{
		if (st[i] == '$')
		{
			if (st[i] == '$' && st[i + 1] == '?')
				temp = hs_change_exit_number(&st[i], i);
			else if (st[i] == '$' && st[i + 1] == '$')
				temp = hs_change_pid(&st[i], i);
			else if (hs_for_only_ds(&st[i], i) == 0)
				temp = hs_give_dollar();
			else
				temp = hs_change_full_path(st, data);
			return (temp);
		}
		i++;
	}
	return (NULL);
}

int	for_before_r_ds_parse(char *c)
{
	int	i;

	i = 0;
	if (c[i] != '\"' && c[i] != '\'' && c[i] != '\0'
		&& c[i] != ' ' && c[i] != '$')
		return (0);
	return (1);
}
