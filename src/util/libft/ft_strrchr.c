/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:50:16 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 23:01:07 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len != 0)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
		len--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
