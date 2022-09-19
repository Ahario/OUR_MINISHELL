/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:38:47 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/19 13:35:23 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

struct s_arg	*ft_list_del(t_arg *cmd)
{
	t_arg	*prev;
	t_arg	*next;

	prev = cmd->prev;
	if (prev)
		prev->next = cmd->next;
	next = cmd->next;
	if (next)
		cmd->next->prev = prev;
	free(cmd->ac);
	free(cmd);
	cmd = next;
	return (cmd);
}
