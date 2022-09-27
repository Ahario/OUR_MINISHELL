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

int	search_mini_path(int j, char *envp[], char *str)
{
	int	i;

	i = 0;
	while (envp[j][i] == str[i])
	{
		if (str[i] == envp[j][i])
			i++;
		else
			return (1);
	}
	if (envp[j][i] == '=' && str[i] == '\0')
		return (0);
	return (1);
}

char	*backup_path(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 0;
	temp = malloc(sizeof(char) * (ft_charlen(str)) + 2);
	temp[0] = '$';
	while (str[j] != '\0')
		temp[i++] = str[j++];
	temp[i] = '\0';
	return (temp);
}

char	*get_full_path(char *str, t_data *data)
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
	temp = malloc(sizeof(char) * (ft_charlen(&data->envp[i][j]) + 1));
	while (data->envp[i][j] != '\0')
		temp[k++] = data->envp[i][j++];
	temp[k] = '\0';
	return (temp);
}

char	*hs_change_exit_number(char *str, int i)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp2 = ft_itoa(g_exit_number);
	temp = get_full_exit(temp2, &str[i + 2]);
	free(temp2);
	return (temp);
}

char	*hs_change_full_path(char *str, t_data *data)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp2 = get_path(str);
	temp = get_full_path(temp2, data);
	free(temp2);
	return (temp);
}
