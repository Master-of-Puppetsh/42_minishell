/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:22:44 by hjeon             #+#    #+#             */
/*   Updated: 2020/07/01 20:10:30 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_escape(int idx, char quote, char *str)
{
	int		is_escape;

	is_escape = 0;
	while (quote != '\'' && idx > 0 && str[idx - 1] == '\\')
	{
		is_escape = !is_escape;
		idx--;
	}
	return (is_escape);
}

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

void		replace_env(char **arg, char **envp, int status)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (*(*arg + ++i) != '\0')
	{
		quote = check_quote(*arg, quote, i);
		if (*(*arg + i) == '$' && *(*arg + i + 1) != '\0'
				&& (quote == '\"' || quote == 0) && !is_escape(i, quote, *arg))
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
		i++;
	}
	return (argv);
}
