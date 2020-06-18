/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 04:43:20 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/13 04:47:54 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	size_t	length;
	void	*temp;
	t_list	*list;
	size_t	idx;

	length = ft_lstlen(*begin_list);
	idx = 0;
	while (1 < length)
	{
		list = *begin_list;
		idx = 0;
		while (idx < length - 1)
		{
			if ((*cmp)(list->content, (list->next)->content) > 0)
			{
				temp = list->content;
				list->content = (list->next)->content;
				(list->next)->content = temp;
			}
			list = list->next;
			idx++;
		}
		length--;
	}
}
