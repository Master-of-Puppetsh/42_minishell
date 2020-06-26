/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 15:08:30 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/26 18:45:53 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

char	check_quote(char *str, char quote)
{
	if ((*str == '\'' || *str == '\"') && ((quote == 0)))
		quote = *str;
	else if ((*str == '\'' || *str == '\"') && (quote == *str))
		quote = 1;
	return (quote);
}

size_t	count_command(char *str, char target)
{
	int		colon_flag;
	char	quote;
	size_t	count;

	quote = 0;
	count = 0;
	colon_flag = 1;
	while (*str != '\0')
	{
		quote = check_quote(str, quote);
		if (*str != target && colon_flag == 1)
		{
			count++;
			colon_flag = 0;
		}
		if (*str == target && (quote == 0))
			colon_flag = 1;
		else if (*str == target && (quote == 1))
		{
			colon_flag = 1;
			quote = 0;
		}
		str++;
	}
	return (count);
}

static size_t	ft_wordlen(char const *s, char target)
{
	size_t		count;

	count = 0;
	while (*s != '\0' && *s != target)
	{
		count++;
		s++;
	}
	return (count);
}


static char		*ft_commanddup(char **str, char target)
{
	char	*result;
	char	quote;
	size_t	i;

	if (!(result = ft_calloc(sizeof(char), (ft_wordlen(*str, target) + 1))))
		return (NULL);
	i = 0;
	quote = check_quote(*str, 0);
	while ((quote || **str != target) && **str != '\0')
	{
		if (!(quote == **str || quote == 1))
		{
			result[i] = **str;
			i++;
		}
		if (quote == 1)
			quote = 0;
		(*str)++;
		quote = check_quote(*str, quote);
	}
	(*str)--;
	return (result);
}

char	**split_command(char *str, char target)
{
	char	**result;
	int		colon_flag;
	char	quote;
	int		i;

	if (!(result = ft_calloc(sizeof(char *), (count_command(str, target) + 1))))
		return (NULL);
	colon_flag = 1;
	quote = 0;
	i = 0;
	while (*str != '\0')
	{
		quote = check_quote(str, quote);
		if (*str != target && colon_flag == 1)
		{
			if (!(result[i++] = ft_commanddup(&str, target)))
				return (free_split(result));
			colon_flag = 0;
		}
		if (*str == target && (quote == 0))
			colon_flag = 1;
		else if (*str == target && (quote == 1))
		{
			colon_flag = 1;
			quote = 0;
		}
		str++;
	}
	return (result);
}
