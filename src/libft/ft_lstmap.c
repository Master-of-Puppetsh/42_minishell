/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:43:38 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:51:18 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*cursor;

	if (lst == NULL)
		return (NULL);
	if (!(begin = ft_lstnew((*f)(lst->content))))
		return (NULL);
	cursor = begin;
	while ((lst = lst->next))
	{
		if (!(cursor->next = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		cursor = cursor->next;
	}
	return (begin);
}
