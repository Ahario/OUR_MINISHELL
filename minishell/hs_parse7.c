/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:35:53 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/27 16:35:58 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_replace_ds_parse(int *k, char *c, char *t, t_data *data)
{
	int		i;
	int		j;
	char	*temp2;

	i = 0;
	j = 0;
	temp2 = replace_dollar_sign(&c[i], data);
	if (!temp2)
		return ;
	while (temp2[i] != '\0')
		t[j++] = temp2[i++];
	free(temp2);
	*k += j;
}

void	hs_check_for_space(int *j, int i, char *temp2, char *t)
{
	int	k;

	k = 0;
	if (*j == 0 && temp2[i] != '\0' && temp2[i] != ' ')
	{
		t[k++] = '\"';
		*j += 1;
	}
	if (temp2[i] != '\0' && *j != 0)
	{
		t[k++] = ' ';
		*j += 1;
	}
}

void	if_replace_ds_parse_dq(int *k, char *c, char *t, t_data *data)
{
	int		i;
	int		j;
	char	*temp2;

	i = 0;
	j = 0;
	temp2 = replace_dollar_sign_dq(&c[i], data);
	if (!temp2)
		return ;
	while (temp2[i] != '\0')
	{
		if (j == 0 && temp2[i] != '\0' && temp2[i] != ' ')
			t[j++] = '\"';
		if (temp2[i] == ' ')
		{
			while (temp2[i] != '\0' && temp2[i] == ' ')
					i++;
			hs_check_for_space(&j, i, temp2, &t[j]);
		}
		else
			t[j++] = temp2[i++];
	}
	t[j++] = '\"';
	*k += j;
	free(temp2);
}

char	*get_full_exit(char *temp, char *str)
{
	int		i;
	int		j;
	char	*temp2;

	i = 0;
	j = 0;
	temp2 = malloc(sizeof(char) * (ft_charlen(temp) + (ft_charlen(str)) + 1));
	while (temp[i] != '\0')
		temp2[j++] = temp[i++];
	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\"')
		temp2[j++] = str[i++];
	temp2[j] = '\0';
	return (temp2);
}

char	*hs_change_full_path_dq(char *str, t_data *data)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp2 = get_path(str);
	temp = get_full_path_dq(temp2, data);
	free(temp2);
	return (temp);
}
