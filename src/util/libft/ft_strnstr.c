/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:57:06 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:50:51 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	find_len;

	find_len = ft_strlen(little);
	if (find_len == 0)
		return ((char *)big);
	while (*big != '\0' && len >= find_len)
	{
		if (ft_strncmp(big, little, find_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
