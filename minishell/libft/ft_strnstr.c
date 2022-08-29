/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:02:43 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/16 14:47:54 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
				return (&((char *)haystack)[i]);
		}
		i++;
	}
	return (0);
}
//int main()
//{
//	const char *haystack = "abcdef";
//	const char *needle;
//	size_t len = 6;
//	printf("%s", ft_strnstr(haystack, needle, len));
//}
