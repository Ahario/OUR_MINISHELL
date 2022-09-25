/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:46:09 by hyeo              #+#    #+#             */
/*   Updated: 2021/12/01 13:43:13 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*source;
	void	*cont;	

	if (lst == NULL || f == NULL)
		return (NULL);
	new = 0;
	source = 0;
	cont = 0;
	while (lst != NULL)
	{
		cont = f(lst->content);
		source = ft_lstnew(cont);
		if (source == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, source);
		lst = lst->next;
	}
	return (new);
}
