/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:58:05 by hyeo              #+#    #+#             */
/*   Updated: 2022/06/16 12:59:56 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_infile_error(int file1, char *commands)
{
	if (file1 < 0)
		perror("unable to open file");
	else
	{
		write(2, "command not found : ", 20);
		write(2, commands, ft_strlen(commands));
		write(2, "\n", 1);
	}
}

void	handle_outfile_error(int file2, char *commands)
{
	if (file2 < 0)
	{
		perror("unable to open file");
		exit(1);
	}
	else
	{
		write(2, "command not found : ", 20);
		write(2, commands, ft_strlen(commands));
		write(2, "\n", 1);
		exit(127);
	}
}

void	fork_error(void)
{
	perror("fork error in command_to_outfile");
}

void	pipe_error(void)
{
	perror("pipe error in command_to_outfile");
}
