/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:05:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/08/30 17:19:34 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"

void	exit2(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int count_total(t_arg *head)
{
	int i;

	i = 0;
	while (head != NULL)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	error_message(char *str)
{
	rl_replace_line("", 1);
	printf ("%s", str);
}

void	ft_exit(t_arg *head)
{
	if (exitcheck(head))
		exit2();
}

int	exitcheck(t_arg *head)
{
	int t_cnt;
	int	j;
	char *str;

	j = 0;
	t_cnt = count_total(head);
	if (t_cnt > 1)
	{
		head = head->next;
		str = head->ac;
		if (str[j] == '-')
			j++;
		while (ft_isdigit(str[j]))
		{
			j++;
		}
		if (j != (int)ft_strlen(str))
		{
			error_message("MINISHELL: exit: ");
			printf ("%s: numeric argument required\n", str);
			return (0);
		}
	}
	if (t_cnt >= 3)
	{
		error_message("MINISHELL: exit: too many arguments\n");
		return(0);
	}
		return (1);
}

void	exit_C_d(void)
{
	printf ("\033[1A");
	printf ("\033[11C");
	printf (" exit\n");
	exit (EXIT_FAILURE);
}
