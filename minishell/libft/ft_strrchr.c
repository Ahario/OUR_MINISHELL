/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:06:45 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/18 13:17:36 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	target;
	char	*src;

	i = ft_strlen(s);
	target = (unsigned char)c;
	src = (char *)s;
	while (i > 0)
	{
		if (src[i] == target)
			return (&((char *)s)[i]);
		i--;
	}
	if (src[i] == target)
		return (&((char *)s)[i]);
	return (0);
}

//int main()
//{
//	const char *s = "abcdef";
//	int c = 99;
//	printf("%s", ft_strrchr(s, c));
//}
