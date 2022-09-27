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

char	*replace_dollar_sign_dq(char *st, t_data *data)
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
			else if (st[i] == '$' && st[i + 1] == '\0')
				temp = hs_give_dollar();
			else
				temp = hs_change_full_path_dq(st, data);
			return (temp);
		}
		i++;
	}
	return (NULL);
}

char	*get_full_path_dq(char *str, t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	temp = NULL;
	while (data->envp[i] != NULL && search_mini_path(i, data->envp, str))
		i++;
	if (data->envp[i] == NULL)
		return (backup_path(str));
	while (data->envp[i][j] != '=')
		j++;
	j++;
	while (data->envp[i][j] != '\0' && data->envp[i][j] == ' ')
		j++;
	temp = malloc(sizeof(char) * (ft_charlen(&data->envp[i][j]) + 1));
	while (data->envp[i][j] != '\0')
		temp[k++] = data->envp[i][j++];
	temp[k] = '\0';
	return (temp);
}

void	add_i(int *i, char *str)
{
	int	k;

	k = 0;
	k++;
	while (for_replace_ds_parse(str, k) == 0)
		k++;
	*i += k;
}

char	*replace_ds_parse(char *str, t_data *data, int flag)
{
	char	*temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp = malloc(sizeof(char) * ((before_r_ds_parse(str, data)) + 1));
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if (str[i] == '$' && flag != 2)
		{
			if (flag == 1)
				if_replace_ds_parse(&k, &str[i], &temp[k], data);
			else
				if_replace_ds_parse_dq(&k, &str[i], &temp[k], data);
			add_i(&i, &str[i]);
		}
		else
			temp[k++] = str[i++];
	}
	temp[k] = '\0';
	free(str);
	return (temp);
}

char	*ft_strcpy_hth(char *str, int here, int there)
{
	int		i;
	int		j;
	char	*temp;

	i = here;
	j = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (there - here));
	while (i + j != there)
	{
		temp[j] = str[i + j];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}
