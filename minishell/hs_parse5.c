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

int	get_temp_size(char *str)
{
	int		i;
	int		j;
	char	charset;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"' || str[i] == '\''))
		{
			charset = str[i];
			i++;
			while (str[i] != charset && str[i] != '\0')
			{
				i++;
				j++;
			}
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

void	if_replace_parse(char *str, char *temp, int *i, int *j)
{
	int		k;
	int		l;
	char	charset;

	k = 0;
	l = 0;
	charset = str[k];
	k++;
	while (str[k] != charset && str[k] != '\0')
		temp[l++] = str[k++];
	if (str[k] != '\0')
		k++;
	*i += k;
	*j += l;
}

char	*reset_replace_parse(int *i, int *j, char *str)
{
	char	*temp;

	temp = malloc(sizeof(char) * (get_temp_size(str) + 1));
	*i = 0;
	*j = 0;
	return (temp);
}

void	replace_parse(t_data *data)
{
	int		i;
	int		j;
	char	*temp;
	t_arg	*curr;

	i = 0;
	j = 0;
	temp = NULL;
	curr = data->cmd;
	while (curr != NULL)
	{
		temp = (reset_replace_parse(&i, &j, curr->ac));
		while (curr->ac[i] != '\0')
		{
			if (curr->ac[i] == '\'' || curr->ac[i] == '\"')
				if_replace_parse(&curr->ac[i], &temp[j], &i, &j);
			else
				temp[j++] = curr->ac[i++];
		}
		temp[j] = '\0';
		free(curr->ac);
		curr->ac = temp;
		temp = NULL;
		curr = curr->next;
	}
}

int	check_flag(int flag, char *str)
{
	int	i;

	i = flag;
	if (str[0] == '\"' && i != 2)
	{
		if (i == 1)
			i = 0;
		else
			i = 1;
	}
	if (str[0] == '\'' && i != 1)
	{
		if (i == 2)
			i = 0;
		else
			i = 2;
	}
	return (i);
}
