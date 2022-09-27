/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:08:47 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/27 18:24:42 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
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
	temp[i] = *s2;
	i++;
	temp[i] = '\0';
	if (flag == 1)
		free(s1);
	return (temp);
}

char	*ft_strjoin_normal(char *s1, char *s2)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s1)
		hs_create_empty(s1);
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

void	ft_free_join(char const *s1, char const *s2)
{
	free((char *)s1);
	free((char *)s2);
	s1 = NULL;
	s2 = NULL;
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
	ft_free_join(s1, s2);
	temp[i] = '\0';
	return (temp);
}

void	free_both(char const *s1, char const *s2)
{
	if (s1)
	{
		free((char *)s1);
		s1 = NULL;
	}
	if (s2)
	{
		free((char *)s2);
		s2 = NULL;
	}
}
