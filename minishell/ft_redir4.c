/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:13:39 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:14:57 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_error(t_arg **prev)
{
	t_arg	*next;

	error_message(NULL, NULL);
	ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	g_exit_number = 258;
	while (*prev)
	{
		next = (*prev)->next;
		free((*prev)->ac);
		free(*prev);
		*prev = next;
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
	if ((*cmd)->ac[0] == '$' && (*cmd)->ac[1] != '\0' && (*cmd)->type != SINQ \
			&& (*cmd)->type != DOLLAR)
	{
		(*cmd) = ft_list_del(*cmd);
		if (!*cmd)
			return (1);
	}
	if (!*prev)
		*prev = *cmd;
	return (0);
}
