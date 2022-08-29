/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:48:50 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/19 11:53:40 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*temp;

	i = 0;
	if (!s || !f)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (temp == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		temp[i] = f(i, s[i]);
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
//char f(unsigned int i, char s)
//{
//	printf("%d %c\n", i, s);
//	return (1);
//}
//
//int main()
//{
//	char const *s = "abcdefg";
//	ft_strmapi(s, f);
//}
