/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 15:08:30 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/29 16:27:54 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_command(char *str, char target)
{
	int		target_flag;
	char	quote;
	size_t	count;

	quote = 0;
	count = 0;
	target_flag = 1;
	while (*str != '\0')
	{
		quote = check_quote(str, quote);
		if (*str != target && target_flag == 1)
		{
			count++;
			target_flag = 0;
		}
		if (*str == target && (quote == 0))
			target_flag = 1;
		else if (*str == target && (quote == 1))
		{
			target_flag = 1;
			quote = 0;
		}
		str++;
	}
	return (count);
}

size_t	ft_wordlen(char *str, char target)
{
	size_t		count;
	char		quote;

	quote = check_quote(str, 0);
	count = 0;
	while ((quote || *str != target) && *str != '\0')
	{
		count++;
		str++;
		quote = check_quote(str, quote);
	}
	return (count);
}

char	*ft_commanddup(char **str, char target)
{
	char	*result;
	char	quote;
	size_t	i;

	if (!(result = ft_calloc(sizeof(char), (ft_wordlen(*str, target) + 2))))
		return (NULL);
	i = 0;
	quote = check_quote(*str, 0);
	while ((quote || **str != target) && **str != '\0')
	{
		result[i] = **str;
		i++;
		if (quote == 1)
			quote = 0;
		(*str)++;
		quote = check_quote(*str, quote);
	}
	while (**str != target && **str != '\0')
		(*str)++;
	return (result);
}

void	set_flags(char *str, char *quote, char target, int *target_flag)
{
	if (*str == target && (*quote == 0))
		target_flag = 1;
	else if (*str == target && (*quote == 1))
	{
		*target_flag = 1;
		*quote = 0;
	}
	return ;
}

char	**split_command(char *str, char target)
{
	char	**result;
	int		target_flag;
	char	quote;
	int		i;

	if (!(result = ft_calloc(sizeof(char *), (count_command(str, target) + 1))))
		return (NULL);
	target_flag = 1;
	quote = 0;
	i = 0;
	while (*str != '\0')
	{
		quote = check_quote(str, quote);
		if (*str != target && target_flag == 1)
		{
			if (!(result[i++] = ft_commanddup(&str, target)))
				return (free_split(result));
			target_flag = 0;
			quote = 0;
		}
		set_flags(str, &quote, target, &target_flag);
		if (*str != '\0')
			str++;
	}
	return (result);
}
