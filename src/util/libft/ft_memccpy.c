/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:19:14 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:57:58 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <stdlib.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dest_str;
	const char	*src_str;
	char		target;
	size_t		i;

	i = 0;
	target = c;
	dest_str = dest;
	src_str = src;
	while (i < n)
	{
		dest_str[i] = src_str[i];
		if (src_str[i] == target)
			return (dest_str + i + 1);
		i++;
	}
	return (NULL);
}
