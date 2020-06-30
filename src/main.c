/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/30 22:07:56 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_pid = -1;

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	*trimmed_line;
	char	**commands;
	int		status;
	int		i;

	status = 0;
	listen_signals();
	while (argc == 1 && *argv)
	{
		prompt();
		line = read_command_line(status);
		if (!(trimmed_line = ft_strtrim(line, " ")))
			return (1);
		free(line);
		if (!(commands = split_command(trimmed_line, ';')))
			return (1);
		free(trimmed_line);
		i = 0;
		while (*(commands + i))
			status = execute_command(*(commands + i++), &envp, status);
		free_split(commands);
	}
	return (status);
}
