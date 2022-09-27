/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:35:53 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/27 16:35:58 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increase_temp(char *temp, char *ch, int *k, int *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	temp[j++] = ch[++i];
	temp[j++] = ch[i++];
	*l += 2;
	*k += 2;
}

int	is_ws(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		return (0);
	return (1);
}

int	for_red(char *c, int f)
{
	int	i;

	i = 0;
	if ((c[i] == '|' || c[i] == '<' || c[i] == '>') && f == 0)
		return (0);
	return (1);
}

int	for_d_red(char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (c[j] != '\0' && ((c[i] == '<' && c[j] == '<')
			|| (c[i] == '>' && c[j] == '>') || (c[i] == '|' && c[j] == '|')))
		return (0);
	return (1);
}

int	ft_charlen_export(char *str)
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
	return (j);
}
