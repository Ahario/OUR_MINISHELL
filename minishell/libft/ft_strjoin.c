/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:08:47 by hyeo              #+#    #+#             */
/*   Updated: 2021/12/01 14:40:25 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (temp == NULL)
		return (NULL);
	while (*s1)
	{
		temp[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		temp[i] = *s2;
		s2++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
