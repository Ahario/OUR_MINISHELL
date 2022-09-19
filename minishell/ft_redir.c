/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:04:06 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/19 16:39:50 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/fcntl.h>

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

void	ft_open_flag(t_data *data, char *filename, int flag)
{
	if (flag == 0)
	{
		close(data->fd_in);
		data->fd_in = open(filename, O_RDONLY);
	}
	else if (flag == 1)
	{
		close(data->fd_out);
		data->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}

}

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
//	if (flag)
//		size = j + 1;
	(*i) += size;
	filename = (char *)malloc(sizeof(char) * size);
	if (!filename)
		return (1);
	while (size >= 0)
		filename[--size] = str[j--];
//	printf("%s\n", filename);
	ft_open_flag(data, filename, flag);
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

struct s_arg	*ft_symbol(t_data *data, t_arg *cmd)
{
	char	*str;
	t_arg	*prev;
	int		i;
	int		flag;

	while (cmd)
	{
		i = 0;
		prev = cmd;
		str = cmd->ac;
		if ((str[i] == '<' || str[i] == '>')) //&& tem->type == 0)
		{
			if (str[i] == '<')
			{
				flag = 0;
				if (str[i + 1] == '\0')
				{
					cmd = ft_list_del(cmd);
					str = cmd->ac;
				}
				else
					i++;
				if(!infilename_check(data, str, &i, flag))
					if (cmd)
						cmd = ft_list_del(cmd);
			}
			else if (str[i] == '>')
			{
				flag = 1;
				if (str[i + 1] == '\0')
				{
					cmd = ft_list_del(cmd);
					str = cmd->ac;
				}
				else
					i++;
				if(!infilename_check(data, str, &i, flag))
					if (cmd)
						cmd = ft_list_del(cmd);
			}

		}
		else
			cmd = cmd->next;
	}
	cmd = prev;
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

void	ft_cmd_set(t_data *data)
{
	t_arg	*prev;
	t_arg	*head;

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
}
/*
void	ft_dep(t_data *data)
{
	t_arg	*new;
	char	*newarg;
	char	*oldarg;
	int		j = 0;

	while(data->cmd)
	{
		int	i = 0;
		while (data->cmd->ac[i])
		{
			if (ft_strchr("<>;", data->cmd->ac[i]))
			{
				new = (t_arg *)malloc(sizeof(t_arg));
				newarg = (char *)malloc(sizeof(char) * i);
				while(i > j)
				{
					newarg[j] = data->cmd->ac[j];
					j++;
				}
				newarg[j] = '\0';
				oldarg = ft_strjoin_normal(NULL , &data->cmd->ac[i]);
				new->ac = newarg;
				printf("new %s\n", newarg);
				printf("old %s\n", oldarg);
				break;
			}
			i++;
		}
		data->cmd = data->cmd->next;
		printf("!!~~~~~~~!!!\n");
	}
}*/

void	ft_redir(t_data *data)
{
//	printf("!!~~~~~~~!!!\n");
//	ft_dep(data);
	ft_cmd_set(data);
	data->cmd = ft_symbol(data, data->cmd);
	return ;
}

void	ft_redirect_restore(t_data *data, int flag)
{
	static int	restore_in = -1;
	static int	restore_out = -1;

	if (data->fd_in < 0 && data->fd_out < 0 &&restore_in < 0 && restore_out < 0)
		return;
	if (!flag)
	{
		restore_in = dup(0);
		restore_out = dup(1);
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
	else if(flag)
	{
		dup2(restore_in, 0);
		dup2(restore_out, 1);
		close(restore_in);
		close(restore_out);
	}
}
