/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:41:19 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:52:36 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;

	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		result[i++] = *s1++;
	}
	while (*s2 != '\0')
	{
		result[i++] = *s2++;
	}
	result[i] = '\0';
	return (result);
}
