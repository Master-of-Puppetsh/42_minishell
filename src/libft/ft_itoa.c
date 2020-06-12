/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:09:51 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:57:02 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <stdlib.h>

static int		ft_numlen(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	n = n / 10;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*result;
	int		sign;
	int		len;

	len = ft_numlen(n);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result[len--] = '\0';
	sign = 1;
	if (n < 0)
	{
		result[0] = '-';
		sign = -1;
	}
	result[len--] = n % 10 * sign + '0';
	while ((n /= 10))
	{
		result[len--] = n % 10 * sign + '0';
	}
	return (result);
}
