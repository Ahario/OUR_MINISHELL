/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:23:19 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 18:32:37 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_keyval_utill(char const *s1, char const *s2, char *temp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
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
	free_both(s1, s2);
	temp[i] = '\0';
	return (temp);
}

char	*ft_strjoin_keyval(char const *s1, char const *s2)
{
	char	*temp;

	if (!s2)
		temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	else
		temp = (char *)malloc(sizeof(char) * \
				(ft_strlen(s1) + ft_strlen(s2) + 2));
	if (temp == NULL)
		return (NULL);
	return (ft_keyval_utill(s1, s2, temp));
}

void	ft_free_flag(char const *s1, char const *s2, int flag)
{
	if (flag == 1 || flag == 3)
	{
		free((char *)s1);
		s1 = NULL;
	}
	if (flag == 2 || flag == 3)
	{
		free((char *)s2);
		s2 = NULL;
	}
}

char	*ft_flag_utill(char const *s1, char const *s2, char *temp, int flag)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
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
	temp[i] = '\0';
	ft_free_flag(s1, s2, flag);
	return (temp);
}

char	*ft_strjoin_flag(char const *s1, char const *s2, int flag)
{
	char	*temp;

	if (!s2)
		temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	else
		temp = (char *)malloc(sizeof(char) * \
				(ft_strlen(s1) + ft_strlen(s2) + 2));
	if (temp == NULL)
		return (NULL);
	return (ft_flag_utill(s1, s2, temp, flag));
}
