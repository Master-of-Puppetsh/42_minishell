/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:58:22 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/17 21:02:43 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_err_continous_semicolons(int err_type)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	if (err_type == 1)
		ft_putendl_fd("';;'", STDERR_FILENO);
	else
		ft_putendl_fd("';'", STDERR_FILENO);
	return (err_type);
}

int		check_continuous_semicolons(char *line)
{
	char	quote;
	int		idx;
	int		j;
	int		has_space;

	init_3vars_to_zero(&quote, &idx, &has_space);
	while (line[idx] != '\0')
	{
		if (!(quote = check_quote(line, quote, idx)) && line[idx] == ';')
		{
			j = 0;
			while (line[idx + ++j] != '\0' && (line[idx + j] == ' '
					|| line[idx + j] == ';'))
			{
				has_space = line[idx + j] == ' ' ? 1 : has_space;
				if (line[idx + j] == ';')
					return (print_err_continous_semicolons(1 + has_space));
			}
			has_space = 0;
		}
		quote = quote == 1 ? 0 : quote;
		idx++;
	}
	return (0);
}

char	**malloc_envp(char **envp)
{
	char	**malloced_envp;
	int		i;

	i = -1;
	while (*(envp + ++i))
		;
	malloced_envp = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (*envp)
	{
		if (!(*(malloced_envp + i) = ft_strdup(*envp)))
			exit_with_err_msg(ERRMSG_MALLOC, CMD_ERR);
		envp++;
		i++;
	}
	return (malloced_envp);
}

void	make_quote_printable(char *str)
{
	while (*str != '\0')
	{
		if (*str == ('\'' - 100) || *str == ('\"' - 100)
			|| *str == ('\\' - 100))
			*str += 100;
		str++;
	}
}

void	clean_arg(char *arg)
{
	remove_escapes(arg);
	remove_quotes(arg);
	make_quote_printable(arg);
}
