/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeon <hjeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:26:25 by hyekim            #+#    #+#             */
/*   Updated: 2020/06/18 22:51:29 by hjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**paths;
	char	**commands;
	int		status;
	int		i;
	char	**cmd_argv;

	paths = init_env(envp);
	status = 0;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		if ((i = get_next_line(STDIN_FILENO, &line)) == -1 || i == 0)
			return (i * -1);
		if (!(commands = split_command(line)))
			return (1);
		i = -1;
		while (*(commands + ++i))
		{
			cmd_argv = parse_command(*(commands + i), envp, status);
			execute_builtin(cmd_argv, &envp, &status);
			if (status == CMD_NOT_FOUND)
				execute_program(paths, cmd_argv, envp, &status);
		}
		free_split(commands);
	}
	return (status);
}
