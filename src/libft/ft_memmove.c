/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:31:26 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/04 21:44:23 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_str;
	const char	*src_str;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	dest_str = dest;
	src_str = src;
	i = 0;
	while (i < n)
	{
		dest_str[n - 1 - i] = src_str[n - 1 - i];
		i++;
	}
	return (dest);
}
