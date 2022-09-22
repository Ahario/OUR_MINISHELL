/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:43:10 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/22 14:17:14 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data)
{
	t_arg	*arg;
	int		flag;
	int		i;

	flag = 0;
	arg = NULL;
	printf ("AAAAAAA\n");
	if (data->cmd->next)
		arg = data->cmd->next;
	while (arg && !ft_strncmp(arg->ac, "-n", 2))
	{
		i = 2;
		while (arg->ac[i] == 'n')
			i++;
		if (arg->ac[i])
			break;
		flag = 1;
		arg = arg->next;
	}
	while (arg)
	{
		printf("%s", arg->ac);
		arg = arg->next;
		if (arg)
			printf (" ");
	}
	if (!flag)
		printf ("\n");
}
