/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 03:16:20 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:51:23 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char		target;
	const char	*str;
	size_t		i;

	target = c;
	str = s;
	i = 0;
	while (i < n)
	{
		if (str[i] == target)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
