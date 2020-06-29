/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:22:44 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/29 16:25:23 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*replace_text(char *dest, int start, int length, char *src)
{
	char	*result;
	int		total_len;

	if (dest == NULL)
		exit_with_err_msg(ERRMSG_MALLOC, 1);
	total_len = ft_strlen(src) + ft_strlen(dest) - length + 1;
	if (!(result = ft_calloc(total_len, sizeof(char))))
		exit_with_err_msg(ERRMSG_MALLOC, 1);
	ft_strlcat(result, dest, start);
	ft_strlcat(result, src, start + ft_strlen(src));
	ft_strlcat(result, dest + start + length, total_len);
	free(dest);
	return (result);
}

void		remove_quotes(char *str)
{
	char	quote;

	quote = 0;
	while (*str != '\0')
	{
		quote = check_quote(str, quote);
		if ((*str == '\'' || *str == '\"') && (quote == *str || quote == 1))
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			str--;
		}
		if (quote == 1)
			quote = 0;
		str++;
	}
}

void		replace_env(char **arg, char **envp, int status)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (*(*arg + ++i) != '\0')
	{
		quote = check_quote((*arg + i), quote);
		if (*(*arg + i) == '$' && *(*arg + i + 1) != '\0'
						&& (quote == '\"' || quote == 0))
		{
			if (*(*arg + ++i) == '?')
			{
				i += replace_question_to_status(status, i, arg);
				continue ;
			}
			i += do_replace_env(i, arg, envp);
		}
		if (quote == 1)
			quote = 0;
	}
}

char		**parse_command(char *command, char **envp, int status)
{
	char	**argv;
	int		i;

	if (!(argv = split_command(command, ' ')))
		exit_with_err_msg(ERRMSG_MALLOC, 1);
	i = 0;
	while (*(argv + i) != NULL)
	{
		replace_env(argv + i, envp, status);
		remove_quotes(*(argv + i));
		i++;
	}
	return (argv);
}
