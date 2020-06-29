/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:21:27 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/29 16:26:39 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		check_quote(char *str, char quote)
{
	if ((*str == '\'' || *str == '\"') && ((quote == 0)))
		quote = *str;
	else if ((*str == '\'' || *str == '\"') && (quote == *str))
		quote = 1;
	return (quote);
}

void		*free_split(char **splitted_str)
{
	int		i;

	i = 0;
	while (*(splitted_str + i))
	{
		free(*(splitted_str + i));
		i++;
	}
	free(splitted_str);
	return (NULL);
}

void		exit_with_err_msg(char *msg, int status)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(status);
}

void		prompt(void)
{
	write(STDERR_FILENO, "\n", 1);
	ft_putstr_fd("\033[0;36m", STDERR_FILENO);
	write(STDERR_FILENO, "\e[1m", 4);
	ft_pwd(STDERR_FILENO);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	write(STDERR_FILENO, "> ", 2);
}

void		remove_tab(char **argv, int idx)
{
	int		i;

	free(argv[idx]);
	i = 1;
	while (*(argv + idx + i))
	{
		argv[idx + i - 1] = argv[idx + i];
		i++;
	}
	argv[idx + i - 1] = NULL;
}
