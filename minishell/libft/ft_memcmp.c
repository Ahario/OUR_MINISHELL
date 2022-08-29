/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:26:07 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/17 11:30:22 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*compare1;
	unsigned char	*compare2;

	i = 0;
	compare1 = (unsigned char *)s1;
	compare2 = (unsigned char *)s2;
	while (i < n)
	{
		if (compare1[i] != compare2[i])
			return (compare1[i] - compare2[i]);
		i++;
	}
	return (0);
}
