/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 21:47:59 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/12 17:21:55 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "get_next_line.h"

ssize_t		ft_stridx(char *str, char target)
{
	ssize_t	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == target)
			return (idx);
		idx++;
	}
	return (-1);
}
