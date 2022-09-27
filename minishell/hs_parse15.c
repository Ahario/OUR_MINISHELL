/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse15.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:35:53 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/27 18:06:33 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hs_create_empty(char *s)
{
	s = malloc(sizeof(char) * 1);
	s[0] = '\0';
}

void	ft_clean_all_utill(t_data **data)
{
	t_arg	*next;
	t_data	*d_next;

	while ((*data)->cmd)
	{
		if ((*data)->cmd->ac)
			free((*data)->cmd->ac);
		next = (*data)->cmd->next;
		if ((*data)->cmd)
			free((*data)->cmd);
		(*data)->cmd = next;
	}
	d_next = (*data)->next;
	if (!(*data)->prev)
	{
		free_split((*data)->envp);
	}
	if ((*data)->pipe && (*data)->next)
	{
		free((*data)->pipe);
	}
	free(*data);
	(*data) = d_next;
}
