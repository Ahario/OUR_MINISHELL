/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:04:06 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/26 19:09:43 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/fcntl.h>

static int	check_str(char c, char *str)
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
		if(data->fd_in > 0)
			close(data->fd_in);
		ret = open(filename, O_RDONLY);
		data->fd_in = ret;
	}
	else if (flag == 1)
	{
		if(data->fd_out > 0)
			close(data->fd_out);
		ret = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		data->fd_out = ret;
	}
	else if (flag == 2)
	{
		if(data->fd_out > 0)
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

static int	filename_error(char *str, int *j)
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
		error_message(NULL, NULL);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(filename);
		data->fd_in = -1;
		data->fd_out = -1;
		g_exit_number = 1;
		if(!data->next && !data->prev)
			return (1);
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
	while (*prev)
	{
		free((*prev)->ac);
		free(*prev);
		*prev = (*prev)->next;
	}
	return (2);
}

void	heredoc_error(t_arg **prev)
{
	error_message(NULL, NULL);
	ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	g_exit_number = 258;
	while (*prev)
	{
		free((*prev)->ac);
		free(*prev);
		*prev = (*prev)->next;
	}
}

int	ft_start_heredoc(t_data *data, t_arg **cmd, char *str, t_arg **prev)
{
	int	i;

	i = 0;
	if (str[i + 2] == '\0')
	{
		*cmd = ft_list_del(*cmd);
		if (*cmd)
			str = (*cmd)->ac;
		else
		{
			heredoc_error(prev);
			return (1);
		}
	}
	else
		i += 2;
	ft_here_doc(data, str, &i, NULL);
	if (!(*cmd)->prev)
		*prev = NULL;
	if (*cmd)
		*cmd = ft_list_del(*cmd);
	return (0);
}

int	symbol_dollar(t_arg **cmd, t_arg **prev)
{
	if ((*cmd) && (*cmd)->ac[0] == '\0' && (*cmd)->next)
		(*cmd) = ft_list_del((*cmd));
	if (!*prev)
		*prev = *cmd;
	return (0);
}

t_arg	*ft_symbol(t_data *data, t_arg *cmd, int sw)
{
	char	*str;
	t_arg	*prev;

	prev = NULL;
	while (cmd)
	{
		str = cmd->ac;
		sw = check_symbol(data, str, &prev, &cmd);
		if (sw)
		{
			if (sw == 4)
				if (ft_start_heredoc(data, &cmd, str, &prev))
					return (0);
			if (sw == 2)
				return (0);
		}
		else
		{
			if (symbol_dollar(&cmd, &prev))
				break ;
			cmd = cmd->next;
		}
	}
	data->cmd = prev;
	return (data->cmd);
}

int	ft_cmd_set(t_data *data)
{
	t_arg	*prev;
	t_arg	*head;

	if (!data->cmd)
		return (1);
	data->cmd->prev = NULL;
	head = data->cmd;
	while (data->cmd)
	{
		prev = data->cmd;
		data->cmd = data->cmd->next;
		if (data->cmd)
			data->cmd->prev = prev;
	}
	data->cmd = head;
	return (0);
}

int	ft_redir(t_data *r_data)
{
	t_data	*data;

	data = r_data;
	data->prev = NULL;
	data->next = NULL;
	if (ft_cmd_set(data))
		return (1);
	data = ft_pipe_list(data);
	while (data)
	{
		data->cmd = ft_symbol(data, data->cmd, 0);
		if (!data->cmd)
			return (1);
		if (!data->next)
			break ;
		data = data->next;
	}
	while (data->prev)
		data = data->prev;
	return (0);
}

static void	ft_redirect_restore2(int restore_in, int restore_out)
{
	close(0);
	close(1);
	dup2(restore_in, 0);
	dup2(restore_out, 1);
	close(restore_in);
	close(restore_out);
}

void	ft_redirect_restore(t_data *data, int flag)
{
	static int	restore_in = -1;
	static int	restore_out = -1;

	if (data->fd_in < 0 && data->fd_out < 0 \
			&& restore_in < 0 && restore_out < 0)
		return ;
	if (!flag)
	{
		restore_in = dup(0);
		restore_out = dup(1);
		data->res_out = dup(1);
		if (data->fd_in > 0)
		{
			dup2(data->fd_in, 0);
			close(data->fd_in);
			data->fd_in = -1;
		}
		if (data->fd_out > 0)
		{
			dup2(data->fd_out, 1);
			close(data->fd_out);
			data->fd_out = -1;
		}
	}
	else if (flag)
		ft_redirect_restore2(restore_in, restore_out);
}
