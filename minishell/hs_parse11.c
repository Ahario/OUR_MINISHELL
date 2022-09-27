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

void	assign_parse(t_data *data)
{
	t_arg	*curr;

	curr = data->cmd;
	while (curr != NULL)
	{
		if (check_q(curr->ac) == 0)
			assign_q(&curr);
		else if (check_dq(curr->ac) == 0)
			assign_dq(&curr);
		else if (check_redirect(curr->ac) == 0)
			assign_redirect(&curr);
		else if (check_pipe(curr->ac) == 0)
			assign_pipe(&curr);
		curr = curr->next;
	}
	parse_bigpart(data);
}

int	check_type(char *str, t_arg *curr)
{
	int	i;

	i = 0;
	if (curr->type != SINQ)
	{
		while (str[i] != '\0')
		{
			if (str[i] == '$' && i > 0)
			{
				if (str[i - 1] == '\"' && str[i + 1] == '\"')
					return (DOLLAR);
			}
			i++;
		}
	}
	return (curr->type);
}

void	parse_bigpart(t_data *data)
{
	int		flag;
	t_arg	*curr;

	flag = 0;
	curr = data->cmd;
	while (curr != NULL)
	{
		flag = 0;
		curr->ac = replace_ds_parse(curr->ac, data, flag);
		curr->type = check_type(curr->ac, curr);
		curr = curr->next;
	}
	replace_parse(data);
}

int	total_path_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0'
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '$')
		i++;
	return (i);
}

char	*get_path(char *str)
{
	int		i;
	int		j;
	char	*temp;

	temp = NULL;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			temp = malloc(sizeof(char) * (total_path_len(&str[i]) + 1));
			while (j != total_path_len(&str[i]))
			{
				temp[j] = str[i + j];
				j++;
			}
			temp[j] = '\0';
			break ;
		}
		i++;
	}
	return (temp);
}
