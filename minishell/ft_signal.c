/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:40:03 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/21 19:14:40 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <sys/signal.h>

static void	ft_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void ft_child_c(int	sig)
{
	(void)sig;
	write(1, "^C\n", 3);
}

void	ft_quit(int sig)
{
	(void)sig;
	ft_putstr_fd("QUIT: 3", 2);
	signal(SIGINT, SIG_IGN);
}

void	ft_signal_cmd(void)
{
	signal(SIGINT, ft_child_c);
	signal(SIGQUIT, ft_quit);
	signal(SIGTERM, SIG_IGN);
}
