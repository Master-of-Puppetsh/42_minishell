/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 15:08:30 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/14 15:20:35 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

size_t	count_command(char *str)
{
	int		colon_flag;
	char	quote;
	size_t	count;

	quote = 0;
	count = 0;
	colon_flag = 1;
	while (*str != '\0')
	{
		if ((*str == '\'' || *str == '\"') && (quote == 0))
		{
			quote = *str;
		}
		else if ((*str == '\'' || *str == '\"') && (quote == *str))
		{
			quote = 0;
		}
		if (*str != ';' && colon_flag == 1)
		{
			count++;
			colon_flag = 0;
		}
		if (*str == ';' && quote == 0)
			colon_flag = 1;
		str++;
	}
	return (count);
}

static size_t	ft_wordlen(char const *s)
{
	size_t		count;

	count = 0;
	while (*s != '\0' && *s != ';')
	{
		count++;
		s++;
	}
	return (count);
}

char	check_quote(char *str, char quote)
{
	if ((*str == '\'' || *str == '\"') && (quote == 0))
		quote = *str;
	else if ((*str == '\'' || *str == '\"') && (quote == *str))
		quote = 1;
	return (quote);
}

static char		*ft_commanddup(char **str)
{
	char	*result;
	char	quote;
	size_t	i;

	if (!(result = ft_calloc(sizeof(char), (ft_wordlen(*str) + 1))))
		return (NULL);
	i = 0;
	quote = 0;
	while ((quote = check_quote(*str, quote)|| **str != ';') && **str != '\0')
	{
		if (!(quote == **str || quote == 1))
		{
			result[i] = **str;
			i++;
		}
		(*str)++;
	}
	(*str)--;
	return (result);
}

char	**split_command(char *str)
{
	char	**result;
	int		colon_flag;
	char	quote;
	int		i;

	if (!(result = ft_calloc(sizeof(char *), (count_command(str) + 1))))
		return (NULL);
	colon_flag = 1;
	quote = 0;
	i = 0;
	while (*str != '\0')
	{
		quote = check_quote(str, quote);
		if (*str != ';' && colon_flag == 1)
		{
			if (!(result[i++] = ft_commanddup(&str)))
				return (free_split(result));
			colon_flag = 0;
		}
		if (*str++ == ';' && (quote == 0 || quote == 1))
			colon_flag = 1;
	}
	return (result);
}
