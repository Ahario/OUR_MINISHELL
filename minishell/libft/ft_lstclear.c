/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <hyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:08:01 by hyeo              #+#    #+#             */
/*   Updated: 2021/11/19 11:56:25 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	temp = *lst;
	while (*lst != NULL)
	{
		*lst = temp->next;
		del(temp->content);
		free(temp);
		temp = *lst;
	}
}
