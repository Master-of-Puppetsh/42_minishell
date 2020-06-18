/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:14:03 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:50:40 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	length;
	size_t	i;

	length = ft_strlen(str);
	result = malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
