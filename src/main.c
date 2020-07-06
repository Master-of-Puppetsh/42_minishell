/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/06 16:14:09 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_pid = -1;

char		*remove_left_space(char *line, int *i)
{
	int		j;

	j = *i - 1;
	while (j >= 0 && line[j] == ' ')
	{
		ft_memmove(line + j, line + j + 1, ft_strlen(line + j + 1) + 1);
		j--;
	}
	*i = j + 1;
	return (line);
}

char		*remove_right_space(char *line, int *i)
{
	int		j;
	int		len;

	j = *i + 1;
	len = ft_strlen(line);
	while (j < len && line[j] == ' ')
	{
		ft_memmove(line + j, line + j + 1, ft_strlen(line + j + 1) + 1);
	}
	*i = j - 1;
	return (line);
}

char		*remove_space_around_separator(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (*(line + i))
	{
		quote = check_quote(line, quote, i);
		if (quote == 0 && (*(line + i) == ';' ||
				*(line + i) == '|') && !is_escape(i, quote, line))
		{
			line = remove_left_space(line, &i);
			line = remove_right_space(line, &i);
		}
		if (quote == 1)
			quote = 0;
		i++;
	}
	return (line);
}

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**commands;
	int		status;
	int		i;

	status = 0;
	listen_signals();
	malloc_envp(envp);
	while (argc == 1 && *argv && prompt())
	{
		if (check_continuous_semicolons((line = read_command_line(status))))
		{
			free(line);
			continue ;
		}
		line = remove_space_around_separator(line);
		if (!(commands = split_command(line, ';')))
			return (1);
		free(line);
		i = 0;
		while (*(commands + i))
			status = execute_command(*(commands + i++), &envp, status);
		free_split(commands);
	}
	return (status);
}
