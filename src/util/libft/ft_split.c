/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 19:36:09 by hyekim            #+#    #+#             */
/*   Updated: 2020/04/03 22:52:29 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static size_t	count_word(char const *s, char c)
{
	int		flag;
	size_t	count;

	count = 0;
	flag = 1;
	while (*s != '\0')
	{
		if (*s != c && flag == 1)
		{
			count++;
			flag = 0;
		}
		if (*s == c)
			flag = 1;
		s++;
	}
	return (count);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t		count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		count++;
		s++;
	}
	return (count);
}

static char		*ft_worddup(char const **s, char c)
{
	char	*result;
	size_t	i;

	if (!(result = malloc(sizeof(char) * (ft_wordlen(*s, c) + 1))))
		return (NULL);
	i = 0;
	while (**s != '\0' && **s != c)
	{
		result[i] = **s;
		i++;
		(*s)++;
	}
	(*s)--;
	result[i] = '\0';
	return (result);
}

static void		*ft_free_split(char **result, size_t split_count)
{
	size_t	i;

	i = 0;
	while (i < split_count)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	int		flag;

	if (!(result = malloc(sizeof(char *) * (count_word(s, c) + 1))))
		return (NULL);
	flag = 1;
	i = 0;
	while (*s != '\0')
	{
		if (*s != c && flag == 1)
		{
			if (!(result[i] = ft_worddup(&s, c)))
				return (ft_free_split(result, i));
			i++;
			flag = 0;
		}
		if (*s == c)
			flag = 1;
		s++;
	}
	result[i] = NULL;
	return (result);
}
