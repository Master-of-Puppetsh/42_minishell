/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/07/06 15:49:08 by hjeon            ###   ########.fr       */
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

char		*remove_space_around_seperator(char *line)
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
			while (line[idx + ++j] != '\0' && (line[idx + j] == ' ' || line[idx + j] == ';'))
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

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**commands;
	int		status;
	int		i;

	status = 0;
	listen_signals();
	malloc_envp(envp);
	while (argc == 1 && *argv)
	{
		prompt();
		line = read_command_line(status);
		if (check_continuous_semicolons(line))
		{
			free(line);
			continue ;
		}
		line = remove_space_around_seperator(line);
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
