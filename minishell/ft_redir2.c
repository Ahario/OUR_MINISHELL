/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:11:13 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:11:48 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_open_flag(t_data *data, char *filename, int flag)
{
	int	ret ;

	ret = 0;
	if (flag == 0)
	{
		if (data->fd_in > 0)
			close(data->fd_in);
		ret = open(filename, O_RDONLY);
		data->fd_in = ret;
	}
	else if (flag == 1)
	{
		if (data->fd_out > 0)
			close(data->fd_out);
		ret = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		data->fd_out = ret;
	}
	else if (flag == 2)
	{
		if (data->fd_out > 0)
			close(data->fd_out);
		ret = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		data->fd_out = ret;
	}
	return (ret);
}

int	filename_token(char *str, int *j)
{
	while (str[*j])
	{
		if (check_str(str[*j], "<>\n\0"))
		{
			error_message(" syntax error near unexpected token", NULL);
			printf ("'%s'\n", &str[*j]);
			g_exit_number = 258;
			return (1);
		}
		if (str[*j] == '$')
			break ;
		(*j)++;
	}
	return (0);
}

int	filename_error(char *str, int *j)
{
	if (!str[*j])
	{
		error_message("syntax error near unexpected token 'newline'\n", NULL);
		g_exit_number = 258;
		return (1);
	}
	if (str[*j] == '$')
	{
		error_message(NULL, NULL);
		ft_putstr_fd(&str[*j], 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		g_exit_number = 1;
		return (1);
	}
	if (filename_token(str, j))
		return (1);
	return (0);
}

void	infile_error_print(t_data *data, char *filename)
{
	if (!data->error)
	{
		error_message(NULL, NULL);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free(filename);
	data->fd_in = -1;
	data->fd_out = -1;
	data->error = 1;
	g_exit_number = 1;
}
