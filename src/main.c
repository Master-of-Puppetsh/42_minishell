/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/30 20:53:24 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_pid = -1;

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**commands;
	int		status;
	int		i;

	status = 0;
	listen_signals();
	while (argc == 1 && *argv)
	{
		prompt();
		line = read_command_line(status);
		if (!(commands = split_command(line, ';')))
			return (1);
		free(line);
		ft_putendl_fd("hello", STDOUT_FILENO);
		i = 0;
		while (*(commands + i))
			status = execute_command(*(commands + i++), &envp, status);
		free_split(commands);
	}
	return (status);
}
