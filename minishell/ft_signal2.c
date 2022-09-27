/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:07:37 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 17:08:21 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_kill(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}

void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(1, "\b\b\b\b\b\b\b\b\b\b\b\b", 12);
	exit(1);
}

void	ft_signal_here(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, ft_signal_kill);
}
