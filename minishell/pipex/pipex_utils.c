/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:58:14 by hyeo              #+#    #+#             */
/*   Updated: 2022/06/13 12:58:16 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *s4)
{
	int	i;

	i = 0;
	if (!s4)
		return (0);
	while (s4[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (temp == NULL)
		return (NULL);
	while (*s1)
	{
		temp[i] = *s1;
		s1++;
		i++;
	}
	temp[i] = '/';
	i++;
	while (*s2)
	{
		temp[i] = *s2;
		s2++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strjoin_for_parsing(char *s1, char s2)
{
	char	*temp;
	size_t	i;
	int		flag;

	flag = 0;
	i = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * (1));
		s1[0] = '\0';
		flag = 1;
	}
	temp = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (temp == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		temp[i] = s1[i];
	temp[i] = s2;
	i++;
	temp[i] = '\0';
	if (flag == 1)
		free(s1);
	return (temp);
}

int	ft_strchr(char *s, char *c)
{
	char	target;
	int		i;

	i = 0;
	target = c[0];
	while (s[i] != '\0')
	{
		if (s[i] == target)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (dstsize == 0)
		return (j);
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
