/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:04:06 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/17 00:39:36 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_str(char c,char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(c == str[i])
			return (1);
		i++;
	}
	return (0);
}

/*int	command_check(t_data *data, char *str, int *i)
{


}*/

int	infilename_check(t_data *data, char *str, int *i, int flag)
{
	int	j;
	int	size;
	char	*filename;

	j = *i;
	while(str[j])
	{
		if (check_str(str[j], "\n\0"))
			return (1);
		j++;
	}
	size = j;
	if (flag)
		size = j + 1;
	filename = (char *)malloc(sizeof(char) * size);
	if (!filename)
		return (1);
	while (size >= 0)
		filename[--size] = str[j--];
	printf("%s\n", filename);
	close(data->fd_in);
	data->fd_in = open(filename, O_RDONLY);
	if (data->fd_in == -1)
	{
		error_message("MINISHELL: ");
		printf ("%s: No such file or directory\n", filename);
		free(filename);
		data->fd_in = 0;
		return (1);
	}
	free(filename);
	return (0);
}

void	ft_redir(t_data *data)
{
	int	i;
	int	flag;
	char	*str;
	t_arg	*tem;

	i = 0;
	tem = data->cmd;
	str = tem->ac;
	if ((str[i] == '<' || str[i] == '>') && tem->type == 0)
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '\0')
			{
				tem = tem->next;
				str = tem->ac;
				flag = 1;
			}
			else
			{
				flag = 0;
				(i)++;
			}
			if(!infilename_check(data, str, &i, flag))
			{
				return ;
			}
		}
	}
}

/*void	ft_redirect_restore(t_data *data, int flag)
{
	if (data->fd_in < 0 && data->fd_out < 0)
	{

	}
}*/
