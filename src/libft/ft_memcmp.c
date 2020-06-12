/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 03:22:33 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 23:00:17 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s1_str;
	const unsigned char *s2_str;
	size_t				i;

	if (n == 0)
		return (0);
	s1_str = s1;
	s2_str = s2;
	i = 0;
	while (i < n - 1 && s1_str[i] == s2_str[i])
	{
		i++;
	}
	return (s1_str[i] - s2_str[i]);
}
