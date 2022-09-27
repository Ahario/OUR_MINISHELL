/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:15:32 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/26 21:17:13 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_data			*data;
	struct termios	terminal;
	char			*ch;

	tcgetattr(STDIN_FILENO, &terminal);
	data = ft_before(argc, argv, envp);
	while (1)
	{
		ch = readline("MINISHELL./ ");
		if (ch)
		{
			if (check_parse(ch, data))
			{
				before_parse(ch, data);
				if (!ft_redir(data))
					ft_cmd_start(data);
			}
		}
		else if (!ch)
			exit_c_d();
		add_history(ch);
		data = clean_all(data, ch);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (0);
}
