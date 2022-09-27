/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:12:37 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:13:05 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infilename_check(t_data *data, char *str, int *i, int flag)
{
	char	*filename;
	int		j;
	int		size;

	j = *i;
	if (filename_error(str, &j))
		return (1);
	size = j - *i;
	filename = (char *)malloc(sizeof(char) * size);
	if (!filename)
		return (1);
	filename[size--] = '\0';
	while (size >= 0)
		filename[size--] = str[--j];
	if (ft_open_flag(data, filename, flag) == -1)
	{
		infile_error_print(data, filename);
		return (0);
	}
	free(filename);
	return (0);
}

int	get_flag(char *str, t_arg *cmd)
{
	int	i;

	i = 0;
	if ((str[i] == '<' && str[i + 1] == '<') \
				&& cmd && cmd->type != SINQ && cmd->type != DOUQ)
		return (4);
	else if ((str[i] == '>' && str[i + 1] == '>') \
				&& cmd->type != SINQ && cmd->type != DOUQ)
		return (2);
	else if ((str[i] == '<' || str[i] == '>') \
				&& cmd->type != SINQ && cmd->type != DOUQ)
	{
		if (str[i] == '<')
			return (0);
		else if (str[i] == '>')
			return (1);
	}
	return (404);
}

void	symbol_del2(t_arg **cmd, char **str, int *i)
{
	if ((*str)[2] == '\0')
	{
		*cmd = ft_list_del(*cmd);
		if (*cmd)
			*str = (*cmd)->ac;
		else
			*str = "\0";
	}
	else
		(*i) += 2;
}

void	symbol_del(t_arg **cmd, char **str, int *i, int flag)
{
	if (flag == 1 || flag == 0)
	{
		if ((*str)[1] == '\0')
		{
			*cmd = ft_list_del(*cmd);
			if (*cmd)
				*str = (*cmd)->ac;
			else
				*str = "\0";
		}
		else
			(*i)++;
	}
	else if (flag == 2)
	{
		symbol_del2(cmd, str, i);
	}
}

int	check_symbol(t_data *data, char *str, t_arg **prev, t_arg **cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = get_flag(str, *cmd);
	if (flag == 404)
		return (0);
	if (flag == 4)
		return (4);
	symbol_del(cmd, &str, &i, flag);
	if (!infilename_check(data, str, &i, flag))
	{
		if (*cmd)
			*cmd = ft_list_del(*cmd);
		return (1);
	}
	(void)prev;
	return (2);
}
