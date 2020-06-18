/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:46:20 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:52:47 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static int	is_in_charset(char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_idx;
	size_t	end_idx;

	start_idx = 0;
	end_idx = ft_strlen(s1);
	if (end_idx == 0)
		return (ft_strdup(s1));
	while (start_idx < end_idx && is_in_charset(s1[start_idx], set))
	{
		start_idx++;
	}
	while ((start_idx < end_idx && is_in_charset(s1[end_idx], set))
			|| s1[end_idx] == '\0')
	{
		end_idx--;
	}
	return (ft_substr(s1, start_idx, end_idx - start_idx + 1));
}
