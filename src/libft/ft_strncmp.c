/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 05:31:05 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 23:00:55 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	if (len == 0)
		return (0);
	while (len != 1 && *s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
		len--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
