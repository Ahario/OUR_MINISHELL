/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:47:28 by hyeo              #+#    #+#             */
/*   Updated: 2021/12/01 13:46:20 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(const char *s, int c)
{
	char	target;
	int		i;

	i = 0;
	target = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == target)
			return (1);
		i++;
	}
	if (s[i] == target)
		return (1);
	return (0);
}
