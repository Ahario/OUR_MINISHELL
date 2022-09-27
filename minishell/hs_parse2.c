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

int	check_dp(char *ch, int i)
{
	if (ch[i - 1] == '|' && ch[i] != ' ' && ch[i] != '|')
		return (0);
	return (1);
}

int	check_red(char *ch, int i)
{
	if ((ch[i - 1] == '<' && ch[i] != ' ')
		|| (ch[i - 1] == '>' && ch[i] != ' '))
		return (0);
	return (1);
}

int	for_bp(int flag, int i, char *ch)
{
	if (flag == 0 && i > 0)
	{
		if ((check_dp(ch, i) == 0) || (check_red(ch, i) == 0))
			return (0);
	}
	return (1);
}

void	before_parse(char *ch, t_data *data)
{
	int		i;
	int		j;
	int		flag;
	char	*temp;

	i = 0;
	j = 0;
	flag = 0;
	temp = malloc(sizeof(char) * (ft_charlen(ch) + ft_find_red(ch)) + 4);
	while (ch[i] != '\0')
	{
		flag = check_flag(flag, &ch[i]);
		if (for_red(&ch[i], flag) == 0)
		{
			if (ch[i - 1] != ' ')
				temp[j++] = ' ';
			if (for_d_red(&ch[i]) == 0)
				increase_temp(&temp[j], &ch[i], &i, &j);
		}
		temp[j++] = ch[i++];
		if (for_bp(flag, i, ch) == 0)
			temp[j++] = ' ';
	}
	temp[j] = '\0';
	parse(temp, data);
}

void	parse(char *ch, t_data *data)
{
	int		i;
	t_arg	*head;

	i = 0;
	head = NULL;
	data->argc = ft_strlen(ch);
	while (ch[i] != '\0')
	{
		if ((ch[i] != '\'' && ch[i] != '\"')
			|| (ch[i] == '\"' || ch[i] == '\''))
		{
			while (is_ws(&ch[i]) == 0)
				i++;
			if (ch[i] != '\0')
			{
				add_back(&head, &ch[i]);
				i += (if_char(&ch[i]));
			}
		}
	}
	data->cmd = head;
	free(ch);
	assign_parse (data);
}
