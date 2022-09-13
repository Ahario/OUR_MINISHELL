/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:58:23 by hyeo              #+#    #+#             */
/*   Updated: 2022/06/16 12:46:17 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	search_path(int i, char *envp[])
{
	if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
		return (0);
	return (1);
}

char	*search_filename(char *command, char *envp[])
{
	int		i;
	int		j;
	char	*filename;

	i = 0;
	j = 5;
	while (envp[i] != NULL && search_path(i, envp))
		i++;
	if (ft_strchr(command, "/") == 1)
		filename = ft_strdup(command);
	else
		filename = my_parsing_filename(i, j, command, envp);
	return (filename);
}

void	free_my_files(char *new_filename, char *temp)
{
	free(new_filename);
	free(temp);
}

void	free_my_pipex(t_pipe *my_pipex)
{
	int	i;

	i = 0;
	while (my_pipex->command[i] != NULL)
	{
		free(my_pipex->command[i]);
		i++;
	}
	free(my_pipex->command);
	free(my_pipex->filename);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		total;
	char	*temp;

	i = 0;
	total = 0;
	while (s1[total] != '\0')
		total++;
	temp = malloc(sizeof(char) * (total + 1));
	if (temp == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
