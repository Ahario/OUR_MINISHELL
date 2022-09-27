/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:03:08 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:04:12 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit2(int flag)
{
	if (!flag)
		printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	count_total(t_arg *head)
{
	int		i;
	t_arg	*tem;

	i = 0;
	tem = head;
	while (tem != NULL)
	{
		i++;
		tem = tem->next;
	}
	return (i);
}

void	error_message(char *str, char *des)
{
	rl_on_new_line();
	ft_putstr_fd("MINISHELL: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	if (des)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(des, 2);
		ft_putstr_fd("'", 2);
	}
	g_exit_number = 127;
}
