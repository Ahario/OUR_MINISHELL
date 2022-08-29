/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:40:03 by sunglee           #+#    #+#             */
/*   Updated: 2022/08/29 14:47:42 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_exit(void)
{
	printf ("\033[1A");
	printf ("\033[11C");
	printf (" exit\n");
	exit (EXIT_FAILURE);
}

void	ft_signal(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
