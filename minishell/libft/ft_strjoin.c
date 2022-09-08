/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:08:47 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/05 01:04:04 by lee-sung         ###   ########.fr       */
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

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (temp == NULL)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		temp[i] = s2[j++];
		i++;
	}
	free((char *)s1);
	free((char *)s2);
	s1 = NULL;
	s2 = NULL;
	temp[i] = '\0';
	return (temp);
}

char	*ft_strjoin_keyval(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		temp = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	else
		temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (temp == NULL)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i++] = '=';
	while (s2 && s2[j])
	{
		temp[i] = s2[j++];
		i++;
	}
	if(s1)
	{
		free((char *)s1);
		s1 = NULL;
	}
	if (s2)
	{
		free((char *)s2);
		s2 = NULL;
	}
	temp[i] = '\0';
	return (temp);
}
