/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:05:56 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/16 14:11:52 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		total;
	char	*temp;

	i = 0;
	total = 0;
	while (s1[total] != '\0')
		total++;
	temp = malloc(sizeof(char) * (total + 1));
	if (temp == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
