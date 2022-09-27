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

void	increase_both(int *i, int *j)
{
	*i += 1;
	*j += 1;
}

int	ft_charlen_export_free(char *str)
{
	int	i;
	int	j;

	j = 2;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	free(str);
	return (j);
}

int	before_r_ds_parse(char *str, t_data *data)
{
	int		i;
	int		j;
	int		flag;
	char	*temp;

	i = 0;
	j = 1;
	flag = 0;
	temp = NULL;
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if (str[i] == '$' && flag != 2)
		{
			temp = replace_dollar_sign(&str[i], data);
			j += ft_charlen_export_free(temp);
			temp = NULL;
			i++;
			while (for_before_r_ds_parse(&str[i]) == 0)
				i++;
		}
		else
			increase_both(&i, &j);
	}
	return (j);
}

int	for_replace_ds_parse(char *c, int k)
{
	int	i;

	i = k;
	if (c[k - 1] == '$' && c[k] == '$')
		return (0);
	if (c[i] != '\"' && c[i] != '\'' && c[i] != '\0'
		&& c[i] != ' ' && c[i] != '$')
		return (0);
	return (1);
}

void	reset_replace_ds_parse(int *flag, int *i, int *k)
{
	*flag = 0;
	*i = 0;
	*k = 0;
}
