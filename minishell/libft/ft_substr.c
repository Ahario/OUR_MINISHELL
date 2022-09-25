/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:12:39 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/29 15:18:39 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	temp = malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (NULL);
	while (s[i] != '\0' && j < len && start < ft_strlen(s))
	{
		temp[j] = s[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}
