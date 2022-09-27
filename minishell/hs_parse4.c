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

int	ft_charlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	for_ft_find_red(char *c, int f)
{
	int	i;

	i = f - 1;
	if (f > 0)
	{
		if ((c[i] == '<' && c[f] == '<') || (c[f] == '>' && c[f] == '>'))
			return (0);
	}
	return (1);
}

int	ft_find_red(char *str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>' ) && flag == 0)
		{
			if (for_ft_find_red(str, i) == 0)
				i++;
			else
				j++;
		}
		i++;
	}
	return (j);
}

int	check_dq_pair(char *str)
{
	int	i;
	int	q_flag;
	int	dq_flag;

	q_flag = 0;
	dq_flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"') || (str[i] == '\''))
		{
			if (str[i] == '\"' && q_flag == 0)
				dq_flag = check_dq_flag(dq_flag);
			else if (str[i] == '\'' && dq_flag == 0)
				q_flag = check_dq_flag(q_flag);
		}
		i++;
	}
	if (q_flag == 1 || dq_flag == 1)
		return (0);
	return (1);
}

int	check_parse(char *ch, t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	(void)data;
	while (ch[i] != '\0')
	{
		if (is_ws(&ch[i]) == 0)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	flag = check_dq_pair(ch);
	return (flag);
}
