/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:58:05 by hyeo              #+#    #+#             */
/*   Updated: 2022/06/16 12:58:56 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execve_error(void)
{
	perror("execve error in command_to_outfile ");
	exit(1);
}

void	file_number_error(void)
{
	perror("you must have 4 inputs");
}
