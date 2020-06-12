/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:32:09 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/04 22:26:14 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	str_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	i = 0;
	while (i < len && start + i < str_len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
