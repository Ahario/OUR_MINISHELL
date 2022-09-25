/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:24:58 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/17 16:06:18 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	size_t	i;

	temp = malloc((count * size));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((unsigned char *)temp)[i] = 0;
		i++;
	}	
	return (temp);
}
