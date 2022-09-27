/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:10:00 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:10:39 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parent_pipe(t_data *tem, int pid)
{
	(void)pid;
	close(tem->pipe[1]);
	if (!tem->next)
		return (1);
	return (0);
}
