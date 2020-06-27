/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyekim <hyekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:57:34 by hjeon             #+#    #+#             */
/*   Updated: 2020/06/19 14:23:335 by hyekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

extern int	g_pid;

void		execute_program(char **argv, char *envp[], int *status)
{
	char		**paths;

	g_pid = fork();
	paths = get_paths(envp);
	if (g_pid > 0)
	{
		waitpid(g_pid, status, 0);
		*status = WEXITSTATUS(*status);
	}
	else if (g_pid == 0)
	{
		while (*(paths))
		{
			execve(ft_strjoin(*(paths), argv[0]), argv, envp);
			paths++;
		}
		exit(CMD_NOT_FOUND);
	}
}
